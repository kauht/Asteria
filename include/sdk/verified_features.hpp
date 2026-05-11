// =====================================================================
// verified_features.hpp — hand-curated working CS2 cheat features
// =====================================================================
//
// Each entry is a known-good offset / hook / ConVar trick that has been
// verified live against the current CS2 build. Constants are static
// constexpr so they can be used at compile time.
//
// CS2_BUILD: 14160
// =====================================================================

#pragma once

#include <cstdint>

namespace cs2::verified
{
    // ----- Entity tracking (OnAddEntity / OnRemoveEntity) [working] -----
    namespace Entity_tracking__OnAddEntity___OnRemoveEntity_
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t CEntitySystem__m_entityListeners__CUtlVector_ = 0x30; // CUtlVector<IEntityListener*> — AddTail your shim here
        constexpr std::ptrdiff_t CEntityIdentity__m_pEntity = 0x0; // C_BaseEntity* — passed to OnAddEntity / OnRemoveEntity
        constexpr std::ptrdiff_t CEntityIdentity__m_designerName = 0x20; // const char* — schema class name; cheap filter
    }

    // ----- Tracing [placeholder] -----
    namespace Tracing
    {
        constexpr const char* status = "placeholder";
    }

    // ----- ESP [working] -----
    namespace ESP
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t C_BaseEntity__m_pGameSceneNode = 0x330; // CSkeletonInstance* — → bone matrix + abs origin
        constexpr std::ptrdiff_t C_BaseEntity__m_iHealth = 0x34C; // int32 — 0 == dead
        constexpr std::ptrdiff_t C_BaseEntity__m_lifeState = 0x354; // uint8 — 0 == ALIVE
        constexpr std::ptrdiff_t C_BaseEntity__m_iTeamNum = 0x3EB; // uint8 — 2 = T, 3 = CT
        constexpr std::ptrdiff_t CGameSceneNode__m_vecAbsOrigin = 0xC8; // Vector3 — world position (ESP root)
        constexpr std::ptrdiff_t CSkeletonInstance__m_modelState = 0x150; // CModelState — embedded; live bone array inside
        constexpr std::ptrdiff_t CCSPlayerController__m_iszPlayerName = 0x6F0; // char[128] — UTF-8 nickname
        constexpr std::ptrdiff_t CCSPlayerController__m_hPawn = 0x6BC; // CHandle — controller → pawn handle
        constexpr std::ptrdiff_t CCSPlayerController__m_iCompetitiveRanking = 0x878; // int32 — Premier rating (revealed pre-warmup)
        constexpr std::ptrdiff_t C_CSPlayerPawnBase__m_pWeaponServices = 0x11E0; // ptr — → active weapon handle
        constexpr std::ptrdiff_t C_BasePlayerWeapon__m_iItemDefinitionIndex = 0x1BA; // uint16 — CSWeaponID for the held weapon
        constexpr std::ptrdiff_t C_BasePlayerWeapon__m_iClip1 = 0x16D8; // int32 — current magazine count
        constexpr std::ptrdiff_t CCSPlayerController_InGameMoneyServices__m_iAccount = 0x40; // int32 — current cash
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_ArmorValue = 0x1C74; // int32 — armor 0..100
        constexpr std::ptrdiff_t CCSPlayer_ItemServices__m_bHasHelmet = 0x49; // bool — kevlar+helmet flag
        constexpr std::ptrdiff_t CCSPlayerController_ActionTrackingServices__m_iKills = 0x30; // int32 — scoreboard kills
        constexpr std::ptrdiff_t CCSPlayerController_ActionTrackingServices__m_iDeaths = 0x34; // int32 — scoreboard deaths
        constexpr std::ptrdiff_t EntitySpottedState_t__m_bSpotted = 0x8; // bool — force true to reveal on radar
        constexpr std::ptrdiff_t EntitySpottedState_t__m_bSpottedByMask = 0xC; // uint32[2] — OR with 0xFFFFFFFF to spot for everyone
    }

    // ----- FOV Changer [working] -----
    namespace FOV_Changer
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t CBasePlayerController__m_iDesiredFOV = 0x784; // uint32 — a2x-named m_iDesiredFOV_OnController — canonical write
        constexpr std::ptrdiff_t CCSPlayer_CameraServices__m_iFOV = 0x290; // uint32 — current camera FOV
        constexpr std::ptrdiff_t CCSPlayer_CameraServices__m_iFOVStart = 0x294; // uint32 — target camera FOV
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_pCameraServices = 0x1218; // CCSPlayer_CameraServices* — deref to reach m_iFOV / m_iFOVStart
    }

    // ----- Aimbot [working] -----
    namespace Aimbot
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t C_CSGameRules__m_bFreezePeriod = 0x40; // bool — freeze — no attacks possible
        constexpr std::ptrdiff_t C_CSGameRules__m_bWarmupPeriod = 0x41; // bool — warmup — no attacks possible
        constexpr std::ptrdiff_t C_CSGameRules__m_bIsValveDS = 0xA4; // bool — TRUE on Valve official MM — soft 0.55×
        constexpr std::ptrdiff_t C_CSGameRules__m_bHasMatchStarted = 0xB0; // bool — match-state gate
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_bWaitForNoAttack = 0x1C68; // bool — post-respawn / weapon-switch lockout
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_bIsDefusing = 0x1C4A; // bool — server forbids attack while defusing
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_bIsGrabbingHostage = 0x1C4B; // bool — server forbids attack while grabbing hostage
        constexpr std::ptrdiff_t C_BaseEntity__m_MoveType = 0x525; // MoveType_t — only WALK(2) / FLYGRAVITY(4) are normal play
        constexpr std::ptrdiff_t C_CSWeaponBaseGun__m_zoomLevel = 0x1CB0; // int32 — 0 = unscoped — refuse silent fire on snipers when zoom == 0
        constexpr std::ptrdiff_t C_CSWeaponBaseGun__m_bNeedsBoltAction = 0x1CCD; // bool — AWP/SSG/Scout bolt-cycle lockout
        constexpr std::ptrdiff_t C_CSWeaponBase__m_bInReload = 0x17F4; // bool — weapon mid-reload
        constexpr std::ptrdiff_t C_BasePlayerWeapon__m_iClip1 = 0x16D8; // int32 — 0 ⇒ no bullet possible
        constexpr std::ptrdiff_t C_BasePlayerWeapon__m_nNextPrimaryAttackTick = 0x16C8; // int32 — absolute server tick when next attack allowed
        constexpr std::ptrdiff_t CBasePlayerController__m_nTickBase = 0x6B8; // int32 — compare against m_nNextPrimaryAttackTick
        constexpr std::ptrdiff_t EntitySpottedState_t__m_bSpottedByMask = 0xC; // uint32[2] — real enemy in PVS ⇒ throttle 0.65×
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_iIDEntIndex = 0x33DC; // int32 — matches target ⇒ bypass throttle
        constexpr std::ptrdiff_t C_BaseEntity__m_vecVelocity = 0x430; // Vector3 — soft throttle 1.0 → 0.5 from 80 → 180 u/s
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_pAimPunchServices = 0x1490; // CCSPlayer_AimPunchServices* — owns aim-punch cache vector
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_iShotsFired = 0x1C5C; // int32 — drives spread seed
        constexpr std::ptrdiff_t C_CSWeaponBase__m_flRecoilIndex = 0x17E0; // float — recoil pattern index
    }

    // ----- Triggerbot (Seeded) [working] -----
    namespace Triggerbot__Seeded_
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_iIDEntIndex = 0x33DC; // int32 — primary target signal
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_iShotsFired = 0x1C5C; // int32 — drives spread seed
        constexpr std::ptrdiff_t C_CSPlayerPawn__m_pAimPunchServices = 0x1490; // CCSPlayer_AimPunchServices* — deref for live aim-punch vec used in the seed
    }

    // ----- Skin Changer [working] -----
    namespace Skin_Changer
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t C_EconItemView__m_iItemDefinitionIndex = 0x1BA; // uint16 — weapon definition (CSWeaponID)
        constexpr std::ptrdiff_t C_EconItemView__m_iItemIDLow = 0x1C4; // uint32 — set 0xFFFFFFFF to force EconItemView lookup miss → fallback path
        constexpr std::ptrdiff_t C_EconItemView__m_iItemIDHigh = 0x1C8; // uint32 — set 0xFFFFFFFF (paired with m_iItemIDLow)
        constexpr std::ptrdiff_t C_EconItemView__m_iEntityQuality = 0x1C0; // int32 — quality slot used by the composite shader
        constexpr std::ptrdiff_t C_EconItemView__m_nFallbackPaintKit = 0x1D0; // uint32 — paint kit ID (the actual 'skin')
        constexpr std::ptrdiff_t C_EconItemView__m_nFallbackSeed = 0x1D4; // int32 — pattern seed
        constexpr std::ptrdiff_t C_EconItemView__m_flFallbackWear = 0x1D8; // float — 0.0 = factory new, 1.0 = battle-scarred
        constexpr std::ptrdiff_t C_EconItemView__m_nFallbackStatTrak = 0x1DC; // int32 — StatTrak counter (-1 disables)
    }

    // ----- Knife Changer [working] -----
    namespace Knife_Changer
    {
        constexpr const char* status = "working";
        constexpr std::ptrdiff_t C_BasePlayerWeapon__m_nSubclassID = 0x36C; // uint32 — knife subclass key (drives mesh + sequences + animgraph)
        constexpr std::ptrdiff_t C_BasePlayerWeapon__m_iItemDefinitionIndex = 0x1BA; // uint16 — must match the knife type for the chosen subclass
    }

    // ----- Glove Changer [placeholder] -----
    namespace Glove_Changer
    {
        constexpr const char* status = "placeholder";
    }

} // namespace cs2::verified
