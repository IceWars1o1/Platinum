#include "../include/commands.hpp"
#include "../include/md5.hpp"
#include "../include/random.hpp"
#include "../include/todo.hpp"
#include "../include/uuid.hpp"
#include "../include/usage.hpp"
#include "../include/update.hpp" 
#include "../include/showtime.hpp"
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