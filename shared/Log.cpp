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
    if (!logFile.has_value()) {
        logFile = std::ofstream();
    }
    // open or create log file
    logFile->open(file);
    if (!logFile->is_open()) {
        std::stringstream ss;
        ss << "could not open file " << file;
        throw std::runtime_error(ss.str());
    }

}

std::string Log::TimeStamp() {
    time_t currentTime = std::time(nullptr);
    tm timeInfo{};
    timeInfo = *localtime(&currentTime);

    std::ostringstream outputStream;
    outputStream << std::put_time(&timeInfo, "%Y-%m-%d_%H-%M");
    return outputStream.str();
}

vega::Log Logger;

} // vega