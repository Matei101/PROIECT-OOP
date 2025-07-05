#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>

class FileLoader {
public:
    explicit FileLoader(const std::string& filename);
    const std::vector<std::string>& getLines() const;
private:
    std::vector<std::string> lines;
};

#endif // FILELOADER_H
