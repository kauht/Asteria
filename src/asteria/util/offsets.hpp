

namespace asteria::util {
    namespace patterns {
        constexpr auto swapchain = "48 89 2D ? ? ? ? 66 0F 7F 05 ? ? ? ?";
        constexpr auto csgoinput = "48 8B 0D ? ? ? ? 4C 8B C6 8B 10 E8";
        constexpr auto get_view_angles = "4C 8B C1 85 D2 74 ? 48 8D 05";
        constexpr auto set_view_angles = "85 D2 75 ? 48 63 81";
        constexpr auto get_entity_index = "E8 ? ? ? ? 8B 8D ? ? ? ? 8D 51";
        constexpr auto construct_input_data = "E8 ? ? ? ? 48 8B CF 48 8B F0 44 8B B0 10 59 00 00";
        constexpr auto poo = "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B CF 48 8B F0 44 8B B0 10 59 00 00";
        constexpr auto automake_user_cmd = "E8 ? ? ? ? 48 89 44 24 40 48 8D 4D F0";
        constexpr auto set_mesh_group_mask = "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 99 ? ? ? ? 48 8B 71";
        constexpr auto get_is_in_game = "48 8B 05 ? ? ? ? 48 85 C0 74 ? 83 B8 A8 00 00 00 03 75 ? 80 B8 A4 00 00 00 00";
        constexpr auto get_is_connected = "48 8B 05 ? ? ? ? 48 85 C0 74 ? 83 B8 F0 0C 00 00 00 7E";
        constexpr auto get_local_player_index = "48 83 EC 28 83 F9 FF 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 30 48 8B 01 FF 90 00 03 00 00 8B 08 48 63 C1 4C 8D 05";
        constexpr auto get_local_pawn = "40 53 48 83 EC ? 33 C9 E8 ? ? ? ? 48 8B D8 48 85 C0 74 ? 48 8B 00 48 8B CB FF 90 ? ? ? ? 84 C0 74 ? 48 8B C3";
        constexpr auto get_base_entity = "4C 8D 49 10 81 FA ?? ?? 00 00 77 ?? 8B CA C1 F9 09";
        constexpr auto entity_system = "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB";
        constexpr auto get_matrix_for_view = "48 8B C4 48 89 68 ? 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 49 8B F1";
        constexpr auto screen_transform = "48 89 5C 24 08 57 48 83 EC ? 48 83 3D ? ? ? ? ? 48 8B DA";
        constexpr auto view_matrix = "48 8D 0D ? ? ? ? 48 C1 E0 06 48 03 C1";
        constexpr auto create_move = "48 8B C4 4C 89 40 ? 48 89 48 ? 55 53 41 54";
        constexpr auto tracer_callback = "48 89 7C 24 20 55 48 8D 6C 24 F0 48 81 EC 10 01 00 00";
        constexpr auto particle_tracer_callback = "40 55 56 48 8D AC 24 E8 FE FF FF 48 81 EC 18 02 00 00";
        constexpr auto fx_tracer = "4C 8B DC 49 89 5B 08 49 89 73 10 57 48 81 EC 80 00 00 00";
    }
    namespace interfaces {
        constexpr auto inputsystem = "InputSystemVersion00";
        constexpr auto schemasystem = "SchemaSystem_00";
        constexpr auto engineclient = "Source2EngineToClient001";
    }
}
