#include "util/logger.hpp"
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "user32.lib")
#include <thread>
#endif
#include "util/math/math.hpp"

#include <d3d11.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

typedef unsigned char BYTE;

using namespace asteria;

// Cool In-Game Console Logging Function
typedef void (*ConMsgType)(const char* msg, ...);
void ConMsg(const char* msg) {
    uintptr_t tier0 = reinterpret_cast<uintptr_t>(GetModuleHandleA("tier0.dll"));
    ConMsgType ConMsg = reinterpret_cast<ConMsgType>(GetProcAddress(GetModuleHandleA("tier0.dll"), "ConMsg"));
    ConMsg(msg);
}
class C_BaseEntity {
  public:
    BYTE unknown_0000[0x38]; // 0x000 - VTable and base class data idk

    // Components
    BYTE m_CBodyComponent[8]; // 0x038 - CBodyComponent::Storage_t

    // Health & Stats
    int32_t m_iMaxHealth;           // 0x350
    int32_t m_iHealth;              // 0x354
    uint8_t m_lifeState;            // 0x35C
    bool m_bTakesDamage;            // 0x35D
    uint64_t m_nTakeDamageFlags;    // 0x360 - TakeDamageFlags_t (8 bytes)
    uint8_t m_nPlatformType;        // 0x368 - EntityPlatformTypes_t
    uint8_t m_ubInterpolationFrame; // 0x369
    BYTE unknown_36A[2];            // 0x36A - padding
    uint32_t m_nSubclassID;         // 0x36C - EntitySubclassID_t

    BYTE unknown_0370[0x3BC - 0x370]; // 0x370 - gap to animation time

    // Time & Movement
    float m_flAnimTime;        // 0x3BC
    float m_flSimulationTime;  // 0x3C0
    float m_flCreateTime;      // 0x3E8 - GameTime_t (treat as float)
    float m_flSpeed;           // 0x3EC
    bool m_bClientSideRagdoll; // 0x3F2
    uint8_t m_iTeamNum;        // 0x3F3
    uint32_t m_spawnflags;     // 0x3F4
    uint32_t m_nNextThinkTick; // 0x3F8 - GameTick_t
    uint32_t m_fFlags;         // 0x400

    BYTE unknown_0404[0x410 - 0x404]; // 0x404

    // Velocity
    BYTE m_vecServerVelocity[40]; // 0x410 - CNetworkVelocityVector

    BYTE unknown_0438[0x518 - 0x438]; // 0x438 - gap to base velocity

    // Position & Physics
    Vec3 m_vecBaseVelocity;       // 0x518
    uint32_t m_hEffectEntity;     // 0x524 - CHandle
    uint32_t m_hOwnerEntity;      // 0x528 - CHandle
    uint8_t m_MoveCollide;        // 0x52C - MoveCollide_t
    uint8_t m_MoveType;           // 0x52D - MoveType_t
    BYTE unknown_052E[2];         // 0x52E
    float m_flWaterLevel;         // 0x530
    uint32_t m_fEffects;          // 0x534
    uint32_t m_hGroundEntity;     // 0x538 - CHandle
    int m_nGroundBodyIndex;       // 0x53C
    float m_flFriction;           // 0x540
    float m_flElasticity;         // 0x544
    float m_flGravityScale;       // 0x548
    float m_flTimeScale;          // 0x54C
    bool m_bAnimatedEveryTick;    // 0x550
    bool m_bGravityDisabled;      // 0x551
    BYTE unknown_0552[2];         // 0x552
    float m_flNavIgnoreUntilTime; // 0x554 - GameTime_t (basically float?)
    uint32_t m_nBloodType;        // 0x600 - BloodType enum
};

template <typename T> static T read(uintptr_t addr) {
    return *reinterpret_cast<const T*>(addr);
}

void entry() {
    const uintptr_t chunk_table_offset = 0x21AD988;

    uintptr_t client_base = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));
    util::info(std::format("Client Base: {}", (void*) client_base));

    uintptr_t* chunk_table = read<uintptr_t*>(client_base + chunk_table_offset);
    util::info(std::format("Chunk Table pointer read: {}", (void*) chunk_table));

    while (!(GetAsyncKeyState(VK_DELETE) & 1)) {

        const int MAX_ENTITIES = 2048;
        for (int i = 0; i < MAX_ENTITIES; i++) {
            int chunk_idx = i >> 9;   // which chunk
            int slot_idx = i & 0x1FF; // slot in chunk

            // read chunk pointer safely from chunk_table[chunk_idx]
            uintptr_t chunk_ptr = read<uintptr_t>(chunk_table[chunk_idx]);
            if (!chunk_ptr) {
                continue;
            }

            // get slot address
            uintptr_t slot_addr = chunk_ptr + (slot_idx * 112); // 112 = size of slot

            C_BaseEntity* entity_ptr = read<C_BaseEntity*>(slot_addr + 0);
            C_BaseEntity entity = read<C_BaseEntity>(reinterpret_cast<uintptr_t>(entity_ptr));

            int32_t health = entity.m_iHealth;
            uint8_t team = entity.m_iTeamNum;

            util::info(std::format("Entity idx {} -> ptr {}, health {}, team {}", i, (void*) entity_ptr, health, team));
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    MessageBoxA(nullptr, "Asteria Unloading!", "Info", MB_OK | MB_ICONINFORMATION);
}

#ifdef _WIN32

BOOL WINAPI DllMain(HINSTANCE /*hinst*/, DWORD reason, LPVOID /*reserved*/) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            util::info("Asteria Loaded");
            std::thread(entry).detach();
            FreeLibrary(GetModuleHandleA("asteria.dll"));
            break;
        case DLL_PROCESS_DETACH:
            util::info("Asteria unloading");
            break;
        default:
            break;
    }
    return TRUE;
}
#else
__attribute__((constructor)) static void asteria_start() {
    info("Asteria Loaded");
}

__attribute__((destructor)) static void asteria_end() {
    info("Asteria unloading");
}
#endif
