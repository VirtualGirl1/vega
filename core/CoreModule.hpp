//
// Created by renier on 10/01/24.
//

#pragma once


#include "VegaModule.hpp"
#include "CommandTemplate.hpp"

namespace vega {

class CoreModule : public VegaModule {
private:
    std::vector<CommandTemplate> commands;
public:
    std::string Name() override;
    void Init(SettingLoader loader) override;
    bool CanExecute(std::string com) override;

private:
};

} // vega
