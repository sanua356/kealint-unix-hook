#include <config.h>

#include <http/post_request_json.h>
#include <http/response_json.h>

#include <string>

#include <boost/asio/local/stream_protocol.hpp>
#include <boost/asio/write.hpp>

#include <kealint_unix.h>
#include <kealint_unix_log.h>

#include "log/macros.h"

using namespace isc::hooks;
using namespace isc::kealint_unix;
using namespace isc::data;

namespace {
std::string proc_name = "";
bool enabled = false;
std::string socket_path = "";
}  // namespace

namespace isc {
namespace kealint_unix {

void
storeConfiguration(std::string param_proc_name, bool param_enabled, std::string param_socket_path) {
    proc_name = param_proc_name;
    enabled = param_enabled;
    socket_path = param_socket_path;
}

void
clearConfiguration() {
    proc_name = "";
    enabled = false;
    socket_path = "";
}
}  // namespace kealint_unix
}  // namespace isc

void
sendConfigurationToSocket(std::string config) {
    boost::asio::io_context io;
    boost::asio::local::stream_protocol::socket socket(io);
    socket.connect(boost::asio::local::stream_protocol::endpoint(socket_path));
    boost::asio::write(socket, boost::asio::buffer(config));
    socket.close();
}

int
sendConfiguration(ConstElementPtr config) {
    if (!config) {
        return (0);
    }

    try {
        std::string config_type = "";

        if (proc_name == "kea-dhcp4") {
            config_type = "Dhcp4";
        } else if (proc_name == "kea-dhcp-ddns") {
            config_type = "DhcpDdns";
        } else if (proc_name == "kea-ctrl-agent") {
            config_type = "Control-agent";
        }

        ElementPtr element = Element::createMap();
        element->set(config_type, config);

        std::stringstream os;
        element->toJSON(os);
        std::string config = os.str();

        sendConfigurationToSocket(config);

        LOG_INFO(kealint_unix_logger, KEALINT_UNIX_CONFIGURATION_SEND_SUCCESS)
            .arg(socket_path)
            .arg(proc_name);

    } catch (const std::exception& e) {
        LOG_ERROR(kealint_unix_logger, KEALINT_UNIX_SOCKET_ERROR)
            .arg(socket_path)
            .arg(proc_name)
            .arg(e.what());
    }

    return (0);
}

extern "C" {

int
dhcp4_srv_configured(CalloutHandle& handle) {
    if (!enabled) {
        return (0);
    }

    ConstElementPtr json_config_ptr;
    handle.getArgument("json_config", json_config_ptr);
    return sendConfiguration(json_config_ptr);
}

int
d2_srv_configured(CalloutHandle& handle) {
    if (!enabled) {
        return (0);
    }

    ConstElementPtr json_config_ptr;
    handle.getArgument("json_config", json_config_ptr);
    return sendConfiguration(json_config_ptr);
}
}  // namespace isc
