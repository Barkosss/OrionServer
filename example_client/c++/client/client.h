#pragma once

#include <map>
#include <memory>
#include <vector>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

struct FileInfo {
    std::string name;
    size_t size;
    std::string hash;
};

class MSClient {
    std::string host_;
    unsigned short port_;
    std::shared_ptr<asio::io_context> io_context_;
    std::shared_ptr<tcp::socket> socket_;

    http::response<http::string_body> sendRequest(const http::verb& method, const std::string& target, const std::string& body);

public:
    MSClient(const std::string& host, unsigned short port);
    ~MSClient();

    std::vector<FileInfo> getManifest();
    bool downloadFile(const std::string& filename, const std::string& saveDir);
    bool downloadZipFile(const std::vector<std::string>& filenames, const std::string &saveDir);
    std::string healthCheck();

    std::map<std::string, std::string> sync(const std::map<std::string, std::string>& clientFiles);
};