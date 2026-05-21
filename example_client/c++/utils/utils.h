#pragma once

#include<string>
#include<map>

std::string computeFileHash(const std::string& filepath);
std::map<std::string, std::string> getLocalManifest(const std::string& gameDir);