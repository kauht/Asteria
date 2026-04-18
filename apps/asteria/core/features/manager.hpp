#pragma once

#include "chams/chams.hpp"

namespace asteria::core::features {

inline bool init() { return chams::init(); }

inline void unload() { chams::unload(); }

} // namespace asteria::core::features
