//
// Created by renier on 10/01/24.
//

#include "CoreModule.hpp"

namespace vega {
std::string CoreModule::Name() {
    return "Core Module";
}

void CoreModule::Init(SettingLoader loader) {
    // get core settings
    auto val = loader.GetSetting("Core");
    if (!val.is_object()) {
        throw std::runtime_error("Could not get core config");
    }

    // get path
    auto corePath = val.as_object().at("ModulePath");
    if (!corePath.is_string()) {
        throw std::runtime_error("Could not get core path");
    }

    // load the file



}

bool CoreModule::CanExecute(std::string com) {
    return false;
}
} // vega