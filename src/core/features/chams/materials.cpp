#include "materials.hpp"

namespace features {
    const char* GetMaterialName(CMaterial* mat) {
        if (!mat || !*reinterpret_cast<void**>(mat)) return nullptr;
        return (*reinterpret_cast<const char*(**)(void*)>(*reinterpret_cast<void**>(mat)))(mat);
    }
}
