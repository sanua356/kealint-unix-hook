#ifndef KEALINT_UNIX_H
#define KEALINT_UNIX_H

#include <log/macros.h>
#include <log/message_initializer.h>

#include <kealint_unix_messages.h>

namespace isc {
namespace kealint_unix {

void
storeConfiguration(std::string proc_name, bool enabled, std::string socket_path);

void
clearConfiguration();

}  // namespace kealint_unix
}  // namespace isc

#endif
