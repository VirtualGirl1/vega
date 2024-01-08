//
// Created by renier on 07/01/24.
//

#include <boost/json.hpp>
#include <iostream>
#include <sstream>

#include "ServerBuilder.hpp"
#include "SettingLoader.hpp"
#include "Log.hpp"

namespace json = boost::json;

vega::Log Logger;

int main(int argc, char** argv) {
    // place holder val
    json::value val;

    try {
        vega::Logger << "Starting VEGA\n";

        // load server builder
        vega::ServerBuilder builder;
        vega::SettingLoader config(builder.GetConfig());

        // get port
        val = config.GetSetting("Port");
        short port;
        switch (val.kind()) {
            case json::kind::int64:
                port = val.as_int64();
                break;
            case json::kind::uint64:
                port = val.as_uint64();
                break;
            default:
                throw std::runtime_error("Could not find option 'Port'");
        }
        builder.SetPort(port);
    }
    catch (std::exception& err) {
        vega::Logger.SetLogLevel(vega::LogLevel::LogError);
        std::stringstream ss;
        ss << err.what() << "\n";
        vega::Logger << ss.str();

    }

    return 0;
}


