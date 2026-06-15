#include "../include/todo.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>

namespace pt {

    static std::string get_config_dir() {
        const char* home = std::getenv("HOME");
        if (!home) home = ".";
        return std::string(home) + "/.config/platinum";
    }
    
    static void create_config_dir() {
        std::string dir = get_config_dir();
        std::string cmd = "mkdir -p " + dir + " 2>/dev/null";
        std::system(cmd.c_str());
    }
    
    std::string get_todo_file() {
        return get_config_dir() + "/todo.txt";
    }
    
    bool is_number(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }
    
    void todo_add(const std::string& item) {
        create_config_dir();
        std::ofstream out(get_todo_file(), std::ios::app);
        if (!out) {
            std::cerr << "Error: Cannot open todo file" << std::endl;
            return;
        }
        out << item << std::endl;
        out.close();
        std::cout << "Added: " << item << std::endl;
    }
    
    void todo_list() {
        std::ifstream in(get_todo_file());
        if (!in) {
            std::cout << "No todo items." << std::endl;
            return;
        }
        std::string line;
        int num = 1;
        while (std::getline(in, line)) {
            std::cout << num++ << ". " << line << std::endl;
        }
        in.close();
    }
    
    void todo_remove_interactive() {
        std::ifstream in(get_todo_file());
        std::vector<std::string> lines;
        std::string line;
        
        if (!in) {
            std::cout << "No todo items." << std::endl;
            return;
        }
        while (std::getline(in, line)) {
            lines.push_back(line);
        }
        in.close();
        
        if (lines.empty()) {
            std::cout << "No todo items." << std::endl;
            return;
        }
        
        for (size_t i = 0; i < lines.size(); i++) {
            std::cout << i + 1 << ". " << lines[i] << std::endl;
        }
        
        std::cout << "Enter number to remove (0 to cancel): ";
        std::string input;
        std::cin >> input;
        
        if (!is_number(input)) {
            std::cout << "Cancelled." << std::endl;
            return;
        }
        
        int n = std::stoi(input);
        if (n <= 0 || n > (int)lines.size()) {
            std::cout << "Cancelled." << std::endl;
            return;
        }
        
        std::string removed = lines[n - 1];
        lines.erase(lines.begin() + (n - 1));
        
        std::ofstream out(get_todo_file(), std::ios::trunc);
        if (!out) {
            std::cerr << "Error: Cannot write todo file" << std::endl;
            return;
        }
        for (const std::string& l : lines) {
            out << l << std::endl;
        }
        out.close();
        
        std::cout << "Removed: " << removed << std::endl;
    }
    
    void todo_clear() {
        std::ofstream out(get_todo_file(), std::ios::trunc);
        if (!out) {
            std::cerr << "Error: Cannot clear todo file" << std::endl;
            return;
        }
        out.close();
        std::cout << "All todo items cleared." << std::endl;
    }

}