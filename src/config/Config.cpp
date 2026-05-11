//
// Created by Andrey Baryshev on 02.05.2026.
//

#include "Config.h"
#include<nlohmann/json.hpp>
#include "../utils/logger/Logger.h"

namespace fs = std::filesystem;

Config::Config() : mode(ConfigMode::AllowList) {
    loadFromFile("config.json");    
}

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

void Config::reload(const string& filename) {
    getInstance().loadFromFile(filename);
}

void Config::loadFromFile(const string& filename) {
    try {
        std::ifstream configFile(filename);

        if (!configFile.is_open()) {
            Logger::error("Config file not found: {}", filename);
            Logger::info("Using default configuration");
            return;
        }

        nlohmann::json json = nlohmann::json::parse(configFile);

        mode = ConfigMode::AllowList;
        client_server_files.clear();
        client_only_files.clear();
        server_only_files.clear();
        blacklist_files.clear();

        if (json.contains("mode")) {
            std::string modeStr = json["mode"];
            std::transform(modeStr.begin(), modeStr.end(), modeStr.begin(), ::tolower);
            if (modeStr == "allowlist") {
                mode = ConfigMode::AllowList;
            } else {
                mode = ConfigMode::BlockList;
            }
        }

        if (json.contains("mods_directory")) {
            mods_directory = json["mods_directory"];
            
            fs::path modsPath(mods_directory);
            if (modsPath.is_relative()) {
                fs::path exePath = fs::current_path();
                modsPath = exePath / modsPath;
                mods_directory = modsPath.string();
                Logger::debug("Resolved mods directory to: {}", mods_directory);
            }
        }

        if (json.contains("client_server") && json["client_server"].is_array()) {
            for (std::string mod : json["client_server"]) {
                client_server_files[mod] = "";
            }
        }

        if (json.contains("client_only") && json["client_only"].is_array()) {
            for (std::string mod : json["client_only"]) {
                client_only_files[mod] = "";
            }
        }

        if (json.contains("server_only") && json["server_only"].is_array()) {
            for (std::string mod : json["server_only"]) {
                server_only_files[mod] = "";
            }
        }

        if (json.contains("blacklist") && json["blacklist"].is_array()) {
            for (std::string mod : json["blacklist"]) {
                blacklist_files[mod] = "";
            }
        }

        Logger::info("Config loaded successfully from: {}", filename);

    } catch (const nlohmann::json::exception& ex) {
        Logger::error("Failed to parse config file: {}", ex.what());
    }
}

bool Config::shouldSendToClient(const std::string& filename) const {

    if (blacklist_files.find(filename) != blacklist_files.end()) {
        return false;
    }

    if (mode == ConfigMode::AllowList) {
        Logger::debug("AllowList:");
        Logger::debug("filename: {}", filename);
        Logger::debug("client_only: {}", client_only_files.find(filename) != client_only_files.end());
        Logger::debug("client_server: {}", client_server_files.find(filename) != client_server_files.end());
        
        // AllowList: Send client/client+server files
        return (client_only_files.find(filename) != client_only_files.end()) ||
                (client_server_files.find(filename) != client_server_files.end());
    } else {
        Logger::debug("BlockList:");
        Logger::debug("filename: {}", filename);
        Logger::debug("server_only: {}", server_only_files.find(filename) == server_only_files.end());
        
        // BlockList: Send all, except server files
        return (server_only_files.find(filename) == server_only_files.end());
    }
}