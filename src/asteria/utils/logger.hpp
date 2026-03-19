#include <string>
#include <string_view>
#include <fstream>
#include <chrono>

namespace asteria::util {

enum class log_level : int { OFF = 0, ERROR = 1, INFO = 2, DEBUG = 3 };

class logger {
public:

    logger() : file_(std::ofstream("asteria.log")), level_(log_level::INFO) {}
    logger(const std::string& path, log_level level = log_level::INFO) : file_(std::ofstream(path)), level_(level) {}
    ~logger() {file_.close();}
    void open() {

    }

    void write(const std::string& msg, log_level level) {
        if (!file_.is_open()) return;
        file_ << '[' << timestamp() << "] ";
        file_ << '[' << level_to_string(level) << "] ";
        file_ << msg << std::endl;
    }


private:
    log_level level_{};
    std::ofstream file_{};

    const char* level_to_string(log_level lvl) {
        switch (lvl) {
            case log_level::ERROR: return "ERROR";
            case log_level::INFO:  return "INFO";
            case log_level::DEBUG: return "DEBUG";
            default:               return "UNKNOWN";
        }
    }

    static std::string timestamp() {
        std::chrono::time_point now = std::chrono::system_clock::now();

        return
    }

};

inline logger g_logger;

void info(const std::string& msg)  { g_logger.write(msg, log_level::INFO);  }
void debug(const std::string& msg) { g_logger.write(msg, log_level::DEBUG); }
void error(const std::string& msg) { g_logger.write(msg, log_level::ERROR); }

} // namespace asteria::util
