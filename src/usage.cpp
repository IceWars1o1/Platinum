#include "../include/usage.hpp"
#include <iostream>

namespace pt{
    void usage() {
        std::cout << "Usage:" << std::endl;
        std::cout << "\tplatinum <command> [options]" << std::endl;
        std::cout << std::endl;
        std::cout << "Commands:" << std::endl;
        std::cout << "\tmd5 <text>\t\tCalculate MD5 hash of text." << std::endl;
        std::cout << "\tbmi <height> <weight>\tCalculate BMI." << std::endl;
        std::cout << "\trandom [options]\tGenerate random number." << std::endl;
        std::cout << "\ttodo <subcommand>\tManage todo items." << std::endl;
        std::cout << "\tcase [options] <text>\tConvert text case." << std::endl;
        std::cout << "\tuuid\t\t\tGenerate a UUID(v1)." << std::endl;
        std::cout << "\tplaysound\t\tPlay a music by beeping." << std::endl;
    
        std::cout << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "\t-v, --version\t\tShow version." << std::endl;
        std::cout << "\t-h, --help\t\tShow this help message." << std::endl;
        std::cout << "\trandom options:" << std::endl;
        std::cout << "\t  --min\t\t\tMinimum value (default: 0)" << std::endl;
        std::cout << "\t  --max\t\t\tMaximum value (default: 100)" << std::endl;
        std::cout << "\ttodo subcommands:" << std::endl;
        std::cout << "\t  add <item>\t\tAdd a todo item." << std::endl;
        std::cout << "\t  list\t\t\tList all todo items." << std::endl;
        std::cout << "\t  remove\t\tRemove a todo item by number." << std::endl;
        std::cout << "\t  finish\t\tMark a todo item as [DONE] by numnber." << std::endl;
        std::cout << "\t  clear\t\t\tClear all todo items." << std::endl;
        std::cout << "\tcase subcommands:" << std::endl;
        std::cout << "\t  upper\t\t\tConvert to uppercase letters." << std::endl;
        std::cout << "\t  lower\t\t\tConvert to lowercase letters." << std::endl;
    }
    
    void version(const char* ver){
        std::cout << "Platinum Toolkit (R)" << std::endl;
        std::cout << "Made by IceWars1o1." << std::endl;
        std::cout << "Version " << ver << std::endl;
    }
}