# Verified features

Working CS2 cheat features. Each entry lists the schema fields, convars and hooks needed to wire it up. Addresses come from the neighbouring `offsets.*` and `signatures.*` files.

Build: `14160`

Features: 7

---

## Entity tracking (OnAddEntity / OnRemoveEntity)

Hook the engine's entity-system listener instead of walking dwEntityList every frame. CEntitySystem keeps a CUtlVector<IEntityListener*> at +0x30; install a small shim with two virtuals (OnAddEntity, OnRemoveEntity) and the engine will call it whenever a CEntityIdentity is bound or torn down. Cache (handle → entity*) in your own flat array and you skip ~16k pointer-chases per second versus the loop. 

Falls back automatically: on the first frame after attach, do one full walk to seed the cache, then run from listener events thereafter.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `CEntitySystem` | `m_entityListeners (CUtlVector)` | `0x30` | `CUtlVector<IEntityListener*>` | AddTail your shim here |
| `CEntityIdentity` | `m_pEntity` | `0x0` | `C_BaseEntity*` | passed to OnAddEntity / OnRemoveEntity |
| `CEntityIdentity` | `m_designerName` | `0x20` | `const char*` | schema class name; cheap filter |

### Hooks

| Function | Module | Signature | Action |
|---|---|---|---|
| `IEntityListener::OnAddEntity` | `client.dll` | `(virtual)` | Insert into the cheat's entity cache. |
| `IEntityListener::OnRemoveEntity` | `client.dll` | `(virtual)` | Remove from the cheat's entity cache; cancel any pending visual state. |

---

## ESP

Render data for each cached pawn: state (m_iHealth, m_lifeState, m_iTeamNum), world position via m_pGameSceneNode → CGameSceneNode::m_vecAbsOrigin, named via m_hController → CCSPlayerController::m_iszPlayerName, weapon via m_hActiveWeapon. Project to screen with dwViewMatrix (4×4 row-major). 

Skeleton: m_pGameSceneNode is actually CSkeletonInstance; the live bone array hangs off CModelState at +0x150. Bone 6 = head, 5 = chest on the standard CSPlayer skeleton. Money / armor / scoreboard / rank live on the controller-side service blocks listed below.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `C_BaseEntity` | `m_pGameSceneNode` | `0x330` | `CSkeletonInstance*` | → bone matrix + abs origin |
| `C_BaseEntity` | `m_iHealth` | `0x34C` | `int32` | 0 == dead |
| `C_BaseEntity` | `m_lifeState` | `0x354` | `uint8` | 0 == ALIVE |
| `C_BaseEntity` | `m_iTeamNum` | `0x3EB` | `uint8` | 2 = T, 3 = CT |
| `CGameSceneNode` | `m_vecAbsOrigin` | `0xC8` | `Vector3` | world position (ESP root) |
| `CSkeletonInstance` | `m_modelState` | `0x150` | `CModelState` | embedded; live bone array inside |
| `CCSPlayerController` | `m_iszPlayerName` | `0x6F0` | `char[128]` | UTF-8 nickname |
| `CCSPlayerController` | `m_hPawn` | `0x6BC` | `CHandle` | controller → pawn handle |
| `CCSPlayerController` | `m_iCompetitiveRanking` | `0x878` | `int32` | Premier rating (revealed pre-warmup) |
| `C_CSPlayerPawnBase` | `m_pWeaponServices` | `0x11E0` | `ptr` | → active weapon handle |
| `C_BasePlayerWeapon` | `m_iItemDefinitionIndex` | `0x1BA` | `uint16` | CSWeaponID for the held weapon |
| `C_BasePlayerWeapon` | `m_iClip1` | `0x16D8` | `int32` | current magazine count |
| `CCSPlayerController_InGameMoneyServices` | `m_iAccount` | `0x40` | `int32` | current cash |
| `C_CSPlayerPawn` | `m_ArmorValue` | `0x1C74` | `int32` | armor 0..100 |
| `CCSPlayer_ItemServices` | `m_bHasHelmet` | `0x49` | `bool` | kevlar+helmet flag |
| `CCSPlayerController_ActionTrackingServices` | `m_iKills` | `0x30` | `int32` | scoreboard kills |
| `CCSPlayerController_ActionTrackingServices` | `m_iDeaths` | `0x34` | `int32` | scoreboard deaths |
| `EntitySpottedState_t` | `m_bSpotted` | `0x8` | `bool` | force true to reveal on radar |
| `EntitySpottedState_t` | `m_bSpottedByMask` | `0xC` | `uint32[2]` | OR with 0xFFFFFFFF to spot for everyone |

