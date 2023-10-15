#include "Logger.h"

Logger::Logger() {
    logging.open("TensorRT_logs.txt", std::ofstream::out);
}

Logger::~Logger() {
    logging.close();
}

void Logger::CustomLog(std::string str)
{
    logging << str << std::endl;
}

inline void Logger::log(Severity severity, const char* msg) noexcept {
    if (severity != Severity::kINFO) {
        CustomLog(msg);
    }
}
