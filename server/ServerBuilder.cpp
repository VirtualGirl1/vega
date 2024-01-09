//
// Created by renier on 07/01/24.
//

#include "ServerBuilder.hpp"
#include "Log.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = boost::filesystem;

namespace vega {

ServerBuilder::ServerBuilder() {
#ifdef DEBUG
    vegaPath = fs::path(PROJECT_DIR) / ".vega";
#else
    vegaPath = fs::path(std::getenv("HOME")) / ".vega";
#endif
    configPath = vegaPath / "config";
    modPath = vegaPath / "modules";

    vegaConfig = configPath / "vega.json";

    ValidatePaths();

    // set default values
    serverPort = 0;
    app = nullptr;
}

ServerBuilder::~ServerBuilder() {
    delete app;
}

std::string ServerBuilder::GetConfig() {
    return vegaConfig.string();
}

Application& ServerBuilder::Build() {

    if (serverPort == 0) {
        throw std::runtime_error("Server port not set");
    }

    app = new Application();
    app->port = serverPort;

    // load modules


    return *app;
}

void ServerBuilder::SetPort(short port) {
    if (port < 1023) {
        throw std::runtime_error("cannot use system port");
    }
    serverPort = port;
}

void ServerBuilder::SetCore(const std::string& path) {

    ValidateFile(path);
    corePath = path;
}

void ServerBuilder::AddExt(const std::string &modPath) {
    ValidateFile(modPath);
    extPaths.push_back(modPath);
}

void ServerBuilder::ValidatePaths() {
    // validate vegaPath
    ValidateDir(vegaPath);
    ValidateDir(configPath);
    ValidateDir(modPath);

    // check config file
    if (!fs::exists(vegaConfig)) {
        std::ofstream vc(vegaConfig.string());
        vc << "{}";
        vc.close();
    }
    if (fs::is_directory(vegaConfig)) {
        std::stringstream ss;
        ss << vegaConfig << " is a directory. Please rename or delete it";
        throw std::runtime_error(ss.str());
    }
}

void ServerBuilder::ValidateDir(const fs::path &path) {
    std::stringstream ss;
    ss << "Checking dir " << path << "\n";
    Logger << ss.str();
    ss.str(std::string());
    char tryCount = 0;
    while (!fs::exists(path) && tryCount < 5) {
        try {
            fs::create_directories(path);
        }
        catch (std::exception& err) {
            ss << err.what() << "\n";
            Logger << ss.str();
            ss.str(std::string());
            tryCount++;
        }
    }
    // could not create dir
    if (tryCount == 5) {

        ss << "could not create file " << path;
        throw std::runtime_error(ss.str());
    }
}

void ServerBuilder::ValidateFile(const std::string &path) {
    // validate file
    if (!fs::exists(path)) {
        std::stringstream ss;
        ss << "Could not find file '" << path << "'";
        throw std::runtime_error(ss.str());
    }

    if (fs::is_directory(path)) {
        std::stringstream ss;
        ss << "'" << path << "' is a directory";
        throw std::runtime_error(ss.str());
    }
}

} // vega