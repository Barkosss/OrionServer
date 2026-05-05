//
// Created by Andrey Baryshev on 04.05.2026.
//
#include "manifest_handler.h"
#include<map>
#include<nlohmann/json.hpp>
#include<vector>
#include<fstream>
#include "../config/Config.h"
#include "../utils/logger/Logger.h"

using std::map;
using std::string;
using std::vector;

bool _getFileStream(vector<string> reqFiles, map<string, std::fstream> &files);

void handleFile(const HttpRequest& req, HttpResponse& res) {
    try {
        nlohmann::json jsonBody(req.body());
        vector<string> reqFiles;
        if (jsonBody.contains("files") && jsonBody["files"].is_array()) {
            reqFiles = vector<string>(jsonBody["files"]);
        } else {
            res.body() = nlohmann::json({"error", "Request require list of filenames"}).dump();
            res.result(http::status::bad_request);
            return;
        }

        map<string, std::fstream> files;
        bool isAll = _getFileStream(reqFiles, files);
        nlohmann::json fileBody;
        for (string filename : reqFiles) {
            if (files.find(filename) == files.end()) {
                continue;
            }

            std::string data((std::istreambuf_iterator<char>(files[filename])), std::istreambuf_iterator<char>());
            fileBody[filename] = data;
        }
        
        res.body() = fileBody.dump();
        res.set(http::field::content_type, "application/octet-stream");
        res.result(((isAll) ? (http::status::ok) : (http::status::partial_content)));

    } catch (std::exception& ex) {
        Logger::error("Failed to send response: ", ex.what());
    }
}

bool _getFileStream(vector<string> reqFiles, map<string, std::fstream> &files) {
    string modsDir = Config::getInstance().getModsDir();
    bool fIsAll = true;

    for (string filename : reqFiles) {
        if (Config::getInstance().shouldSendToClient(filename)) {
            files[filename] = std::fstream(modsDir + filename);
        } else {
            fIsAll = false;
        }
    }

    return fIsAll;
}
