#include "client/client.h"
#include "utils/utils.h"
#include<iostream>

void printManifest(const std::vector<FileInfo>& files) {
    std::cout << "Server manifest (" << files.size() << " files):\n";
    for (const auto& f : files) {
        std::cout << "  - " << f.name << " (" << f.size << " bytes)\n";
    }
}

void syncAndUpdate(MSClient& client, const std::string& pathDir) {
    auto localManifest = getLocalManifest(pathDir);
    auto toUpdate = client.sync(localManifest);

    if (toUpdate.empty()) {
        return;
    }

    std::vector<std::string> filenames;
    for (const auto& [name, _] : toUpdate) {
        filenames.push_back(name);
    }

    if (client.downloadZipFile(filenames, pathDir)) {
        std::cout << "Downloaded via ZIP" << std::endl;
    } else {
        for (const auto& name : filenames) {
            client.downloadFile(name, pathDir);
            std::cout << "Downloaded: " << name << std::endl;
        }
    }
}

int main() {
    try {
        MSClient client("localhost", 8080);
        std::cout << "Health check: " << client.healthCheck() << std::endl << std::endl;

        auto files = client.getManifest();
        std::cout << std::endl;

        printManifest(files);

        syncAndUpdate(client, "../mods");

    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}