#pragma once
#include<NvInfer.h>
#include <fstream>

class Logger : public nvinfer1::ILogger {
public:
    std::ofstream logging;

    Logger();

    ~Logger();

    void CustomLog(std::string str);

    void log(Severity severity, const char* msg) noexcept override;
};