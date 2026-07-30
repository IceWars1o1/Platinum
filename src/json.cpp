#include "../include/json.hpp"
#include <fstream>

namespace pt{
    int parse_spacenum(const char* arg, int default_val) {
        if (std::strncmp(arg, "--spacenum=", 11) == 0) {
            int val = std::atoi(arg + 11);
            if (val == 2 || val == 4) return val;
            // 无效值，返回 -1 作为错误标记
            return -1;
        }
        return default_val;  // 不是 --spacenum 参数
    }

    std::string json_str(std::string input, int process){

        json j = json::parse(input);
        switch(process){

            case 1:         // minify
                return j.dump();
                break;

            case 2:         // format with 2 spaces
                return j.dump(2);
                break;

            case 3:         // format with 4 spaces
                return j.dump(4);
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