#include "Util.h"


bool Util::doesFileExist(const std::string& filepath) {
    std::ifstream f(filepath.c_str());
    return f.good();
}

void Util::checkCudaErrorCode(cudaError_t code) {
    if (code != 0) {
        std::string errMsg = "CUDA operation failed with code: " + std::to_string(code) + "(" + cudaGetErrorName(code) + "), with message: " + cudaGetErrorString(code);
        std::cout << errMsg << std::endl;
        throw std::runtime_error(errMsg);
    }
}

std::vector<std::string> Util::getFilesInDirectory(const std::string& dirPath) {
    std::vector<std::string> filepaths;
    for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        filepaths.emplace_back(entry.path().string());
    }
    return filepaths;
}
