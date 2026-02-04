#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID KEALINT_UNIX_MISSING_PARAMS = "KEALINT_UNIX_MISSING_PARAMS";
extern const isc::log::MessageID KEALINT_UNIX_ENABLED_PARAM_BAD_TYPE = "KEALINT_UNIX_ENABLED_PARAM_BAD_TYPE";
extern const isc::log::MessageID KEALINT_UNIX_SOCKET_PATH_PARAM_BAD_TYPE = "KEALINT_UNIX_SOCKET_PATH_PARAM_BAD_TYPE";
extern const isc::log::MessageID KEALINT_UNIX_UNEXPECTED_ERROR = "KEALINT_UNIX_UNEXPECTED_ERROR";
extern const isc::log::MessageID KEALINT_UNIX_UNLOAD_SUCCESS = "KEALINT_UNIX_UNLOAD_SUCCESS";
extern const isc::log::MessageID KEALINT_UNIX_CONFIGURATION_SEND_SUCCESS = "KEALINT_UNIX_CONFIGURATION_SEND_SUCCESS";
extern const isc::log::MessageID KEALINT_UNIX_SOCKET_ERROR = "KEALINT_UNIX_SOCKET_ERROR";

namespace {

const char* values[] = {
    "KEALINT_UNIX_MISSING_PARAMS", "Hook awaiting required parameters: \"enabled\" and \"socket-path\".",
    "KEALINT_UNIX_ENABLED_PARAM_BAD_TYPE", "Param \"enabled\" must be of boolean type.",
    "KEALINT_UNIX_SOCKET_PATH_PARAM_BAD_TYPE", "Param \"socket-path\" must be string type.",
    "KEALINT_UNIX_UNEXPECTED_ERROR", "An unexpected error occurred while turning on the hook.",
    "KEALINT_UNIX_UNLOAD_SUCCESS", "Hook unloaded successfully.",
    "KEALINT_UNIX_CONFIGURATION_SEND_SUCCESS", "The configuration '%1' of the KEA server has been successfully sent to the UNIX socket '%2' for processing in KEALint.",
    "KEALINT_UNIX_SOCKET_ERROR", "An error occurred when the UNIX socket '%1' to send the configuration '%2' to KEALint. %3",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace
