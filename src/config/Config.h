//
// Created by Andrey Baryshev on 02.05.2026.
//

#ifndef MSBackend_CONFIG_H
#define MSBackend_CONFIG_H

#include<map>
#include<string>
#include<fstream>

using std::map;
using std::string;
using std::fstream;

enum class ConfigMode {
    AllowList,
    BlockList
};

class Config {
private:
    Config();
    ~Config() = default;

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    ConfigMode mode;
    string mods_directory = "./mods";
    map<string, string> client_server_files;
    map<string, string> client_only_files;
    map<string, string> server_only_files;
    map<string, string> blacklist_files;

    void loadFromFile(const std::string& filename);

public:
    static Config& getInstance();

    static void reload(const string &filename = "config.json");

    ConfigMode getMode() const { return mode; }
    const std::string& getModsDir() const { return mods_directory; }
    const map<string, string>& getClientServerFiles() const { return client_server_files; }
    const map<string, string>& getClientOnlyFiles() const { return client_only_files; }
    const map<string, string>& getServerOnlyFiles() const { return server_only_files; }
    const map<string, string>& getBlacklistFiles() const { return blacklist_files; }

    bool isAllowList() const {
        return mode == ConfigMode::AllowList;
    }

    bool isBlockList() const {
        return mode == ConfigMode::BlockList;
    }

    bool shouldSendToClient(const std::string& filename) const;
};

#endif //MSBackend_CONFIG_H
