#include "hooks.hpp"
#include "../../utils/utils.hpp"
#include <safetyhook.hpp>

namespace hooks {

    void Install() {
        io::println("--- Installing Hooks ---");







        io::println("--- Hooks Installed ---");
    }

    void Uninstall() {
        original::CreateMoveInner = {};
        original::OnAddEntity = {};
        original::OnRemoveEntity = {};
    }
}
