#include "sdk/client_dll.hpp"
#include "sdk/server_dll.hpp"
#include <sdk/cs2sdk.hpp>
#include <unordered_map>

namespace entities {
    std::unordered_map<int, cs2::sdk::server::CBaseEntity> entities; // index, entity
}
