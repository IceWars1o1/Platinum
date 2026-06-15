#pragma once
#include <string>
#include <vector>

namespace pt {

    std::string get_todo_file();
    void todo_add(const std::string& item);
    void todo_list();
    void todo_remove_interactive();
    void todo_clear();
    bool is_number(const std::string& s);
    
}