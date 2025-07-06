#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <functional>
#include <string>
#include <map>
#include <vector>

class EventManager {
public:
    using HandlerId = size_t;
    using Handler   = std::function<void(const std::string&)>;

    HandlerId subscribe(const std::string& event, Handler h);
    void unsubscribe(const std::string& event, HandlerId id);
    void publish(const std::string& event, const std::string& data) const;

private:
    struct Entry { HandlerId id; Handler fn; };
    std::map<std::string, std::vector<Entry>> handlers_;
    HandlerId nextId_ = 1;
};

#endif // EVENTMANAGER_H
