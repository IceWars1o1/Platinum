#include "../include/commands.hpp"
#include "../include/md5.hpp"
#include "../include/random.hpp"
#include "../include/todo.hpp"
#include "../include/uuid.hpp"
#include "../include/usage.hpp"
#include "../include/update.hpp" 
#include "../include/showtime.hpp"
#include "../include/json.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>

namespace pt {

    std::string join_args(int argc, char* argv[], int start) {
        std::string result;
        for (int i = start; i < argc; i++) {
            if (i > start) result += " ";
            result += argv[i];
        }
        return result;
    }
    
    void cmd_md5(int argc, char* argv[]) {
        if (argc < 3) {
            std::cerr << "Error: md5 requires text argument" << std::endl;
            return;
        }
        std::string text = join_args(argc, argv, 2);
        std::cout << md5_string(text) << std::endl;
    }
    
    void cmd_random(int argc, char* argv[]) {
        int min_val = 0, max_val = 100;
        for (int i = 2; i < argc; i++) {
            if (!std::strcmp(argv[i], "--min") && i + 1 < argc) {
                min_val = std::atoi(argv[++i]);
            } else if (!std::strcmp(argv[i], "--max") && i + 1 < argc) {
                max_val = std::atoi(argv[++i]);
            }
        }
        std::cout << random(min_val, max_val) << std::endl;
    }
    
    void cmd_todo(int argc, char* argv[]) {
        if (argc < 3) {
            std::cerr << "Error: todo requires subcommand" << std::endl;
            return;
        }
        if (!std::strcmp(argv[2], "add") && argc >= 4) {
            std::string item = join_args(argc, argv, 3);
            todo_add(item);
        } else if (!std::strcmp(argv[2], "list")) {
            todo_list();
        } else if (!std::strcmp(argv[2], "remove")) {
            todo_remove_interactive();
        } else if (!std::strcmp(argv[2], "finish")){
            todo_done_interactive();
        } else if (!std::strcmp(argv[2], "clear")) {
            todo_clear();
        } else {
            std::cerr << "Error: Unknown todo subcommand" << std::endl;
        }
    }

    void cmd_json(int argc, char* argv[]) {
        if (argc < 5) {
            std::cerr << "Error: insufficient arguments\n" << JSON_USAGE << std::endl;
            return;
        }

        std::string mode = argv[2];
        if (mode != "str" && mode != "file") {
            std::cerr << "Error: unknown mode '" << mode << "'\n" << JSON_USAGE << std::endl;
            return;
        }

        std::string action = argv[3];
        if (action != "minify" && action != "format") {
            std::cerr << "Error: unknown action '" << action << "'\n" << JSON_USAGE << std::endl;
            return;
        }

        // 解析可选参数 --spacenum 和 input 的位置
        int process = 0;      // 1=minify, 2=format-2sp, 3=format-4sp
        int input_idx = 4;    // input 默认在 argv[4]
        int spaces = 2;       // format 默认缩进

        if (mode == "str" || mode == "file") {
            if (action == "minify") {
                process = 1;
            } else {  // format
                // 检查 argv[4] 是否是 --spacenum=?
                int sp = parse_spacenum(argv[4]);
                if (sp == -1) {
                    std::cerr << "Error: invalid --spacenum value (must be 2 or 4)\n" << JSON_USAGE << std::endl;
                    return;
                }
                if (sp != 2) {  // 如果 argv[4] 是 --spacenum=4
                    spaces = sp;
                    input_idx = 5;  // input 后移到 argv[5]
                }
                else if (parse_spacenum(argv[4], 0)){ // 判断 argv[4] 是否为 --spacenum=2
                    input_idx = 5;
                }
                // 否则保持默认
                
                process = (spaces == 2) ? 2 : 3;
            }
        }

        // 检查 input 是否存在
        if (input_idx >= argc) {
            std::cerr << "Error: missing input " << (mode == "str" ? "string" : "file path") << "\n" << JSON_USAGE << std::endl;
            return;
        }

        // 执行处理
        try {
            if (mode == "str") {
                std::string input = argv[input_idx];
                std::cout << json_str(input, process) << std::endl;
            } else {  // file
                fs::path filepath = argv[input_idx];
                json_file(filepath, process);
                std::cout << "File processed successfully: " << filepath << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    void cmd_uuid() {
        std::cout << uuid() << std::endl;
    }

    void cmd_update(const int ver[3]) {
        do_update(ver);
    }

    void cmd_time(int argc, char* argv[]) {
        show_time(argc, argv);
    }

}