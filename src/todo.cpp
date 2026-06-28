#include "../include/todo.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>

namespace pt {

    static fs::path get_config_dir() {
        wchar_t path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, path))) {
            return fs::path(path);
        }
        return fs::current_path();
    }

    static void create_config_dir(){
        fs::path pa = get_config_dir();
        if (fs::create_directory(pa / "platinum")){
            std::ofstream file(pa / "platinum" / "todo.log");
            if (file.is_open()){
                file << "Create Successfully\n";
                file.close();
            }
        }
    }
    
    fs::path get_todo_file() {
        return get_config_dir() / "platinum" / "todo.txt";
    }
    
    bool is_number(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }
    
    static bool is_done(const std::string& line) {
        return line.find("[DONE]") != std::string::npos;
    }
    
    static std::string mark_done(const std::string& line) {
        if (is_done(line)) return line;
        return "[DONE]\t" + line;
    }
    
    static void print_line(int num, const std::string& line) {
        if (is_done(line)) {
            std::cout << "[D] " << num << ". " << line.substr(line.find('\t') + 1) << std::endl;
        } else {
            std::cout << "[ ] " << num << ". " << line << std::endl;
        }
    }
    
    void todo_add(const std::string& item) {
        if (!fs::exists(get_config_dir() / "platinum")) create_config_dir();
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
            print_line(num++, line);
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
            print_line(i + 1, lines[i]);
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
    
    void todo_done_interactive() {
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
            print_line(i + 1, lines[i]);
        }
        
        std::cout << "Enter number to mark done (0 to cancel): ";
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
        
        if (is_done(lines[n - 1])) {
            std::cout << "Already done." << std::endl;
            return;
        }
        
        lines[n - 1] = mark_done(lines[n - 1]);
        
        std::ofstream out(get_todo_file(), std::ios::trunc);
        if (!out) {
            std::cerr << "Error: Cannot write todo file" << std::endl;
            return;
        }
        for (const std::string& l : lines) {
            out << l << std::endl;
        }
        out.close();
        
        std::cout << "Marked as done." << std::endl;
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