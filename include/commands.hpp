#pragma once
#include <string>

namespace pt {
    std::string join_args(int argc, char* argv[], int start);
    void cmd_md5(int argc, char* argv[]);
    void cmd_random(int argc, char* argv[]);
    void cmd_todo(int argc, char* argv[]);
    void cmd_json(int argc, char* argv[]);
    void cmd_uuid();
    void cmd_update(const int ver[3]);
    void cmd_time(int argc, char* argv[]);
}