---

## FOV Changer

Two-prong approach. (1) Hook GetWorldFov in client.dll (signature SetWorldFov, E8-CALL @ +1) and return the desired value when the local pawn is not scoped — keeps the value sticky against engine resets. (2) Every tick write the desired FOV into m_iFOV and m_iFOVStart on the camera services AND into m_iDesiredFOV on the local controller. The controller-level field is the canonical source the renderer reads; without it the camera-services side gets clobbered back to default.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `CBasePlayerController` | `m_iDesiredFOV` | `0x784` | `uint32` | a2x-named m_iDesiredFOV_OnController — canonical write |
| `CCSPlayer_CameraServices` | `m_iFOV` | `0x290` | `uint32` | current camera FOV |
| `CCSPlayer_CameraServices` | `m_iFOVStart` | `0x294` | `uint32` | target camera FOV |
| `C_CSPlayerPawn` | `m_pCameraServices` | `0x1218` | `CCSPlayer_CameraServices*` | deref to reach m_iFOV / m_iFOVStart |

### Hooks

| Function | Module | Signature | Action |
|---|---|---|---|
| `GetWorldFov` | `client.dll` | `SetWorldFov` | Return cfg.fovValue when not scoped, else delegate to original. |

---

## Aimbot

Per-tick phase machine driven from CCSGOInput::CreateMove (IDLE → REACTING → ATTACKING → CORRECTING → LOCKED). Target selection scores enemies on FOV delta, distance, visibility (engine trace) and weighting flags. Final angle delivery happens via a hooked CSGOInputHistoryEntry::WriteSubtick (signature `48 89 5C 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC B0 00 00 00 8B 01 48 8B F9 81 4A 10 00 02`, unique match @ 0x180C53DB0 in build 14152) so the override only touches per-subtick shoot angles (fe[7..9]) on attack subticks (a3 != 0). The real view-angle stream replayed for spectators / GOTV / Overwatch (fe[4..6]) is NEVER touched. 

