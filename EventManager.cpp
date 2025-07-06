#include "EventManager.h"
#include <algorithm>

EventManager::HandlerId EventManager::subscribe(const std::string& event, Handler h) {
    HandlerId id = nextId_++;
    handlers_[event].push_back({id, std::move(h)});
    return id;
}

void EventManager::unsubscribe(const std::string& event, HandlerId id) {
    auto it = handlers_.find(event);
    if (it == handlers_.end()) return;
    auto& vec = it->second;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [id](auto& e){ return e.id == id; }),
        vec.end());
}

void EventManager::publish(const std::string& event, const std::string& data) const {
    auto it = handlers_.find(event);
    if (it == handlers_.end()) return;
    for (auto& e : it->second) {
        e.fn(data);
    }
}
