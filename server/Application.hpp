//
// Created by renier on 08/01/24.
//

#pragma once

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

#include "VegaModule.hpp"

namespace vega {

// this is the actual application
// it handles the main process loop and all error handling
class Application {
private:
    boost::asio::io_service service;
    short port;

    // modules
    boost::shared_ptr<VegaModule> coreModule;
    std::vector<boost::shared_ptr<VegaModule>> extModules;

public:
    friend class ServerBuilder;

    Application();
    explicit Application(short p);

private:
    void SetCore(const std::string& path);
};

} // vega
