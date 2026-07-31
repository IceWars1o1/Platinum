#include "../include/json.hpp"
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

namespace pt{
    // GBK -> UTF-8
    std::string gbk_to_utf8(const std::string& gbk) {
        if (gbk.empty()) return "";
        
        int wlen = MultiByteToWideChar(936, 0, gbk.c_str(), -1, nullptr, 0);
        std::vector<wchar_t> wstr(wlen);
        MultiByteToWideChar(936, 0, gbk.c_str(), -1, wstr.data(), wlen);
        
        int ulen = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
        std::string utf8(ulen - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, wstr.data(), -1, &utf8[0], ulen, nullptr, nullptr);
        
        return utf8;
    }

    // UTF-8 -> GBK
    std::string utf8_to_gbk(const std::string& utf8) {
        if (utf8.empty()) return "";
        
        int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
        std::vector<wchar_t> wstr(wlen);
        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wstr.data(), wlen);
        
        int glen = WideCharToMultiByte(936, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
        std::string gbk(glen - 1, 0);
        WideCharToMultiByte(936, 0, wstr.data(), -1, &gbk[0], glen, nullptr, nullptr);
        
        return gbk;
    }

    int parse_spacenum(const char* arg, int default_val) {  // int default_val=2;
        if (std::strncmp(arg, "--spacenum=", 11) == 0) {
            int val = std::atoi(arg + 11);
            if (val == 2 || val == 4) return val;
            // 无效值，返回 -1 作为错误标记
            return -1;
        }
        return default_val;  // 不是 --spacenum 参数
    }

    std::string json_str(std::string input, int process){

        std::string utf8_input = gbk_to_utf8(input);

        json j = json::parse(utf8_input);
        switch(process){

            case 1:         // minify
                return utf8_to_gbk(j.dump());
                break;

            case 2:         // format with 2 spaces
                return utf8_to_gbk(j.dump(2));
                break;

            case 3:         // format with 4 spaces
                return utf8_to_gbk(j.dump(4));
                break;

            default:
                throw std::runtime_error("Unknown processing method.");

        }

    }
    
    void json_file(fs::path file, int process){

        if (!fs::exists(file)) {
            throw std::runtime_error("File not found: " + file.string());
        }

        std::ifstream ifs(file);
        if (!ifs) {
            throw std::runtime_error("Cannot open file: " + file.string());
        }

        json j;
        try {
            ifs >> j;
        } catch (const json::parse_error& e) {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()));
        }

        ifs.close();
        std::string result;


        switch(process){

            case 1:         // minify
                result = j.dump();
                break;

            case 2:         // format with 2 ' 's
                result = j.dump(2);
                break;

            case 3:         // format with 4 ' 's
                result = j.dump(4);
                break;

            default:
                throw std::runtime_error("Unknown processing method.");

        }

        std::ofstream ofs(file, std::ios::trunc);
        if (!ofs) {
            throw std::runtime_error("Cannot write to file: " + file.string());
        }

        ofs << result;
        ofs.close();

    }

}