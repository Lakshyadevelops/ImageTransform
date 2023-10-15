#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <NvInfer.h>
#include <filesystem>

namespace Util {
    bool doesFileExist(const std::string& filepath);

    void checkCudaErrorCode(cudaError_t code);

    std::vector<std::string> getFilesInDirectory(const std::string& dirPath);
}

