#include <config.h>

#include <asiolink/io_service_mgr.h>
#include <cc/dhcp_config_error.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/srv_config.h>
#include <exceptions/exceptions.h>
#include <hooks/library_handle.h>
#include <process/daemon.h>

#include <filesystem>
#include <regex>
#include <string>
#include <vector>

#include <kealint_unix.h>
#include <kealint_unix_log.h>

#include "cc/data.h"
#include "log/macros.h"

namespace isc {
namespace kealint_unix {

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::hooks;

extern "C" {
int
load(isc::hooks::LibraryHandle& handle) {
    std::string proc_name = Daemon::getProcName();
    if (proc_name != "kea-dhcp4" && proc_name != "kea-dhcp-ddns" && proc_name != "kea-ctrl-agent") {
        isc_throw(isc::Unexpected,
                  "Bad process name: " << proc_name
                                       << ", expected kea-dhcp4, kea-dhcp-ddns or kea-ctrl-agent");
    }

    try {
        ConstElementPtr enabled = handle.getParameter("enabled");
        ConstElementPtr socket_path = handle.getParameter("socket-path");

        if (enabled == nullptr || socket_path == nullptr) {
            LOG_ERROR(kealint_unix_logger, KEALINT_UNIX_MISSING_PARAMS);
            return (1);
        }

        if (enabled->getType() != Element::boolean) {
            LOG_ERROR(kealint_unix_logger, KEALINT_UNIX_ENABLED_PARAM_BAD_TYPE);
            return (1);
        }

        if (socket_path->getType() != Element::string) {
            LOG_ERROR(kealint_unix_logger, KEALINT_UNIX_SOCKET_PATH_PARAM_BAD_TYPE);
            return (1);
        }

        int enabled_value = enabled->boolValue();
        std::string socket_path_value = socket_path->stringValue();

        clearConfiguration();
        storeConfiguration(proc_name, enabled_value, socket_path_value);
        return (0);
    } catch (const std::exception& ex) {
        LOG_ERROR(kealint_unix_logger, KEALINT_UNIX_UNEXPECTED_ERROR);
        return (1);
    }
}

int
unload() {
    clearConfiguration();
    LOG_INFO(kealint_unix_logger, KEALINT_UNIX_UNLOAD_SUCCESS);
    return (0);
}

int
multi_threading_compatible() {
    return (1);
}
}

}  // namespace kealint_unix
}  // namespace isc
