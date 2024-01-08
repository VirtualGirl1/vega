//
// Created by renier on 07/01/24.
//

#pragma once

#include <string>

namespace vega {

class VegaModule {
public:
    virtual std::string Name() = 0;
    virtual bool CanExecute(std::string comm) = 0;


    virtual ~VegaModule() = default;
};

}