Hard-suppress gates (any true ⇒ skip the angle write entirely): freeze / warmup, m_bWaitForNoAttack, no-scope sniper, m_bNeedsBoltAction, m_bInReload, m_iClip1 == 0, m_nNextPrimaryAttackTick > tickBase + 1, m_bIsDefusing, m_bIsGrabbingHostage, MoveType not WALK / FLYGRAVITY. Soft throttle scales the 28°/subtick flick cap: m_bIsValveDS × 0.55, observerCount × 0.55, m_bSpotted + observers × 0.65, horizontal speed > 80 u/s linearly ramps to 0.5 (caps at 180 u/s), ±0.10° LCG jitter. Crosshair-aligned bypass: when local m_iIDEntIndex resolves to the silent-aim target, the throttle is bypassed.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `C_CSGameRules` | `m_bFreezePeriod` | `0x40` | `bool` | freeze — no attacks possible |
| `C_CSGameRules` | `m_bWarmupPeriod` | `0x41` | `bool` | warmup — no attacks possible |
| `C_CSGameRules` | `m_bIsValveDS` | `0xA4` | `bool` | TRUE on Valve official MM — soft 0.55× |
| `C_CSGameRules` | `m_bHasMatchStarted` | `0xB0` | `bool` | match-state gate |
| `C_CSPlayerPawn` | `m_bWaitForNoAttack` | `0x1C68` | `bool` | post-respawn / weapon-switch lockout |
| `C_CSPlayerPawn` | `m_bIsDefusing` | `0x1C4A` | `bool` | server forbids attack while defusing |
| `C_CSPlayerPawn` | `m_bIsGrabbingHostage` | `0x1C4B` | `bool` | server forbids attack while grabbing hostage |
| `C_BaseEntity` | `m_MoveType` | `0x525` | `MoveType_t` | only WALK(2) / FLYGRAVITY(4) are normal play |
| `C_CSWeaponBaseGun` | `m_zoomLevel` | `0x1CB0` | `int32` | 0 = unscoped — refuse silent fire on snipers when zoom == 0 |
| `C_CSWeaponBaseGun` | `m_bNeedsBoltAction` | `0x1CCD` | `bool` | AWP/SSG/Scout bolt-cycle lockout |
| `C_CSWeaponBase` | `m_bInReload` | `0x17F4` | `bool` | weapon mid-reload |
| `C_BasePlayerWeapon` | `m_iClip1` | `0x16D8` | `int32` | 0 ⇒ no bullet possible |
| `C_BasePlayerWeapon` | `m_nNextPrimaryAttackTick` | `0x16C8` | `int32` | absolute server tick when next attack allowed |
| `CBasePlayerController` | `m_nTickBase` | `0x6B8` | `int32` | compare against m_nNextPrimaryAttackTick |
| `EntitySpottedState_t` | `m_bSpottedByMask` | `0xC` | `uint32[2]` | real enemy in PVS ⇒ throttle 0.65× |
| `C_CSPlayerPawn` | `m_iIDEntIndex` | `0x33DC` | `int32` | matches target ⇒ bypass throttle |
| `C_BaseEntity` | `m_vecVelocity` | `0x430` | `Vector3` | soft throttle 1.0 → 0.5 from 80 → 180 u/s |
| `C_CSPlayerPawn` | `m_pAimPunchServices` | `0x1490` | `CCSPlayer_AimPunchServices*` | owns aim-punch cache vector |
| `C_CSPlayerPawn` | `m_iShotsFired` | `0x1C5C` | `int32` | drives spread seed |
| `C_CSWeaponBase` | `m_flRecoilIndex` | `0x17E0` | `float` | recoil pattern index |

### Hooks

| Function | Module | Signature | Action |
|---|---|---|---|
| `CCSGOInput::CreateMove` | `client.dll` | `CreateMove` | Phase machine + target select + angle snap; sets fire latch. |
| `CSGOInputHistoryEntry::WriteSubtick` | `client.dll` | `48 89 5C 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC B0 00 00 00 8B 01 48 8B F9 81 4A 10 00 02` | Per-subtick angle override — attack subticks only; fe[7..9] only. |

---

## Triggerbot (Seeded)

Per-tick seeded prediction. Reads the live spread seed (m_iShotsFired + aim-punch) and re-runs Valve's spread RNG via SpreadSeedGen + CalcSpread to compute exactly where the next bullet would fly, then traces from local eye to that point. Strict-window mode tests only ticks {0, +1} and ALL must hit before firing; wide-window mode accepts ANY hit in {0, +1, -1, +2}. Local eye position is projected by localVel × leadTime so test geometry matches engine fire-time eye pos. 

Uses the REAL m_fAccuracyPenalty + m_flTurningInaccuracy in the predictor — the earlier 'perfect-shot' override that zeroed client spread caused server desync (kill sound but no damage); that path is OFF by default. 

Cooperates with aimbot: trigger defers whenever Aimbot::state.phase ∈ {REACTING, ATTACKING, CORRECTING}. SendInput LBUTTON edges from trigger are masked out of aimbot's rawAim filter via an 80 ms synth-click window so the synthetic click can't wake aimbot uninvited.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `C_CSPlayerPawn` | `m_iIDEntIndex` | `0x33DC` | `int32` | primary target signal |
| `C_CSPlayerPawn` | `m_iShotsFired` | `0x1C5C` | `int32` | drives spread seed |
| `C_CSPlayerPawn` | `m_pAimPunchServices` | `0x1490` | `CCSPlayer_AimPunchServices*` | deref for live aim-punch vec used in the seed |

### Hooks

| Function | Module | Signature | Action |
|---|---|---|---|
| `CCSPlayerAnimGraphState::CalcSpread` | `client.dll` | `CalcSpread` | Cache (mode, baseSpread, inaccuracy) per itemDef. |
| `NoSpread1` | `client.dll` | `NoSpread1` | Optional perfect-shot path — DISABLED by default. |

