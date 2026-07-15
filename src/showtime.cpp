#include "../include/showtime.hpp"
#include <iostream>
#include <cstring>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#endif

namespace pt {

    static void print_usage() {
        std::cout << "Usage:" << std::endl;
        std::cout << "\tplatinum time [style: dash|slash|unix] <options>" << std::endl;
        std::cout << std::endl;
        std::cout << "Styles:" << std::endl;
        std::cout << "\tdash:  YYYY-MM-DD hh:mm(:ss)" << std::endl;
        std::cout << "\tslash: YYYY/MM/DD hh:mm(:ss)" << std::endl;
        std::cout << "\tunix:  Unix timestamp" << std::endl;
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "\t--net:    Get time from the internet." << std::endl;
        std::cout << "\tdash | slash:" << std::endl;
        std::cout << "\t  --no-sec: Do not display seconds." << std::endl;
        std::cout << "\tunix:" << std::endl;
        std::cout << "\t  --ms:   Use milliseconds." << std::endl;
    }

    #ifdef _WIN32
    static std::string fetch_network_time() {
        HINTERNET hSession = WinHttpOpen(L"Platinum/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS, 0);
        if (!hSession) return "";

        // 淘宝时间 API
        HINTERNET hConnect = WinHttpConnect(hSession, L"api.m.taobao.com",
            INTERNET_DEFAULT_HTTP_PORT, 0);
        if (!hConnect) {
            WinHttpCloseHandle(hSession);
            return "";
        }

        HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET",
            L"/rest/api3.do?api=mtop.common.getTimestamp", 
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
        if (!hRequest) {
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            return "";
        }

        BOOL bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS, 0,
            WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
        if (bResults) {
            bResults = WinHttpReceiveResponse(hRequest, NULL);
        }

        std::string response;
        if (bResults) {
            DWORD dwSize = 0;
            do {
                dwSize = 0;
                if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) break;
                if (dwSize == 0) break;

                char* buffer = new char[dwSize + 1];
                ZeroMemory(buffer, dwSize + 1);
                DWORD dwDownloaded = 0;
                if (WinHttpReadData(hRequest, (LPVOID)buffer, dwSize, &dwDownloaded)) {
                    response.append(buffer, dwDownloaded);
                }
                delete[] buffer;
            } while (dwSize > 0);
        }

        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);

        // Parse unixtime from JSON response
        size_t pos = response.find("\"unixtime\":");
        if (pos != std::string::npos) {
            pos += 11;
            size_t end = response.find(",", pos);
            if (end == std::string::npos) end = response.find("}", pos);
            return response.substr(pos, end - pos);
        }
        return "";
    }
    #endif

    static time_t get_time(bool use_network) {
    #ifdef _WIN32
        if (use_network) {
            std::string net_time = fetch_network_time();
            if (!net_time.empty()) {
                try {
                    return static_cast<time_t>(std::stoll(net_time));
                } catch (...) {
                    // fallback to system time
                }
            }
        }
    #endif
        return std::time(nullptr);
    }

    static void format_dash(time_t t, bool no_sec) {
        std::tm* tm = std::localtime(&t);
        if (!tm) return;
        if (no_sec) {
            std::cout << std::put_time(tm, "%Y-%m-%d %H:%M") << std::endl;
        } else {
            std::cout << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << std::endl;
        }
    }

    static void format_slash(time_t t, bool no_sec) {
        std::tm* tm = std::localtime(&t);
        if (!tm) return;
        if (no_sec) {
            std::cout << std::put_time(tm, "%Y/%m/%d %H:%M") << std::endl;
        } else {
            std::cout << std::put_time(tm, "%Y/%m/%d %H:%M:%S") << std::endl;
        }
    }

    static void format_unix(time_t t, bool use_ms) {
        if (use_ms) {
            auto now = std::chrono::system_clock::now();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()).count();
            std::cout << ms << std::endl;
        } else {
            std::cout << t << std::endl;
        }
    }

    void show_time(int argc, char* argv[]) {
        if (argc < 3) {
            print_usage();
            return;
        }

        const char* style = argv[2];
        bool use_network = false;
        bool no_sec = false;
        bool use_ms = false;

        for (int i = 3; i < argc; i++) {
            if (!std::strcmp(argv[i], "--net")) use_network = true;
            else if (!std::strcmp(argv[i], "--no-sec")) no_sec = true;
            else if (!std::strcmp(argv[i], "--ms")) use_ms = true;
        }

        time_t t = get_time(use_network);

        if (!std::strcmp(style, "dash")) {
            format_dash(t, no_sec);
        } else if (!std::strcmp(style, "slash")) {
            format_slash(t, no_sec);
        } else if (!std::strcmp(style, "unix")) {
            format_unix(t, use_ms);
        } else {
            std::cerr << "Unknown style: " << style << std::endl;
            print_usage();
        }
    }

}