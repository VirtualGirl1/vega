//
// Created by renier on 07/01/24.
//

#include "CommandTemplate.hpp"

#include <regex>

namespace json = boost::json;

namespace vega {
CommandTemplate::CommandTemplate() {
    commandRegex = "";
    target = "";
    priority = 0;
}

CommandTemplate::CommandTemplate(boost::json::object obj) {
    // make sure all fields are present
    if (!obj.contains("CommandRegex")) {
        throw std::runtime_error("command template does not contain field 'CommandRegex'");
    }
    if (!obj.contains("Target")) {
        throw std::runtime_error("command template does not contain field 'Target'");
    }
    if (!obj.contains("Priority")) {
        throw std::runtime_error("command template does not contain field 'Priority'");
    }

    // make sure all fields are correct type
    json::value val;

    val = obj.at("CommandRegex");
    if (!val.is_string()) {
        throw std::runtime_error("value for CommandRegex must be a string");
    }
    commandRegex = val.as_string();

    val = obj.at("Target");
    if (!val.is_string()) {
        throw std::runtime_error("value for Target must be a string");
    }
    target = val.as_string();

    val = obj.at("Priority");
    if (!val.is_int64() && !val.is_uint64()) {
        throw std::runtime_error("value for Priority must be an integer");
    }
    priority = val.is_int64() ? val.as_int64() : val.as_uint64();

}

CommandTemplate::CommandTemplate(std::string cr, std::string t, short p) {
    commandRegex = cr;
    target = t;
    priority = p;
}

std::string CommandTemplate::GetCommandRegex() {
    return commandRegex;
}

std::string CommandTemplate::GetTarget() {
    return target;
}

short CommandTemplate::GetPriority() {
    return priority;
}

bool CommandTemplate::operator==(std::string &other) {

    std::regex r(commandRegex);
    return std::regex_match(other, r);
}

bool CommandTemplate::operator>(CommandTemplate &other) const {
    return this->priority > other.priority;
}

bool CommandTemplate::operator>=(CommandTemplate &other) const {
    return this->priority >= other.priority;
}

bool CommandTemplate::operator<(CommandTemplate &other) const {
    return this->priority < other.priority;
}

bool CommandTemplate::operator<=(CommandTemplate &other) const {
    return this->priority <= other.priority;
}
} // vega