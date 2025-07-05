#include "FileLoader.h"
#include "Exception.h"
#include <fstream>
#include <string>

FileLoader::FileLoader(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw FileException(filename);
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }
    if (lines.empty()) {
        throw FormatException("file is empty or only blank lines");
    }
}

const std::vector<std::string>& FileLoader::getLines() const {
    return lines;
}
