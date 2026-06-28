#include "include/commands.hpp"
#include "include/usage.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>

const char* VERSION = "Alpha 26.1.0.062800A";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        pt::usage();
        return 0;
    }

    if (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version")) {
        pt::version(VERSION);
        return 0;
    }

    if (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help")) {
        pt::usage();
        return 0;
    }

    if (!std::strcmp(argv[1], "md5")) {
        pt::cmd_md5(argc, argv);
        return 0;
    }

    if (!std::strcmp(argv[1], "bmi")) {
        pt::cmd_bmi(argc, argv);
        return 0;
    }

    if (!std::strcmp(argv[1], "random")) {
        pt::cmd_random(argc, argv);
        return 0;
    }

    if (!std::strcmp(argv[1], "todo")) {
        pt::cmd_todo(argc, argv);
        return 0;
    }
    
    if (!std::strcmp(argv[1], "case")) {
        pt::cmd_case(argc, argv);
        return 0;
    }

    if (!std::strcmp(argv[1], "uuid")) {
        pt::cmd_uuid();
        return 0;
    }

    if (!std::strcmp(argv[1], "playsound")) {
        pt::beep_music();
        return 0;
    }

    std::cerr << "Unknown command: " << argv[1] << std::endl;
    pt::usage();
    return 1;
}