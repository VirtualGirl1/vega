//
// Created by renier on 07/01/24.
//

#pragma once

#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include "Application.hpp"

namespace vega {


// this is a class that builds the VEGA server and handles its destruction
// this object should not be destroyed as long as the server is needed or
// running
class ServerBuilder {
    // path to '.vega' directory
    boost::filesystem::path vegaPath;
    // paths to '.vega/config' and '.vega/modules'
    boost::filesystem::path configPath;
    boost::filesystem::path modPath;
    // config file
    boost::filesystem::path vegaConfig;


    // build settings
    short serverPort;

    std::string corePath;
    std::vector<std::string> extPaths;

    Application* app;
public:
    ServerBuilder();
    ~ServerBuilder();

    std::string GetConfig();
    Application& Build();

    // setters
    void SetPort(short port);

    void SetCore(const std::string& path);
    void AddExt(const std::string& modPath);

private:
    void ValidatePaths();
    static void ValidateDir(const boost::filesystem::path& path);
    static void ValidateFile(const std::string& path);
};

} // vega
