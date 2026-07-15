#include "include/commands.hpp"
#include "include/usage.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

const char* VERSION = "Alpha 26.1.0.071500A";
const int VERSION_TAG[3] = {0, 3, 0};

static int dispatch(int argc, char* argv[]) {
    if (argc < 2) {
        pt::usage();
        return 0;
    }

    const char* cmd = argv[1];

    if (!std::strcmp(cmd, "-v") || !std::strcmp(cmd, "--version")) {
        pt::version(VERSION);
        return 0;
    }
    if (!std::strcmp(cmd, "-h") || !std::strcmp(cmd, "--help")){
        pt::usage();
        return 0;
    }
    if (!std::strcmp(cmd, "md5"))      { pt::cmd_md5(argc, argv);     return 0; }
    if (!std::strcmp(cmd, "random"))   { pt::cmd_random(argc, argv);  return 0; }
    if (!std::strcmp(cmd, "todo"))     { pt::cmd_todo(argc, argv);    return 0; }
    if (!std::strcmp(cmd, "uuid"))     { pt::cmd_uuid();              return 0; }
    if (!std::strcmp(cmd, "update"))   { pt::cmd_update(VERSION_TAG); return 0; } 
    if (!std::strcmp(cmd, "time"))     { pt::cmd_time(argc, argv);    return 0; }

    std::cerr << "Unknown command: " << cmd << std::endl;
    pt::usage();
    return 1;
}

static std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::string cur;
    bool inQuotes = false;
    for (char c : line) {
        if (c == '"') { inQuotes = !inQuotes; continue; }
        if (c == ' ' && !inQuotes) {
            if (!cur.empty()) { tokens.push_back(cur); cur.clear(); }
        } else {
            cur += c;
        }
    }
    if (!cur.empty()) tokens.push_back(cur);
    return tokens;
}

static void interactive_terminal() {
    std::cout << "Platinum Toolkit (R) - Interactive Mode\n"
              << "  Version " << VERSION << "\n"
              << "  Made by IceWars1o1.\n\n"
              << "Type 'help' for commands, 'exit' to quit.\n\n";

    std::string line;
    while (std::cout << "PLATINUM > " && std::getline(std::cin, line)) {
        auto tokens = tokenize(line);
        if (tokens.empty()) continue;

        const std::string& cmd = tokens[0];

        if (!cmd.empty() && cmd[0] == '-') {
            std::cerr << "Unknown command: " << cmd << std::endl;
            std::cout << "\n";
            continue;
        }

        if (cmd == "exit" || cmd == "quit") {
            break;
        }
        if (cmd == "help") {
            pt::usage();
            std::cout << "\n";
            continue;
        }
        if (cmd == "version") {
            pt::version(VERSION);
            std::cout << "\n";
            continue;
        }

        std::vector<char*> argv;
        argv.push_back(const_cast<char*>("platinum"));
        for (auto& t : tokens) argv.push_back(const_cast<char*>(t.c_str()));
        argv.push_back(nullptr);

        dispatch(static_cast<int>(argv.size()) - 1, argv.data());
        std::cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        interactive_terminal();
        return 0;
    }
    return dispatch(argc, argv);
}