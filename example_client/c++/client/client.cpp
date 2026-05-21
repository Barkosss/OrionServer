#include "client.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

bool extractZip(const std::string& zipPath, const std::string& destDir);

MSClient::MSClient(const std::string& host, unsigned short port)
    : host_(host), port_(port),
    io_context_(std::make_shared<asio::io_context>()),
    socket_(std::make_shared<tcp::socket>(*io_context_)) {
        tcp::resolver resolver(*io_context_);
        asio::connect(*socket_, resolver.resolve(host_, std::to_string(port_)));
};

MSClient::~MSClient() {
    socket_->close();
};

http::response<http::string_body> MSClient::sendRequest(const http::verb &method, const std::string &target, const std::string &body) {
    http::request<http::string_body> req;
    req.method(method);
    req.target(target);
    req.set(http::field::host, host_);
    req.set(http::field::content_type, "application/json");

    if (!body.empty()) {
        req.body() = body;
        req.set(http::field::content_length, std::to_string(body.size()));
    }

    http::write(*socket_, req);

    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(*socket_, buffer, res);

    return res;
}

std::vector<FileInfo> MSClient::getManifest() {
    auto res = sendRequest(http::verb::get, "/manifest", nlohmann::json{}.dump());

    if (res.result() != http::status::ok) {
        throw std::runtime_error("Failed to get manifest: " + res.body());
    }

    auto json = nlohmann::json::parse(res.body());
    std::vector<FileInfo> files;

    for (const auto& item : json["files"]) {
        FileInfo file;
        file.name = item["name"];
        file.size = item["size"];
        file.hash = item["hash"];
        files.push_back(file);
    }

    return files;
}

bool MSClient::downloadFile(const std::string& filename, const std::string& savePath) {
    std::string target = "/file/" + filename;
    auto res = sendRequest(http::verb::get, target, nlohmann::json{}.dump());
    
    if (res.result() != http::status::ok) {
        return false;
    }
    
    fs::path path(savePath);
    if (path.has_parent_path()) {
        fs::create_directories(path.parent_path());
    }
    
    std::ofstream file(savePath, std::ios::binary);
    file.write(res.body().data(), res.body().size());
    
    return true;
}

bool MSClient::downloadZipFile(const std::vector<std::string>& filenames, const std::string& saveDir) {
    nlohmann::json reqJson;
    reqJson["files"] = filenames;

    http::request<http::string_body> req;
    req.method(http::verb::get);
    req.target("/file");
    req.set(http::field::host, host_);
    req.set(http::field::content_type, "application/json");
    req.body() = reqJson.dump();
    req.prepare_payload();

    auto res = sendRequest(http::verb::get, "/file", reqJson.dump());

    if (res.result() != http::status::ok) {
        std::cout << "Zip download failed: " << res.body();
        return false;
    }

    fs::path tempZip = fs::path(saveDir) / ("temp_" + std::to_string(time(nullptr)) + ".zip");
    fs::create_directories(saveDir);

    std::ofstream ofs(tempZip, std::ios::binary);
    ofs.write(res.body().data(), res.body().size());
    ofs.close();

    bool success = extractZip(tempZip, saveDir);
    fs::remove(tempZip);

    if (!success) {
        std::cout << "Failed to extract zip" << std::endl;
        return false;
    }

    std::cout << "Successfully downloaded and extracted files: " << filenames.size() << std::endl;
    return true;
}

bool extractZip(const std::string& zipPath, const std::string& destDir) {
    #ifdef _WIN32
        std::string cmd = "powershell -Command \"Expand-Archive -Path " + zipPath + " -DestinationPath " + destDir + " -Force\"";
    #else
        std::string cmd = "unzip -o " + zipPath + " -d " + destDir;
    #endif
    return system(cmd.c_str()) == 0;
}

std::string MSClient::healthCheck() {
    auto res = sendRequest(http::verb::get, "/health", nlohmann::json{}.dump());
    
    if (res.result() == http::status::ok) {
        auto json = nlohmann::json::parse(res.body());
        return json.value("status", "unknown");
    }
    
    return "error";
}

std::map<std::string, std::string> MSClient::sync(const std::map<std::string, std::string>& clientFiles) {
    nlohmann::json reqJson;
    reqJson["files"] = clientFiles;
    reqJson["strategy"] = "full";

    auto res = sendRequest(http::verb::get, "/sync", reqJson.dump());

    if (res.result() != http::status::ok) {
        throw std::runtime_error("Sync failed: " + res.body());
    }

    auto resJson = nlohmann::json::parse(res.body());
    std::map<std::string, std::string> result;

    if (resJson.contains("files")) {
        for (const auto& file : resJson["files"]) {
            result[file] = file;
        }
    }

    return result;
}