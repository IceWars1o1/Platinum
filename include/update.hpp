#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace pt {

    struct VersionInfo {
        std::string version_name;
        int tag[3];  // [major, minor, patch]
        std::vector<std::pair<std::string, std::string>> changes;
    };

    fs::path get_update_dir();
    fs::path get_update_bat_path();
    fs::path get_temp_download_path();
    fs::path get_current_exe_path();
    std::string http_get(const std::string& url);
    std::vector<VersionInfo> parse_changelog(const std::string& json_str);
    VersionInfo get_latest_version(const std::string& json_str);
    bool is_newer_version(const int remote[3], const int local[3]);
    bool download_file(const std::string& url, const fs::path& dest);
    void run_update_script(const fs::path& new_exe, const fs::path& current_exe);
    void do_update(const int ver[3]);

}