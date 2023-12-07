#include "Logger.h"

Logger::Logger() {
    logging.open("TensorRT_logs.txt", std::ofstream::out);
}

Logger::~Logger() {
    logging.close();
}

inline void Logger::log(Severity severity, const char* msg) noexcept {
    if (severity <= Severity::kINFO) {
        CustomLog(msg);
    }
}
