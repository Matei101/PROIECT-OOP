#include "TimeUtils.h"
#include <chrono>
#include <ctime>
#include <sstream>

std::string TimeUtils::now() {
    auto t = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S",
                  std::localtime(&t));
    return buf;
}
