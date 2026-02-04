#include <config.h>

#include <hooks/hooks.h>

namespace isc {
namespace kealint_unix {

extern "C" {

int
version() {
    return (KEA_HOOKS_VERSION);
}

}  // extern "C"

}  // namespace kealint_unix
}  // namespace isc
