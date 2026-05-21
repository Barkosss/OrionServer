#include "utils.h"
#include <fstream>
#include <filesystem>
#include<ctime>

namespace fs = std::filesystem;

std::string computeFileHash(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) return "";

    std::srand(std::time(nullptr));
    int random_value = std::rand();

    return std::to_string(random_value);
    
    // MD5_CTX md5Context;
    // MD5_Init(&md5Context);
    
    // char buffer[4096];
    // while (file.read(buffer, sizeof(buffer))) {
    //     MD5_Update(&md5Context, buffer, file.gcount());
    // }
    // MD5_Update(&md5Context, buffer, file.gcount());
    
    // unsigned char hash[MD5_DIGEST_LENGTH];
    // MD5_Final(hash, &md5Context);
    
    // std::stringstream ss;
    // for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
    //     ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    // }
    
    // return ss.str();
}

std::map<std::string, std::string> getLocalManifest(const std::string& gameDir) {
    std::map<std::string, std::string> manifest;
    
    if (!fs::exists(gameDir)) return manifest;
    
    for (const auto& entry : fs::recursive_directory_iterator(gameDir)) {
        if (entry.is_regular_file()) {
            std::string relPath = fs::relative(entry.path(), gameDir).string();
            manifest[relPath] = computeFileHash(entry.path().string());
        }
    }
    
    return manifest;
}