#include <iostream>
#include <string>
#include <chrono>
#include <iomanop>

enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug
};

class Logger {
public:
    void log(const std::string& message, LogLevel level = LogLevel::Info) {
        auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);
        std::cout << "[" << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S") << "] "
                  << toString(level) << ": " << message << std::endl;
    }

private:
    std::string toString(LogLevel level) {
        switch (level) {
            case LogLevel::Error: return "ERROR";
            case LogLevel::Warning: return "WARNING";
            case LogLevel::Info: return "INFO";
            case LogLevel::Debug: return "DEBUG";
            default: return "UNKNOWN";
        }
    }
};

