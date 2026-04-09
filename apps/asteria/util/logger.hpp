#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <filesystem>
#include <sstream>
#include <ctime>

namespace asteria::util {

enum class log_level : int { OFF = 0, ERROR = 1, INFO = 2, DEBUG = 3 };

class logger {
public:
    logger() : path_("asteria.log") {
        file_.open(path_, std::ios::out | std::ios::trunc);
    }

    logger(const std::string& path, log_level level = log_level::INFO) {
        path_ = path;
        file_.open(path_, std::ios::out | std::ios::trunc);
    }

    ~logger() {
        std::lock_guard<std::mutex> lk(mutex_);
        if (file_.is_open()) {
            file_.flush();
            file_.close();
        }
    }

    bool open(const std::string& path) {
        std::lock_guard<std::mutex> lk(mutex_);

        path_ = path;

        std::filesystem::path p(path_);

        file_.open(path_, std::ios::out | std::ios::trunc);

        if (!file_.is_open()) {
            return false;
        }

        return true;
    }

    void close() {
        std::lock_guard<std::mutex> lk(mutex_);
        if (file_.is_open()) {
            file_.close();
        }
    }

    bool is_open() const {
        std::lock_guard<std::mutex> lk(mutex_);
        return file_.is_open();
    }

    void write(const std::string& msg, log_level level) {
        std::lock_guard<std::mutex> lk(mutex_);
        if (level == log_level::OFF) {
            return;
        }

        if (!file_.is_open()) {
            return;
        }

        file_ << '[' << timestamp_locked() << "] ";
        file_ << '[' << level_to_string(level) << "] ";
        file_ << msg << '\n';
        file_.flush();
    }

private:
    std::ofstream file_;
    std::string path_;
    mutable std::mutex mutex_;

    static const char* level_to_string(log_level lvl) {
        switch (lvl) {
            case log_level::ERROR: return "ERROR";
            case log_level::INFO:  return "INFO";
            case log_level::DEBUG: return "DEBUG";
            case log_level::OFF:   return "OFF";
            default:               return "UNKNOWN";
        }
    }

    static std::string timestamp_locked() {
        using namespace std::chrono;
        auto now = system_clock::now();
        std::time_t t = system_clock::to_time_t(now);

        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif

        std::ostringstream ss;
        ss << std::put_time(&tm, "%H:%M:%S");
        return ss.str();
    }
};

inline logger& global_logger() {
    static logger instance;
    return instance;
}


inline void info(const std::string& msg)  { global_logger().write(msg, log_level::INFO);  }
inline void debug(const std::string& msg) { global_logger().write(msg, log_level::DEBUG); }
inline void error(const std::string& msg) { global_logger().write(msg, log_level::ERROR); }

} // namespace asteria::util
