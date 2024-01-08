//
// Created by renier on 07/01/24.
//

#pragma once


#include <boost/json.hpp>
#include <fstream>
#include <string>

namespace vega {

/*
 * Loads settings from a json file
 * primarily used for main settings but can be used by
 * individual modules for their configs
 */
class SettingLoader {
private:
    boost::json::object settings;

public:
    explicit SettingLoader(const std::string& configPath);

    boost::json::value GetSetting(const std::string& opt);
private:
    // private methods
    static boost::json::object Parse(std::ifstream& file);
};

} // vega
