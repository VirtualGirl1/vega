//
// Created by renier on 08/01/24.
//

#include "Log.hpp"

#include <iomanip>

namespace vega {
Log::Log(LogLevel level) {
    logLevel = level;
    logMode = LogMode::LogConsole;
}

void Log::SetLogLevel(vega::LogLevel level) {
    logLevel = level;
}

void Log::SetLogMode(LogMode mode) {
    logMode = mode;

}

void Log::SetLogFile(const std::string& file) {
    // open or create log file
    logFile->open(file);
    if (!logFile->is_open()) {
        std::stringstream ss;
        ss << "could not open file " << file;
        throw std::runtime_error(ss.str());
    }

}

std::string Log::TimeStamp() {
    auto timeStamp = std::time(nullptr);
    tm time_info{};
    std::ostringstream output_stream;
    output_stream << std::put_time(&time_info, "%Y-%m-%d_%H-%M");
    return output_stream.str();
}

vega::Log Logger;

} // vega