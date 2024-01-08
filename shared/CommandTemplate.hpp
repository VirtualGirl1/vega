//
// Created by renier on 07/01/24.
//

#pragma once

#include <boost/json.hpp>
#include <string>

namespace vega {

class CommandTemplate {
private:
    std::string commandRegex;
    std::string target;
    short priority;

public:
    CommandTemplate();
    explicit CommandTemplate(boost::json::object obj);
    explicit CommandTemplate(std::string cr, std::string t, short p);

    std::string GetCommandRegex();
    std::string GetTarget();
    short GetPriority();
};

} // vega
