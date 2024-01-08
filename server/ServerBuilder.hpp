//
// Created by renier on 07/01/24.
//

#pragma once

#include <boost/filesystem.hpp>

namespace vega {

class ServerBuilder {
    // path to '.vega' directory
    boost::filesystem::path vegaPath;
    // paths to '.vega/config' and '.vega/modules'
    boost::filesystem::path configPath;
    boost::filesystem::path modPath;

    // config file
    boost::filesystem::path vegaConfig;
public:
    ServerBuilder();

private:
    void ValidatePaths();
    static void ValidateDir(const boost::filesystem::path& path);
};

} // vega