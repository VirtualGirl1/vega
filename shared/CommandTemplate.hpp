//
// Created by renier on 07/01/24.
//

#pragma once

#include <boost/json.hpp>
#include <string>

namespace vega {


/*
 * CommandTemplate represents a command that is matched using regex.
 *
 * commandRegex -> the regex to check the command
 * target       -> the name of the function to call
 * priority     -> in the case of multiple matching commands the one with
 *                  the highest priority will be run
 */
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

    // compare regex
    bool operator==(std::string& other);

    // compare priority
    bool operator>(CommandTemplate& other) const;
    bool operator>=(CommandTemplate& other) const;
    bool operator<(CommandTemplate& other) const;
    bool operator<=(CommandTemplate& other) const;
};

} // vega
