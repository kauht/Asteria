#pragma once

#include <format>
#include <fstream>
#include <mutex>
#include <string_view>
#include <chrono>

namespace asteria::util {

// Simple file logger. Thread-safe. Writes to asteria.log in the working directory.
class logger {
  public:
    logger() { file_.open("asteria.log", std::ios::out | std::ios::trunc); }
    ~logger() {
        if (file_.is_open()) file_.close();
    }

    void write(std::string_view msg, std::string_view level) {
        std::lock_guard lock(mutex_);
        if (!file_.is_open()) return;
        file_ << std::format("[{}] [{}] {}\n", timestamp(), level, msg);
        file_.flush();
    }

  private:
    std::ofstream file_;
    mutable std::mutex mutex_;

    static std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &time);
        return std::format("{:02}:{:02}:{:02}", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
};

inline logger& global_logger() {
    static logger instance;
    return instance;
}

inline void info(std::string_view msg) { global_logger().write(msg, "INFO"); }
inline void debug(std::string_view msg) { global_logger().write(msg, "DEBUG"); }
inline void error(std::string_view msg) { global_logger().write(msg, "ERROR"); }

// Convenience: log a formatted message directly.
// Usage: asteria::util::log("value = {}", 42);
template <typename... Args> inline void log(std::format_string<Args...> fmt, Args&&... args) { info(std::format(fmt, std::forward<Args>(args)...)); }

} // namespace asteria::util
