//
// Created by renier on 07/01/24.
//

#include "SettingLoader.hpp"

#include <boost/filesystem.hpp>
#include <sstream>

namespace fs = boost::filesystem;
namespace json = boost::json;

namespace vega {
SettingLoader::SettingLoader(const std::string& configPath) {
    // ensure configPath is valid
    if (!fs::exists(configPath)) {
        std::stringstream ss;
        ss << "could not find file '" << configPath << "'";
        throw std::runtime_error(ss.str());
    }
    if (fs::is_directory(configPath)) {
        std::stringstream ss;
        ss << "path '" << configPath << "' is a directory";
        throw std::runtime_error(ss.str());
    }

    // open file
    std::ifstream config;
    config.open(configPath);

    settings = Parse(config);

}

json::value SettingLoader::GetSetting(const std::string& opt) {
    json::value ret = nullptr;
    if (settings.contains(opt)) {
        ret = settings.at(opt);
    }

    return ret;
}

json::object SettingLoader::Parse(std::ifstream& file) {

    json::stream_parser p;
    json::error_code ec;

    do {
        char buff[4096];
        file.read(buff, sizeof(buff));
        auto nread = file.gcount();
        p.write(buff, nread, ec);
    } while (!file.eof());

    if (ec) {
        throw std::runtime_error(ec.what());
    }
    p.finish(ec);
    if (ec) {
        throw std::runtime_error(ec.what());
    }

    // make sure value is object
    json::value val = p.release();

    if (!val.is_object()) {
        throw std::runtime_error("File format incorrect. Please ensure content is wrapped in {}");
    }

    return val.as_object();
}
} // vega