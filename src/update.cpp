#include "../include/update.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <winhttp.h>
#include <shlobj.h>

// #pragma comment(lib, "winhttp.lib")

namespace pt {

    fs::path get_update_dir() {
        wchar_t path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, path))) {
            return fs::path(path) / "platinum";
        }
        return fs::current_path() / "platinum";
    }

    fs::path get_update_bat_path() {
        return get_update_dir() / "update.bat";
    }

    fs::path get_temp_download_path() {
        wchar_t path[MAX_PATH];
        GetTempPathW(MAX_PATH, path);
        return fs::path(path) / "platinum_update.exe";
    }

    fs::path get_current_exe_path() {
        wchar_t path[MAX_PATH];
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        return fs::path(path);
    }

    std::string http_get(const std::string& url) {
        std::string result;

        URL_COMPONENTS urlComp = {0};
        urlComp.dwStructSize = sizeof(urlComp);
        
        wchar_t hostName[256] = {0};
        wchar_t urlPath[1024] = {0};
        wchar_t scheme[32] = {0};
        
        urlComp.lpszHostName = hostName;
        urlComp.dwHostNameLength = ARRAYSIZE(hostName);
        urlComp.lpszUrlPath = urlPath;
        urlComp.dwUrlPathLength = ARRAYSIZE(urlPath);
        urlComp.lpszScheme = scheme;
        urlComp.dwSchemeLength = ARRAYSIZE(scheme);

        std::wstring wurl(url.begin(), url.end());
        if (!WinHttpCrackUrl(wurl.c_str(), 0, 0, &urlComp)) {
            std::cerr << "[ERROR] Failed to parse URL" << std::endl;
            return result;
        }

        HINTERNET hSession = WinHttpOpen(
            L"Platinum-Updater/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0
        );
        if (!hSession) {
            std::cerr << "[ERROR] WinHttpOpen failed" << std::endl;
            return result;
        }

        HINTERNET hConnect = WinHttpConnect(
            hSession,
            urlComp.lpszHostName,
            urlComp.nPort,
            0
        );
        if (!hConnect) {
            std::cerr << "[ERROR] WinHttpConnect failed" << std::endl;
            WinHttpCloseHandle(hSession);
            return result;
        }

        HINTERNET hRequest = WinHttpOpenRequest(
            hConnect,
            L"GET",
            urlComp.lpszUrlPath,
            nullptr,
            WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0
        );
        if (!hRequest) {
            std::cerr << "[ERROR] WinHttpOpenRequest failed" << std::endl;
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            return result;
        }

        BOOL bResults = WinHttpSendRequest(
            hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0,
            WINHTTP_NO_REQUEST_DATA,
            0,
            0,
            0
        );

        if (!bResults || !WinHttpReceiveResponse(hRequest, nullptr)) {
            std::cerr << "[ERROR] Request failed" << std::endl;
            WinHttpCloseHandle(hRequest);
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            return result;
        }

        DWORD dwSize = 0;
        DWORD dwDownloaded = 0;
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
                break;
            }

            if (dwSize == 0) break;

            std::vector<char> buffer(dwSize + 1);
            ZeroMemory(buffer.data(), dwSize + 1);

            if (!WinHttpReadData(hRequest, buffer.data(), dwSize, &dwDownloaded)) {
                break;
            }

            result.append(buffer.data(), dwDownloaded);
        } while (dwSize > 0);

        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);

        return result;
    }

    std::vector<VersionInfo> parse_changelog(const std::string& json_str) {
        std::vector<VersionInfo> result;

        try {
            auto j = json::parse(json_str);

            for (const auto& item : j) {
                VersionInfo info;
                info.version_name = item.value("version", "Unknown");

                if (item.contains("tag") && item["tag"].is_array()) {
                    auto& tags = item["tag"];
                    for (size_t i = 0; i < 3 && i < tags.size(); i++) {
                        info.tag[i] = tags[i].get<int>();
                    }
                }

                result.push_back(info);
            }
        } catch (const json::exception& e) {
            std::cerr << "[ERROR] JSON parse error: " << e.what() << std::endl;
        }

        return result;
    }

    VersionInfo get_latest_version(const std::string& json_str) {
        auto versions = parse_changelog(json_str);
        if (!versions.empty()) {
            return versions[0];
        }
        return VersionInfo{"Unknown", {0, 0, 0}};
    }

    bool is_newer_version(const int remote[3], const int local[3]) {
        for (int i = 0; i < 3; i++) {
            if (remote[i] > local[i]) return true;
            if (remote[i] < local[i]) return false;
        }
        return false;
    }

    bool download_file(const std::string& url, const fs::path& dest) {
        std::string data = http_get(url);
        if (data.empty()) {
            std::cerr << "[ERROR] Download failed: empty response" << std::endl;
            return false;
        }

        std::ofstream out(dest, std::ios::binary);
        if (!out) {
            std::cerr << "[ERROR] Cannot open file for writing: " << dest << std::endl;
            return false;
        }

        out.write(data.data(), data.size());
        out.close();

        return true;
    }

    void run_update_script(const fs::path& new_exe, const fs::path& current_exe) {
        fs::path update_dir = get_update_dir();
        if (!fs::exists(update_dir)) {
            fs::create_directories(update_dir);
        }

        fs::path bat_path = get_update_bat_path();

        std::ofstream bat(bat_path);
        if (!bat) {
            std::cerr << "[ERROR] Cannot create update script" << std::endl;
            return;
        }

        std::string current_str = current_exe.string();
        std::string new_str = new_exe.string();

        bat << "@echo off\n";
        bat << "echo [INFO] Waiting for Platinum to exit...\n";
        bat << "timeout /t 2 /nobreak >nul\n";
        bat << "echo [INFO] Installing update...\n";
        bat << "copy /Y \"" << new_str << "\" \"" << current_str << "\"\n";
        bat << "if %errorlevel% neq 0 (\n";
        bat << "    echo [ERROR] Update failed. Please run as administrator.\n";
        bat << "    pause\n";
        bat << "    exit /b 1\n";
        bat << ")\n";
        bat << "del \"" << new_str << "\"\n";
        bat << "echo [INFO] Update complete. Restarting...\n";
        bat << "start \"\" \"" << current_str << "\"\n";
        bat << "exit\n";

        bat.close();

        std::cout << "[INFO] Launching update installer..." << std::endl;

        Sleep(1000);

        ShellExecuteA(
            nullptr,
            "open",
            bat_path.string().c_str(),
            nullptr,
            nullptr,
            SW_SHOW
        );
    }

    void do_update(const int ver[3]) {

        const bool DEBUG = false;

        std::cout << "[INFO] Checking for updates..." << std::endl;

        std::string json_url = "https://pt.iw1o1.qzz.io/assets/res/update.json";
        if (DEBUG) json_url = "http://127.0.0.1:8080/update.json"; // debug
        std::string response = http_get(json_url);

        if (response.empty()) {
            std::cout << "[INFO] Primary source failed, trying fallback..." << std::endl;
            json_url = "https://raw.githubusercontent.com/IceWars1o1/Platinum/refs/heads/master/website/assets/res/update.json";
            response = http_get(json_url);
        }

        if (response.empty()) {
            std::cerr << "[ERROR] Failed to fetch update info. Please check your network." << std::endl;
            return;
        }

        VersionInfo latest = get_latest_version(response);

        std::cout << "[INFO] Current version: " << ver[0] << "." 
                  << ver[1] << "." << ver[2] << std::endl;
        std::cout << "[INFO] Latest version: " << latest.tag[0] << "." 
                  << latest.tag[1] << "." << latest.tag[2] << std::endl;

        if (!is_newer_version(latest.tag, ver)) {
            std::cout << "[INFO] You are already running the latest version." << std::endl;
            return;
        }

        std::cout << "[INFO] A new version is available!" << std::endl;
        std::cout << "[INFO] Changelog: https://pt.iw1o1.qzz.io/#changelog" << std::endl;

        std::cout << "[PROMPT] Download and install update? [Y/n] ";
        std::string input;
        std::cin >> input;

        if (input.empty() || (input[0] != 'Y' && input[0] != 'y')) {
            std::cout << "[INFO] Update cancelled." << std::endl;
            return;
        }

        fs::path temp_path = get_temp_download_path();

        std::cout << "[INFO] Downloading from GitHub..." << std::endl;
        std::string download_url = "https://github.com/IceWars1o1/Platinum/releases/download/"
            + std::to_string(latest.tag[0]) + "."
            + std::to_string(latest.tag[1]) + "."
            + std::to_string(latest.tag[2])
            + "/platinum.exe";
        if (DEBUG) download_url = "http://127.0.0.1:8080/"
            + std::to_string(latest.tag[0]) + "."
            + std::to_string(latest.tag[1]) + "."
            + std::to_string(latest.tag[2])
            + "/platinum.exe";

        if (!download_file(download_url, temp_path)) {
            std::cout << "[INFO] GitHub direct download failed, trying mirror..." << std::endl;
            std::string mirror_download_url = "https://gh-proxy.org/" + download_url;
            
            if (!download_file(mirror_download_url, temp_path)) {
                std::cerr << "[ERROR] Download failed." << std::endl;
                std::cout << "[INFO] You can manually download from:" << std::endl;
                std::cout << "      " << download_url << std::endl;
                std::cout << "[INFO] Or visit: https://github.com/IceWars1o1/Platinum/releases" << std::endl;
                return;
            }
        }

        std::cout << "[INFO] Download complete." << std::endl;

        std::cout << "[INFO] Platinum will now exit to apply the update." << std::endl;

        std::cout << temp_path << std::endl;

        Sleep(3000);

        fs::path current_exe = get_current_exe_path();
        run_update_script(temp_path, current_exe);

        std::exit(0);
    }

}