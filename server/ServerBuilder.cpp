//
// Created by renier on 07/01/24.
//

#include "ServerBuilder.hpp"

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
    std::cout << "Checking dir " << path << "\n";
    char tryCount = 0;
    while (!fs::exists(path) && tryCount < 5) {
        try {
            fs::create_directories(path);
        }
        catch (std::exception& err) {
            std::cerr << err.what() << "\n";
            tryCount++;
        }
    }
    // could not create dir
    if (tryCount == 5) {
        std::stringstream ss;
        ss << "could not create file " << path;
        throw std::runtime_error(ss.str());
    }
}
} // vega