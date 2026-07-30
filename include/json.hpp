#pragma once
#include "third_party/json.hpp"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace pt{
    inline const char* JSON_USAGE = R"(
Usage: filename json <str|file> <minify|format> [--spacenum=<2|4>] <input>

Commands:
  str          Process a JSON string directly
  file         Process a JSON file (path provided as input)

Subcommands:
  minify       Output compact JSON (no whitespace)
  format       Pretty-print JSON with indentation

Options:
  --spacenum=2  Indent with 2 spaces (default for format)
  --spacenum=4  Indent with 4 spaces

Arguments:
  input        JSON string (for 'str') or file path (for 'file')

Examples:
  platinum json str minify '{"a": 1}'
  platinum json str format --spacenum=4 '{"a": 1}'
  platinum json file format /path/to/file.json
  platinum json file minify /path/to/file.json
)";

    int parse_spacenum(const char* arg, int default_val = 2);
    std::string json_str(std::string input, int process);
    void json_file(fs::path file, int process);
    void json_usage();
}