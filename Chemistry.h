#ifndef CHEMISTRY_H
#define CHEMISTRY_H

#include <string>
#include <map>

class Chemistry {
public:
    void recordResult(const std::string& team, bool win);
    double getModifier(const std::string& team) const;
private:
    std::map<std::string,int> form;
};

#endif // CHEMISTRY_H
