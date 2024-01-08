//
// Created by renier on 08/01/24.
//

#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <ctime>

namespace vega {

enum class LogMode {
    LogFile,
    LogConsole
};

enum class LogLevel {
    LogError,
    LogInfo,
    LogWarning,
    LogDebug
};

class Log {
public:
    explicit Log(LogLevel level = LogLevel::LogDebug);
    explicit Log(Log& other) = delete;

    void SetLogLevel(LogLevel level);
    void SetLogMode(LogMode mode);

    void SetLogFile(const std::string& file);

    template <typename T>
    Log& operator<<(T const& value) {

        // create timestamp
       std::string ts = TimeStamp();
       buffer << ts << ": ";

       switch (logLevel) {
           case LogLevel::LogError:
               buffer << "Error: ";
               break;
           case LogLevel::LogInfo:
               buffer << "Info: ";
               break;
           case LogLevel::LogWarning:
               buffer << "Warning: ";
               break;
           case LogLevel::LogDebug:
               buffer << "Debug: ";
               break;
       }
       buffer << value;

       switch (logMode) {

           case LogMode::LogFile: {
               std::lock_guard<std::mutex> lock(fileLock);
               logFile.value() << buffer.str();
               break;
           }
           case LogMode::LogConsole:
               switch (logLevel) {
                   case LogLevel::LogError:
                       std::cerr << buffer.str();
                       break;
                   case LogLevel::LogWarning:
                       std::cout << "\033[1;33" << buffer.str() << "\033[0m";
                       break;
                   default:
                       std::cout << buffer.str();
                       break;
               }
               break;
       }
       // clear buffer
       buffer.str(std::string());

       return *this;
    }
private:
    static std::string TimeStamp();

    LogLevel logLevel;
    LogMode logMode;

    std::mutex fileLock;
    std::optional<std::ofstream> logFile;
    std::stringstream buffer;
    std::string logPath;

};

extern Log Logger;

} // vega
