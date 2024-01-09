//
// Created by renier on 08/01/24.
//

#include "Application.hpp"

#include <boost/function.hpp>
#include <boost/dll/import.hpp>

namespace asio = boost::asio;
namespace dll = boost::dll;

namespace vega {
Application::Application() {
    port = 0;
}

Application::Application(short p) : service() {
    port = p;
}

void Application::SetCore(const std::string &path) {
    // load core
    // path should have already been validated
    typedef boost::shared_ptr<VegaModule> (pluginApiCreate)();
    boost::function<pluginApiCreate> creator;

    creator = dll::import_alias<pluginApiCreate>(
            path,
            "CreateModule",
            dll::load_mode::append_decorations
            );

    coreModule = creator();
}
} // vega