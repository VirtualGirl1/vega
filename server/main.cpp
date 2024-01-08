//
// Created by renier on 07/01/24.
//

#include <iostream>
#include <sstream>

#include "ServerBuilder.hpp"
#include "Log.hpp"

vega::Log Logger;

int main(int argc, char** argv) {

    try {
        vega::Logger << "Starting VEGA\n";

        // load server builder
        vega::ServerBuilder builder;

    }
    catch (std::exception& err) {
        vega::Logger.SetLogLevel(vega::LogLevel::LogError);
        std::stringstream ss;
        ss << err.what() << "\n";
        vega::Logger << ss.str();

    }

    return 0;
}