---

## Skin Changer

Writes m_nFallbackPaintKit / m_nFallbackSeed / m_flFallbackWear / m_iEntityQuality on each weapon then forces the modern paint-apply path: ApplyEconCustomization(weapon, 1) → sub_181079790 → sub_18105AAF0 (which actually consumes the fallback fields and queues 'clientside_reload_custom_econ' to rebuild the composite material). RegenerateWeaponSkin alone is INSUFFICIENT — it only handles the legacy static paint table. GetCustomPaintKitIndex is polled to detect rejection and gate re-apply work instead of hammering ApplyEconCustomization every tick. Setting m_iItemIDLow / High to 0xFFFFFFFF forces the EconItemView lookup to fail → fallback path taken.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `C_EconItemView` | `m_iItemDefinitionIndex` | `0x1BA` | `uint16` | weapon definition (CSWeaponID) |
| `C_EconItemView` | `m_iItemIDLow` | `0x1C4` | `uint32` | set 0xFFFFFFFF to force EconItemView lookup miss → fallback path |
| `C_EconItemView` | `m_iItemIDHigh` | `0x1C8` | `uint32` | set 0xFFFFFFFF (paired with m_iItemIDLow) |
| `C_EconItemView` | `m_iEntityQuality` | `0x1C0` | `int32` | quality slot used by the composite shader |
| `C_EconItemView` | `m_nFallbackPaintKit` | `0x1D0` | `uint32` | paint kit ID (the actual 'skin') |
| `C_EconItemView` | `m_nFallbackSeed` | `0x1D4` | `int32` | pattern seed |
| `C_EconItemView` | `m_flFallbackWear` | `0x1D8` | `float` | 0.0 = factory new, 1.0 = battle-scarred |
| `C_EconItemView` | `m_nFallbackStatTrak` | `0x1DC` | `int32` | StatTrak counter (-1 disables) |

### Hooks

| Function | Module | Signature | Action |
|---|---|---|---|
| `ApplyEconCustomization` | `client.dll` | `ApplyEconCustomization` | Modern paint-apply entry; consumes m_nFallback* and queues composite rebuild. |
| `RegenerateWeaponSkin` | `client.dll` | `RegenerateWeaponSkin` | Legacy static-paint pass; called for completeness. |
| `GetCustomPaintKitIndex` | `client.dll` | `CEconItemView::GetCustomPaintKitIndex` | Read live paint kit to detect rejection and gate re-apply. |

---

## Knife Changer

Spoofs m_nSubclassID on the knife entity, calls UpdateSubclass to re-bind the subclass-data ptr at weapon+0x388 (the per-knife sequence set), then AnimGraphRebuild(controller, 2) to tear down the existing CNmGraphInstance at controller+0x448 and let the manager re-bind from the (now-updated) vdata's animgraph. Without the rebuild the knife mesh swaps but inspect / deploy / swing animations stay on the OLD subclass's sequences (Emerald Butterfly mesh + default-knife inspect anim was the symptom). SetMeshGroupMask refreshes the visible mesh after the subclass change.

### Fields

| Class | Field | Offset | Type | Note |
|---|---|---|---|---|
| `C_BasePlayerWeapon` | `m_nSubclassID` | `0x36C` | `uint32` | knife subclass key (drives mesh + sequences + animgraph) |
| `C_BasePlayerWeapon` | `m_iItemDefinitionIndex` | `0x1BA` | `uint16` | must match the knife type for the chosen subclass |

### Hooks

| Function | Module | Signature | Action |
|---|---|---|---|
| `UpdateSubclass` | `client.dll` | `48 8B 41 10 48 8B D9 8B 50 30` | Re-bind subclass-data ptr at weapon+0x388. |
| `AnimGraphRebuild` | `client.dll` | `AnimGraphRebuild` | Mode = 2: destroy CNmGraphInstance and re-bind. |
| `SetMeshGroupMask` | `client.dll` | `SetMeshGroupMask` | Refresh visible mesh after subclass change. |

---

