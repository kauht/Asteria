# CS2 Signatures

_This file is regenerated on every successful run of `cs2-sdk`._

**512/558 signatures resolved across 18 module(s).**

## `animationsystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `Animation::ShouldUpdateSequences` | `__int64 __fastcall sub_18014F0A0(__int64 a1, __int64 a2, __int64 a3)` | `raw` | `0x7FFC43B9F0A0` | `0x14F0A0` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B 40 48` |
| `CAnimationSystem_FrameUpdate` | `void __fastcall sub_18008B530(__int64 a1)` | `raw` | `0x7FFC43ADB530` | `0x8B530` | `48 89 4C 24 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 C8 EB FF FF B8 38 15 00 00` |

## `client.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `AddNametagEntity` | `char __fastcall sub_18078B070(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFED7B0A0` | `0x78B0A0` | `40 55 53 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B DA` |
| `AddStattrakEntity` | `void __fastcall sub_180A4C790(__int64 a1, unsigned int a2)` | `raw` | `0x7FFBFF03C5D0` | `0xA4C5D0` | `48 8B C4 48 89 58 08 48 89 70 10 57 48 83 EC 50 33 F6 8B FA 48 8B D1` |
| `AnimGraphRebuild` | `__int64 __fastcall sub_1808AEC70(__int64 a1, char a2)` | `raw` | `0x7FFBFEE9EBE0` | `0x8AEBE0` | `40 55 56 48 83 EC 28 4C 89 74 24 58 48 8B F1 80 FA FF 75 04 0F B6 51 18` |
| `ApplyEconCustomization` | `__int64 __fastcall sub_1807A8A90(__int64 a1, char a2)` | `raw` | `0x7FFBFED98AC0` | `0x7A8AC0` | `48 89 5C 24 ? 57 48 83 EC ? 8B FA 48 8B D9 E8 ? ? ? ? 48 8B CB E8 ? ? ? ? 48 85 C0 74` |
| `AutowallInit` | `__int64 __fastcall sub_1808E1EE0(__int64 a1)` | `raw` | `0x7FFBFEED1CE0` | `0x8E1CE0` | `40 53 48 83 EC ? 48 8B D9 48 81 C1 ? ? ? ? E8 ? ? ? ?` |
| `AutowallTraceData` | `char __fastcall sub_18098E9C0(_QWORD *a1, int *a2, int a3, int a4, _BYTE *a5, int a6)` | `raw` | `0x7FFBFEF7E7E0` | `0x98E7E0` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 09` |
| `AutowallTracePos` | `char __fastcall sub_180807780(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEDF7700` | `0x807700` | `40 55 56 41 54 41 55 41 57 48 8B EC` |
| `BulkRegenIterator` | `__int64 __fastcall sub_18078E570(char a1)` | `raw` | `0x7FFBFED7E5A1` | `0x78E5A1` | `57 48 83 EC 40 0F B6 F9 E8 ? ? ? ? 48 85 C0 0F 84` |
| `CAM_ThinkReturn` | `char __fastcall sub_18031A460(__int64 a1, _DWORD *a2)` | `raw` | `0x7FFBFE90A4FF` | `0x31A4FF` | `BA 04 00 00 00 FF 15 ? ? ? ? 84 C0 0F 84` |
| `CAttributeStringFill` | `__int64 __fastcall sub_180EAEC20(__int64 a1, __int64 a2)` | `rel32` | `0x7FFBFF49F150` | `0xEAF150` | `E8 ? ? ? ? 41 83 CF 08` |
| `CAttributeStringInit` | `_QWORD *__fastcall sub_1805F86B0(_QWORD *a1, __int64 a2, char a3)` | `rel32` | `0x7FFBFEBE86B0` | `0x5F86B0` | `E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 7D ? 48 89 45 ? 49 8D 4F` |
| `CBaseEntity_ChangeModel` | `__int64 __fastcall sub_1808DB1C0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEECAFC0` | `0x8DAFC0` | `40 53 48 83 EC ? 48 8B D9 4C 8B C2 48 8B 0D ? ? ? ? 48 8D 54 24` |
| `CBaseEntity_TakeDamageOld` | `unsigned __int64 __fastcall sub_180223D20(__int64 a1, __int64 a2, __int64 **a3)` | `raw` | `0x7FFBFE813D20` | `0x223D20` | `40 55 53 56 57 41 54 48 8D 6C 24 E0 48 81 EC 20 01 00 00 4D 8B E0 48 8B FA 48 8B F1 E8` |
| `CBaseModelEntity::SetBodyGroup` | `` | `raw` | `0x7FFBFEEC9C70` | `0x8D9C70` | `85 D2 0F 88 ? ? ? ? 55 53 56 41 56 48 8B EC 48 83 EC 78` |
| `CBaseModelEntity_SetBodygroup` | `void __fastcall sub_1808D9E70(__int64 a1, int a2, int a3)` | `raw` | `0x7FFBFEEC9C70` | `0x8D9C70` | `85 D2 0F 88 CB 01 00 00 55 53 56 41 56 48 8B EC 48 83 EC 78 45 8B F0 8B DA 48 8B F1 E8 ? ? ?` |
| `CBodyComponent` | `__int64 sub_1801BC160()` | `stringref` | `0x7FFBFE7AC160` | `0x1BC160` | `"CBodyComponent"` |
| `CBodyComponentSkeletonInstance` | `__int64 (__fastcall ***sub_1801C3040())()` | `stringref` | `0x7FFBFE7B3040` | `0x1C3040` | `"CBodyComponentSkeletonInstance"` |
| `CBufferStringInit` | `char __fastcall sub_1817E29D0(__int64 a1, const char *a2)` | `raw` | `0x7FFBFFDD2C50` | `0x17E2C50` | `48 89 5C 24 ? 57 48 83 EC ? 8B 41 ? 48 8D 79` |
| `CCSGOInput::CreateMove` | `double __fastcall sub_180C5E7F0(__int64 a1, unsigned int a2, __int64 a3)` | `raw` | `0x7FFBFF24EC40` | `0xC5EC40` | `48 8B C4 4C 89 40 18 48 89 48 08 55 53 41 54 41 55` |
| `CCSGameRules` | `_QWORD *sub_18007E160()` | `stringref` | `0x7FFBFE66E160` | `0x7E160` | `"CCSGameRules"` |
| `CCSGameRulesProxy` | `__int64 sub_1806E9500()` | `stringref` | `0x7FFBFECD9500` | `0x6E9500` | `"CCSGameRulesProxy"` |
| `CCSInventoryManager::EquipItemInLoadout` | `char __fastcall sub_1807C2150(_QWORD *a1, unsigned int a2, int a3, unsigned __int64 a4)` | `raw` | `0x7FFBFEDB2180` | `0x7C2180` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 89 54 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 0F B7 FA` |
| `CCSPlayer::ThirdPersonReset` | `` | `raw` | `0x7FFBFF0B85A0` | `0xAC85A0` | `48 8B 40 08 44 38 ? 75 10 44 88 ? 01` |
| `CCSPlayerController` | `__int64 __fastcall sub_1807E5220(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFEDD5250` | `0x7E5250` | `"CCSPlayerController"` |
| `CCSPlayerController_ActionTrackingServices` | `__int64 __fastcall sub_1807E5220(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFEDD5250` | `0x7E5250` | `"CCSPlayerController_ActionTrackingServices"` |
| `CCSPlayerController_DamageServices` | `__int64 __fastcall sub_1807E5220(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFEDD5250` | `0x7E5250` | `"CCSPlayerController_DamageServices"` |
| `CCSPlayerController_InGameMoneyServices` | `__int64 __fastcall sub_1807E5220(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFEDD5250` | `0x7E5250` | `"CCSPlayerController_InGameMoneyServices"` |
| `CCSPlayerController_InventoryServices` | `__int64 __fastcall sub_1807E5220(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFEDD5250` | `0x7E5250` | `"CCSPlayerController_InventoryServices"` |
| `CCSPlayerInventory::GetItemInLoadout` | `__int64 *__fastcall sub_1807C3D70(__int64 a1, unsigned int a2, unsigned int a3)` | `raw` | `0x7FFBFEDB3DA0` | `0x7C3DA0` | `40 55 48 83 EC ? 49 63 E8` |
| `CCSPlayerPawn` | `__int64 sub_180BB0E40()` | `stringref` | `0x7FFBFF1A0C80` | `0xBB0C80` | `"CCSPlayerPawn"` |
| `CCSPlayer_BulletServices` | `void *__fastcall sub_180813BA0(__int64 a1)` | `stringref` | `0x7FFBFEE03A90` | `0x813A90` | `"CCSPlayer_BulletServices"` |
| `CCSPlayer_CameraServices` | `__int64 sub_18080FCB0()` | `stringref` | `0x7FFBFEDFFBA0` | `0x80FBA0` | `"CCSPlayer_CameraServices"` |
| `CCSPlayer_HostageServices` | `void *__fastcall sub_180813BA0(__int64 a1)` | `stringref` | `0x7FFBFEE03A90` | `0x813A90` | `"CCSPlayer_HostageServices"` |
| `CCSPlayer_ItemServices` | `void *__fastcall sub_180850B00(__int64 a1)` | `stringref` | `0x7FFBFEE40510` | `0x850510` | `"CCSPlayer_ItemServices"` |
| `CCSPlayer_MovementServices` | `__int64 *sub_18083DE80()` | `stringref` | `0x7FFBFEE2D880` | `0x83D880` | `"CCSPlayer_MovementServices"` |
| `CCSPlayer_MovementServices_CheckJumpButton` | `void __fastcall sub_180ACF410(__int64 a1, __int64 a2, __int64 a3)` | `raw` | `0x7FFBFF0BF250` | `0xACF250` | `4C 89 44 24 18 55 56 41 56 48 8D AC 24 70 EC FF FF B8 90 14 00 00` |
| `CCSPlayer_PingServices` | `void *__fastcall sub_180850ED0(__int64 a1)` | `stringref` | `0x7FFBFEE417B0` | `0x8517B0` | `"CCSPlayer_PingServices"` |
| `CCSPlayer_ProcessForceSubtickMoves` | `` | `raw` | `0x7FFBFEFC5D40` | `0x9D5D40` | `40 55 53 48 8D AC 24 68 FF FF FF 48 81 EC 98 01 00 00 8B 15 ? ? ? ? 48 8B D9 65 48 8B 04 25 58 00 00 00 B9 98 00 00 00 48 8B 04 D0 8B 04 01 39 05 ? ? ? ? 0F 8F B6 07 00 00` |
| `CCSPlayer_QueueForceSubtickMove` | `` | `raw` | `0x7FFBFEFB76E0` | `0x9C76E0` | `48 83 EC 28 8B 0D ? ? ? ? 65 48 8B 04 25 58 00 00 00 BA 98 00 00 00 48 8B 04 C8 8B 04 02 39 05 ? ? ? ? 0F 8F F4 11 00 00` |
| `CCSPlayer_RunCommand_Context` | `void __fastcall sub_1809DBAF0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEFCB940` | `0x9DB940` | `48 8B C4 48 81 EC C8 00 00 00 48 89 58 10 48 89 68 18 48 8B EA 48 89 70 20 48 8B F1 48 89 78 F8` |
| `CCSPlayer_UseServices` | `__int64 sub_1808821D0()` | `stringref` | `0x7FFBFEE71BC0` | `0x881BC0` | `"CCSPlayer_UseServices"` |
| `CCSPlayer_WaterServices` | `__int64 *sub_180877460()` | `stringref` | `0x7FFBFEE66E50` | `0x876E50` | `"CCSPlayer_WaterServices"` |
| `CCSPlayer_WeaponServices` | `__int64 *sub_180877810()` | `stringref` | `0x7FFBFEE67200` | `0x877200` | `"CCSPlayer_WeaponServices"` |
| `CCSWeaponBase` | `__int64 sub_18077F3D0()` | `stringref` | `0x7FFBFED6F400` | `0x77F400` | `"CCSWeaponBase"` |
| `CCSWeaponBaseGun` | `__int64 sub_18077F470()` | `stringref` | `0x7FFBFED6F4A0` | `0x77F4A0` | `"CCSWeaponBaseGun"` |
| `CCSWeaponBaseVData` | `const char *sub_18075A2B0()` | `stringref` | `0x7FFBFED4A2E0` | `0x75A2E0` | `"CCSWeaponBaseVData"` |
| `CCollisionProperty` | `__int64 __fastcall sub_1802E0F90(int a1, __int64 a2, __int64 a3, __int64 a4)` | `stringref` | `0x7FFBFE8D0F90` | `0x2E0F90` | `"CCollisionProperty"` |
| `CCompositeMaterialManager_AddPanoramaPanelRenderRequest_Caller` | `__int64 __fastcall sub_1813BB640(__int64 a1, const char *a2, __int64 a3, __int64 a4)` | `stringref` | `0x7FFBFF9AC004` | `0x13BC004` | `"CCompositeMaterialManager::AddNewPanoramaPanelRenderRequest"` |
| `CDecoyProjectile` | `__int64 sub_18074E1E0()` | `stringref` | `0x7FFBFED3E210` | `0x74E210` | `"CDecoyProjectile"` |
| `CEconItemCreateInstance` | `uintptr_t __cdecl CEconItemCreateInstance()` | `raw` | `0x7FFBFF5E7CA0` | `0xFF7CA0` | `48 83 EC 28 B9 48 00 00 00 E8` |
| `CEconItemSchema::GetAttributeDefinitionByName` | `__int64 __fastcall sub_18104CEA0(__int64 a1, unsigned __int8 *a2)` | `raw` | `0x7FFBFF63D3D0` | `0x104D3D0` | `48 89 5C 24 10 48 89 6C 24 18 57 41 56 41 57 48 83 EC 60 48 8D 05` |
| `CEconItemView::GetCustomPaintKitIndex` | `__int64 __fastcall sub_1810A8A60(__int64 *a1)` | `raw` | `0x7FFBFF698F90` | `0x10A8F90` | `48 89 5C 24 ? 57 48 83 EC ? 8B 15 ? ? ? ? 48 8B F9 65 48 8B 04 25 ? ? ? ? B9 ? ? ? ? 48 8B 04 D0 8B 04 01 39 05 ? ? ? ? 0F 8F ? ? ? ? E8 ? ? ? ? 8B 58 ? 39 1D ? ? ? ? 74 ? E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 89 05 ? ? ? ? 89 1D ? ? ? ? EB ? 48 8B 05 ? ? ? ? 48 85 C0 74` |
| `CEntitySystem_QueuePostDataUpdates` | `` | `raw` | `0x7FFBFFA9E590` | `0x14AE590` | `48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 80 B9 DA 0B 00 00 00 49 8B D8 8B FA 48 8B F1 74 61` |
| `CFlashbangProjectile` | `__int64 sub_180FE03F0()` | `stringref` | `0x7FFBFF5D0971` | `0xFE0971` | `"CFlashbangProjectile"` |
| `CFogController` | `__int64 sub_18027EFD0()` | `stringref` | `0x7FFBFE86EFD0` | `0x27EFD0` | `"CFogController"` |
| `CGameEntitySystem::OnAddEntity` | `__int64 __fastcall sub_180968640(__int64 a1, __int64 a2, int a3)` | `raw` | `0x7FFBFEF58460` | `0x968460` | `48 89 74 24 ? 57 48 83 EC ? 41 B9 ? ? ? ? 41 8B C0 41 23 C1 48 8B F2 41 83 F8 ? 48 8B F9 44 0F 45 C8 41 81 F9 ? ? ? ? 73 ? FF 81` |
| `CGameEntitySystem::OnRemoveEntity` | `__int64 __fastcall sub_180968EA0(__int64 a1, _QWORD *a2, int a3)` | `raw` | `0x7FFBFEF58CC0` | `0x968CC0` | `48 89 74 24 ? 57 48 83 EC ? 41 B9 ? ? ? ? 41 8B C0 41 23 C1 48 8B F2 41 83 F8 ? 48 8B F9 44 0F 45 C8 41 81 F9 ? ? ? ? 73 ? FF 89` |
| `CGameSceneNode` | `__int64 __fastcall sub_1801A38F0(int a1, __int64 a2)` | `stringref` | `0x7FFBFE793B30` | `0x1A3B30` | `"CGameSceneNode"` |
| `CGameSceneNode_BuildBoneMergeWork` | `char __fastcall sub_18093FA40(__int64 a1, _QWORD *a2, char a3)` | `raw` | `0x7FFBFEF2F860` | `0x93F860` | `40 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 50 48 8D 6C 24 50 80 A1 06 01 00 00 FB 4C 8B F9 80` |
| `CGameSceneNode_PerformBatchedInvalidatePhysicsRecursive` | `void __fastcall sub_18093E660(char a1)` | `raw` | `0x7FFBFEF2E480` | `0x93E480` | `40 57 48 81 EC 90 00 00 00 84 C9 74 4D BF 01 00 00 00 F0 0F C1 3D ? ? ? ? FF C7 83 FF 01 0F 85 63 05 00 00 48 8D 0D ? ? ? ? 48 8D 15` |
| `CGameSceneNode_StartHierarchicalAttachment` | `char __fastcall sub_18098C5E0(__int64 a1)` | `raw` | `0x7FFBFEF7C400` | `0x98C400` | `48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 83 EC 30 48 8B F9 8B` |
| `CGameTrace_TraceShape_Client` | `bool __fastcall sub_18098EAA0(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4, _BYTE *a5, __int64 a6)` | `raw` | `0x7FFBFEF7E8C0` | `0x98E8C0` | `48 89 5C 24 20 48 89 4C 24 08 55 57 41 54 41 55 41 56 48 8D AC 24 10 E0 FF FF B8 F0 20 00 00` |
| `CGlowProperty` | `__int64 __fastcall sub_1802E11A0(int a1, __int64 a2, __int64 a3, __int64 a4)` | `stringref` | `0x7FFBFE8D11A0` | `0x2E11A0` | `"CGlowProperty"` |
| `CGlowProperty_OnGlowTypeChanged` | `__int64 __fastcall sub_180B0CD90(__int64 a1)` | `raw` | `0x7FFBFF0FCBD0` | `0xB0CBD0` | `48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 8B D9 F3 0F 10 41 4C` |
| `CHEGrenadeProjectile` | `__int64 sub_180FE0490()` | `stringref` | `0x7FFBFF5D09D0` | `0xFE09D0` | `"CHEGrenadeProjectile"` |
| `CLoopModeGame_OnPostDataUpdate` | `` | `raw` | `0x7FFBFEF9B920` | `0x9AB920` | `48 89 5C 24 08 48 89 74 24 18 55 57 41 56 48 8B EC 48 83 EC 50 45 8B F1 48 8B FA 48 8B F1 45 85` |
| `CMolotovProjectile` | `__int64 sub_18074E3C0()` | `stringref` | `0x7FFBFED3E3F0` | `0x74E3F0` | `"CMolotovProjectile"` |
| `CPaintKitDefinitions_FindOrCreateByName` | `char __fastcall sub_18105A690(__int64 a1, __int64 a2, char *a3, __int64 a4)` | `stringref` | `0x7FFBFF64ABC0` | `0x105ABC0` | `"Kit "[%s]" specified, but doesn't exist!! You're probably missing an entry in items_paintkits.txt or items_stickerkits.txt or need to run with -use_local_item_data\n"` |
| `CPaintKitDefinitions_LoadDefaultKit` | `char __fastcall sub_18102C760(__int64 a1, KeyValues *a2, _DWORD *a3)` | `stringref` | `0x7FFBFF61CC90` | `0x102CC90` | `"Unable to find "default" paint kit in "paint_kits_rarity""` |
| `CPlantedC4_Use` | `` | `raw` | `0x7FFBFEDA05B0` | `0x7B05B0` | `40 55 53 56 48 8D AC 24 C0 FE FF FF 48 81 EC 40 02 00 00 48 8B DA 48 8B F1 BA FF FF FF FF` |
| `CPostProcessingVolume` | `__int64 sub_1802A3D60()` | `stringref` | `0x7FFBFE893D60` | `0x2A3D60` | `"CPostProcessingVolume"` |
| `CS2ItemEditor_BuildTemplateMaterialFromFile` | `CKeyValues_Data *__fastcall sub_1813BCA50(__int64 a1, const char *a2)` | `raw` | `0x7FFBFF9AD180` | `0x13BD180` | `48 89 54 24 10 55 53 41 55 41 57 48 8D AC 24 18 F9 FF FF 48 81 EC E8 07 00 00 4C 8B FA 48 85 D2` |
| `CSBaseGunFireData_fn` | `void __fastcall sub_1814E8140(__int64 a1)` | `raw` | `0x7FFBFFAD8870` | `0x14E8870` | `48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 68 A8 48 81 EC ? ? ? ? 4C 8B 69` |
| `CSGOInput_CreateMove` | `double __fastcall sub_180C5E7F0(__int64 a1, unsigned int a2, __int64 a3)` | `raw` | `0x7FFBFF24EC40` | `0xC5EC40` | `48 8B C4 4C 89 40 18 48 89 48 08 55 53 41 54 41 55 48 8D A8 F8 FE FF FF` |
| `CSkeletonInstance` | `__int64 __fastcall sub_1801A3A20(int a1, __int64 a2)` | `stringref` | `0x7FFBFE793C60` | `0x1A3C60` | `"CSkeletonInstance"` |
| `CSkeletonInstance::SetMeshGroupMask` | `__int64 __fastcall sub_180A2DB50(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFF01D990` | `0xA2D990` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 99` |
| `CSkeletonInstance_GetTransformsForHitboxList` | `char __fastcall sub_180A1A6C0(__int64 a1, __int64 a2, int *a3)` | `raw` | `0x7FFBFF00A500` | `0xA1A500` | `48 89 5C 24 18 55 56 57 41 55 41 57 48 81 EC A0 00 00 00 49 63 28 4D 8B F8 48 8B FA 48 8B D9 85` |
| `CSkeletonInstance_OnBodyGroupChoiceChanged` | `__int64 __fastcall sub_180A25310(__int64 a1, __int64 a2, int a3, _DWORD *a4)` | `raw` | `0x7FFBFF015150` | `0xA25150` | `48 89 5C 24 08 57 48 83 EC 20 49 63 D8 49 8B F9 45 85 C0 78 20 3B 99 18 02 00 00 7D 18` |
| `CSkeletonInstance_OnSkeletonModelChanged` | `__int64 __fastcall sub_180A25520(__int64 a1, __int64 a2, __int64 *a3)` | `raw` | `0x7FFBFF015360` | `0xA25360` | `49 8B 00 48 89 81 B8 00 00 00 C6 81 B0 00 00 00 01 C3` |
| `CSkeletonInstance_PostDataUpdate` | `char __fastcall sub_180A264B0(__int64 a1, __int64 a2, __int64 a3)` | `raw` | `0x7FFBFF0162F0` | `0xA262F0` | `48 8B C4 4C 89 40 18 89 50 10 55 57 48 8D A8 68 FE FF FF 48 81 EC 88 02 00 00 48 89 70 E0 48 8B` |
| `CSkeletonInstance_SetMaterialGroup` | `void __fastcall sub_180A2C830(__int64 a1, unsigned int a2)` | `raw` | `0x7FFBFF01C670` | `0xA2C670` | `3B 91 C4 03 00 00 74 24 89 91 C4 03 00 00 48 8B 81 28 02 00 00 48 85 C0 74 12` |
| `CSkeletonInstance_SetMeshGroupMask` | `void __fastcall sub_180A25480(__int64 a1, __int64 a2, _QWORD *a3)` | `raw` | `0x7FFBFF0152C0` | `0xA252C0` | `48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 49 8B 00 49 8B F8 48 8B F2 48 8B D9 48 39 81 C8 01` |
| `CSmokeGrenadeProjectile` | `__int64 sub_18074E460()` | `stringref` | `0x7FFBFED3E490` | `0x74E490` | `"CSmokeGrenadeProjectile"` |
| `CSource2Client_Shutdown` | `__int64 sub_180AE5B90()` | `raw` | `0x7FFBFF0D59D0` | `0xAE59D0` | `48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 81 EC 40 02 00 00 8B 0D ? ? ? ? BA 02 00 00` |
| `CTonemapController2` | `__int64 sub_180257C90()` | `stringref` | `0x7FFBFE847C90` | `0x257C90` | `"CTonemapController2"` |
| `CUserCmd_ParseSubtickDuration` | `` | `raw` | `0x7FFBFE69D420` | `0xAD420` | `40 55 48 8D AC 24 70 FD FF FF 48 81 EC 90 03 00 00 F2 0F 10 05 ? ? ? ? 48 8D 05` |
| `CUserCmd_ParseSubtickFraction` | `` | `raw` | `0x7FFBFE69D760` | `0xAD760` | `40 55 48 8D AC 24 40 FE FF FF 48 81 EC C0 02 00 00 F2 0F 10 05 ? ? ? ? 48 8D 05` |
| `CUtlVector_CompositeMaterialInput_AddToTail` | `__int64 __fastcall sub_180789C50(int *a1, __int64 a2)` | `raw` | `0x7FFBFED79C80` | `0x789CD2` | `41 B9 88 02 00 00 8B 57 14 81 E2 FF FF FF 3F 8D 71 01 44 8B C6 FF 15` |
| `C_AttributeContainer` | `__int64 __fastcall sub_180C18BB0(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFF209010` | `0xC19010` | `"C_AttributeContainer"` |
| `C_BaseEntity` | `__int64 (__fastcall *sub_18004E260())()` | `stringref` | `0x7FFBFE63E260` | `0x4E260` | `"C_BaseEntity"` |
| `C_BaseEntity_CheckPredictionForceReLatch` | `__int64 __fastcall sub_180B47910(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFF137750` | `0xB47750` | `48 8B C4 48 89 50 10 53 55 56 48 81 EC 00 01 00 00 0F 29 78 98 48 8B F2 8B 91 04 01 00 00` |
| `C_BaseEntity_ProcessInterpolatedList` | `__int64 __fastcall sub_180A6BDD0(__int64 a1, unsigned int a2, int a3, unsigned int a4)` | `raw` | `0x7FFBFF05BC10` | `0xA6BC10` | `4C 8B DC 49 89 5B 10 49 89 6B 18 49 89 73 20 57 41 54 41 57 48 83 EC 60 49 C7 43 B0 E1 07 00 00` |
| `C_BaseEntity_RestoreData` | `void __fastcall sub_180A71610(__int64 a1, const char *a2, unsigned int a3, int a4)` | `raw` | `0x7FFBFF061450` | `0xA71450` | `40 55 53 56 41 54 41 57 48 8D AC 24 20 FF FF FF 48 81 EC E0 01 00 00 48 8B D9 45 8B E1 48 8B 89` |
| `C_BaseEntity_SaveData` | `void __fastcall sub_180A71820(_QWORD *a1, const char *a2, __int64 a3, int a4, int a5, unsigned int a6, __int64 a7)` | `raw` | `0x7FFBFF061660` | `0xA71660` | `48 8B C4 55 56 57 41 56 41 57 48 8D A8 E8 FD FF FF 48 81 EC F0 02 00 00 48 83 B9 A0 05 00 00 00` |
| `C_BaseEntity_StartParticleSystem` | `` | `raw` | `0x7FFBFF393890` | `0xDA3890` | `48 89 5C 24 08 55 48 8B EC 48 83 EC 40 E8 ? ? ? ? 48 8D 05 ? ? ? ? 33 DB 48 8D 15` |
| `C_BaseModelEntity` | `__int64 __fastcall sub_180158010(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFE7481E0` | `0x1581E0` | `"C_BaseModelEntity"` |
| `C_BasePlayerPawn` | `__int64 (__fastcall *sub_18006DA20())()` | `stringref` | `0x7FFBFE65DA20` | `0x6DA20` | `"C_BasePlayerPawn"` |
| `C_CSPlayerPawn` | `__int64 __fastcall sub_1806C2430(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFECB2430` | `0x6C2430` | `"C_CSPlayerPawn"` |
| `C_CSPlayerPawnBase` | `__int64 *sub_180BD7140()` | `stringref` | `0x7FFBFF1C6FF0` | `0xBD6FF0` | `"C_CSPlayerPawnBase"` |
| `C_CSWeaponBase` | `_QWORD *__fastcall sub_180742170(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFED321A0` | `0x7421A0` | `"C_CSWeaponBase"` |
| `C_CSWeaponBase_GetEconWpnData` | `__int64 __fastcall sub_180795180(__int64 a1)` | `raw` | `0x7FFBFED851B0` | `0x7951B0` | `40 53 48 83 EC 40 48 8B D9 E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 85 C0 75 ? 48 8B 43 10` |
| `C_EconEntity_BuildLegacyGloveSkinMaterial` | `void __fastcall sub_180BC1460(int *a1)` | `stringref` | `0x7FFBFF1B1310` | `0xBC1310` | `"MapPlayerPreview gloves"` |
| `C_EconEntity_BuildLegacyWeaponSkinMaterial` | `void __fastcall sub_18078C2A0(__int64 a1, char a2)` | `stringref` | `0x7FFBFED7C2D0` | `0x78C2D0` | `"workshop preview weapon"` |
| `C_EconEntity_BuildModernWeaponSkinMaterial` | `void __fastcall sub_180D84F90(__int64 a1, _QWORD *a2, __int64 a3, int a4, char a5, char a6, __int64 a7)` | `raw` | `0x7FFBFF375490` | `0xD85490` | `48 85 C9 0F 84 ? ? 00 00 48 8B C4 48 89 50 10 48 89 48 08 55 41 54 41 56 41 57 48 8D A8 B8 FA` |
| `C_EconEntity_BuildNametagOverlayMaterial` | `char __fastcall sub_18078B070(__int64 a1, __int64 a2)` | `stringref` | `0x7FFBFED7B0A0` | `0x78B0A0` | `"low-res nametag"` |
| `C_EconItemView` | `_QWORD *__fastcall sub_18070B570(int a1, _QWORD *a2)` | `stringref` | `0x7FFBFECFB5A0` | `0x70B5A0` | `"C_EconItemView"` |
| `C_EconWearable_OnNewCustomMaterials` | `__int64 __fastcall sub_1810B9090(__int64 a1, char a2)` | `stringref` | `0x7FFBFF6A95C0` | `0x10B95C0` | `"Invalid EconItemView -- Can't create custom materials for wearable, debug this.\n"` |
| `C_Hostage` | `__int64 (__fastcall *sub_1800E7480())()` | `stringref` | `0x7FFBFE6D7480` | `0xE7480` | `"C_Hostage"` |
| `C_Inferno` | `__int64 (__fastcall *sub_1800F7440())()` | `stringref` | `0x7FFBFE6E7440` | `0xF7440` | `"C_Inferno"` |
| `C_PlantedC4` | `__int64 (__fastcall *sub_1800F07A0())()` | `stringref` | `0x7FFBFE6E07A0` | `0xF07A0` | `"C_PlantedC4"` |
| `C_SmokeGrenadeProjectile` | `__int64 (__fastcall *sub_180095A10())()` | `stringref` | `0x7FFBFE685A10` | `0x95A10` | `"C_SmokeGrenadeProjectile"` |
| `CacheParticleEffect` | `` | `raw` | `0x7FFBFE7F7BC0` | `0x207BC0` | `4C 8B DC 53 48 81 EC ? ? ? ? F2 0F 10 05` |
| `CalcSpread` | `` | `raw` | `0x7FFBFF26F0A0` | `0xC7F0A0` | `48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 4C 63 EA` |
| `CalcViewmodel` | `void __fastcall sub_18084F430(__int64 a1, float *a2, float *a3)` | `raw` | `0x7FFBFEE3EE40` | `0x84EE40` | `40 55 53 56 41 56 41 57 48 8B EC` |
| `CalcViewmodelTransform_v2` | `__int64 __fastcall sub_1807A24F0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFED92520` | `0x7A2520` | `48 89 5C 24 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 80 48 81 EC 80 01 00 00 48 8B FA` |
| `CalcViewmodelView` | `__int64 __fastcall sub_180C6BF20(__int64 a1, __int64 a2, _DWORD *a3)` | `raw` | `0x7FFBFF25C3D0` | `0xC6C3D0` | `40 53 48 83 EC 60 48 8B 41 08 49 8B D8 8B 48 30 48 C1 E9 0C F6 C1 01 0F 85 48 01 00 00 41 B8 07` |
| `CalculateInterpolation` | `int *__fastcall sub_1814C7E70(__int64 a1, int *a2)` | `rel32` | `0x7FFBFFAB85A0` | `0x14C85A0` | `E8 ? ? ? ? 8B 45 ? 3B 45 60 75 04 32 D2 EB 09 BA 01 00 00 00 41 0F 4C D5 C0 EA 07 84 D2 0F 85 87` |
| `CalculateWorldSpaceBones` | `void __fastcall sub_180A0B070(__int64 a1, unsigned int a2)` | `raw` | `0x7FFBFEFFAEB0` | `0xA0AEB0` | `48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8D 6C 24 ? 48 8B 81` |
| `ClearHUDWeaponIcon` | `__int64 __fastcall sub_180DEDDD0(__int64 a1, int a2, __int64 a3)` | `rel32` | `0x7FFBFF3DE300` | `0xDEE300` | `E8 ? ? ? ? 8B F8 C6 84 24 ? ? ? ? ?` |
| `Client::CCSGOHudVote_OnVoteResult` | `void __fastcall sub_180E14250(__int64 a1, int a2, const char *a3, int a4, __int64 a5)` | `raw` | `0x7FFBFF404250` | `0xE14250` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 81 EC 90 01 00 00 65 48 8B 04 25 58 00 00 00 49 8B E8 44 8B 15 ? ? ? ? 8B FA` |
| `Client::CCSGO_HudChat_OnSayText2` | `void __fastcall sub_1810C3D50(int a1, __int64 a2)` | `raw` | `0x7FFBFF6B3D50` | `0x10C3D50` | `48 89 5C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 70 F3 FF FF 48 81 EC 90 0D 00 00 81 A5 DC 0C 00 00 FF FF 0F FF 33 F6 8B 5A 6C 48 8B` |
| `Client::CCSPlayer_MovementServices_ValidateVelocity` | `void __fastcall sub_1808476D0(__int64 movementServices)` | `stringref` | `0x7FFBFEE376D0` | `0x8476D0` | `"CCSPlayer_MovementServices(%s):  %d/%s Got a NaN velocity on %s\n"` |
| `Client::CLegacyGameUI_Initialize` | `__int64 __fastcall sub_180CA6A40(__int64 thisptr)` | `stringref` | `0x7FFBFF296A40` | `0xCA6A40` | `"CLegacyGameUI::Initialize() failed to get necessary interfaces\n"` |
| `Client::CPrediction_Update` | `__int64 __fastcall sub_180B4DA50(__int64 thisptr, int reason)` | `raw` | `0x7FFBFF13DA50` | `0xB4DA50` | `48 8B C4 89 50 ? 48 89 48 ? 55 53 57` |
| `Client::C_BasePlayerPawn_PrePhysicsSimulate` | `bool __fastcall sub_1808CF580(__int64 pawn)` | `stringref` | `0x7FFBFEEBF580` | `0x8CF580` | `"C_BasePlayerPawn::PrePhysicsSimulate"` |
| `Client::C_DispatchEffect` | `__int64 __fastcall sub_180ACDB70(const char *name, __int64 data)` | `stringref` | `0x7FFBFF0BDB70` | `0xACDB70` | `"DispatchEffect: effect "%s" not found on client\n"` |
| `Client::C_GameRules_ctor` | `__int64 __fastcall sub_180B03BD0(__int64 thisptr)` | `stringref` | `0x7FFBFF0F3BD0` | `0xB03BD0` | `"%s:  CGameRules::CGameRules constructed\n"` |
| `Client::C_PlantedC4_ClientThink` | `_DWORD *__fastcall sub_180C09800(__int64 plantedC4)` | `stringref` | `0x7FFBFF1F9800` | `0xC09800` | `"C4.ExplodeTriggerTrip"` |
| `ClientModeCSNormal_OnEvent` | `void __fastcall sub_180C5C660(__int64 a1, KeyValues *a2)` | `raw` | `0x7FFBFF24CAB0` | `0xC5CAB0` | `40 53 57 48 81 EC 78 02 00 00 48 8B CA 48 8B FA` |
| `Client_DispatchSpawn` | `__int64 __fastcall sub_1814D5B10(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4)` | `raw` | `0x7FFBFFAC6240` | `0x14D6240` | `4C 8B DC 55 56 48 83 EC 78 49 8B 68 08 48 8B F1 48 85 ED 0F 84 72 01 00 00 49 89 5B 08 49 8D 4B` |
| `CompositeMaterialPanoramaPanel_Init` | `__int64 __fastcall sub_180B91260(__int64 a1, __int64 a2, __int64 a3)` | `stringref` | `0x7FFBFF1810A0` | `0xB910A0` | `"CompositeMaterialPanoramaPanel_t::Init"` |
| `ComputeRandomSeed` | `__int64 __fastcall sub_180C7E2D0(__int64 a1, __int64 a2, int a3)` | `raw` | `0x7FFBFF26E780` | `0xC7E780` | `48 89 5C 24 ? 57 48 81 EC ? ? ? ? ? ? ? ? 48 8D 8C 24` |
| `ConCommand_firstperson` | `__int64 sub_180ACA2B0()` | `raw` | `0x7FFBFF0BA0F0` | `0xACA0F0` | `48 83 EC 28 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 08 03 00 00 83 7C 24 ? 00 75 ? 48 8B 05 ? ? ? ? C6 80 29 02 00 00 00 C7 80 A8 06 00 00 00` |
| `ConCommand_thirdperson` | `__int64 sub_180ACA390()` | `raw` | `0x7FFBFF0BA1D0` | `0xACA1D0` | `48 83 EC 38 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 08 03 00 00 83 7C 24 ? 00 0F 85 ? ? ? ? 4C 8B 05 ? ? ? ? 41 8B 80 50 0B 00 00` |
| `ConvarGet` | `void __fastcall sub_1808BE720(__int64 a1, unsigned int *a2)` | `raw` | `0x7FFBFEEAF5A2` | `0x8BF5A2` | `8B D0 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F 10 45 ? 83 F0 74` |
| `CreateBaseTypeCache` | `` | `raw` | `0x7FFBFFB015D0` | `0x15115D0` | `40 53 48 83 EC ? 4C 8B 49 ? 44 8B D2` |
| `CreateEconItem` | `` | `raw` | `0x7FFBFF5E7CA0` | `0xFF7CA0` | `48 83 EC 28 B9 48 00 00 00 E8 ? ? ? ? 48 85` |
| `CreateEntityByClassName` | `__int64 __fastcall sub_181604AB0(__int64 a1, int a2, __int64 a3, __int64 a4)` | `raw` | `0x7FFBFFBF4EC6` | `0x1604EC6` | `4C 8D 05 ? ? ? ? 4C 8B CF BA 03 00 00 00 FF 15 ? ? ? ? EB ? 0F B7 C8 48` |
| `CreateInterface` | `__int64 __fastcall CreateInterface(__int64 a1, _DWORD *a2)` | `raw` | `0x7FFBFFE25A10` | `0x1835A10` | `4C 8B 0D ? ? ? ? 4C 8B D2 4C 8B D9 4D 85 C9 74 ? 49 8B 41 08` |
| `CreateNewSubtickMoveStep` | `__int64 __fastcall sub_1804B1D80(__int64 a1)` | `rel32` | `0x7FFBFEAA1D80` | `0x4B1D80` | `E8 ? ? ? ? 48 8B D0 48 8B CE E8 ? ? ? ? 48 8B C8` |
| `CreateParticleEffect` | `__int64 __fastcall sub_180987020(int a1, int a2, int a3, __int64 a4, int a5)` | `raw` | `0x7FFBFEF76E40` | `0x986E40` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? F3 0F 10 1D ? ? ? ? 41 8B F8 8B DA 4C 8D 05` |
| `CreateSOSubclassEconItem` | `__int64 sub_180FF7770()` | `raw` | `0x7FFBFF5E7CA0` | `0xFF7CA0` | `48 83 EC 28 B9 48 00 00 00 E8 ? ? ? ? 48 85` |
| `DamageFeedbackEmitter` | `void __fastcall sub_18081FB40(__int64 a1, _QWORD *a2, __int64 a3)` | `raw` | `0x7FFBFEE0FA30` | `0x81FA30` | `48 89 4C 24 08 55 53 41 54 41 55 41 57 48 8D AC 24 E0 FE FF FF 48 81 EC 20 02 00 00 48 83 79 38` |
| `DestroyParticle` | `void __fastcall sub_1809463E0(__int64 a1, __int64 a2, unsigned __int8 a3, char a4)` | `raw` | `0x7FFBFEF36200` | `0x946200` | `83 FA ? 0F 84 ? ? ? ? 41 54` |
| `DispatchEffect` | `__int64 __fastcall sub_18035A570(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFE94A570` | `0x35A570` | `48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 48 8B DA 48 8D 4C 24` |
| `DispatchSpawn_caller` | `__int64 __fastcall sub_1814D5B10(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4)` | `raw` | `0x7FFBFFAC6240` | `0x14D6240` | `4C 8B DC 55 56 48 83 EC 78 49 8B 68 08 48 8B F1 48 85 ED 0F 84 72 01 00 00` |
| `DispatchUpdateOnRemove` | `` | `raw` | `0x7FFBFFAC3CE0` | `0x14D3CE0` | `48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 41 56 41 57 48 8B EC 48 83 EC 60 48 8D B9 80 00 00 00 45 33 FF 4D 8B F0` |
| `DrawCrosshair` | `bool __fastcall sub_1807B0BF0(_QWORD *a1)` | `raw` | `0x7FFBFEDA0C20` | `0x7B0C20` | `48 89 5C 24 08 57 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 85` |
| `DrawLegs` | `void __fastcall sub_1810F0410(__int64 *a1, __int64 *a2, __int64 a3, __int64 a4, __int64 a5)` | `raw` | `0x7FFBFF6E0940` | `0x10F0940` | `40 55 53 56 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? F2 0F 10 42` |
| `DrawOverHead` | `unsigned __int8 __fastcall sub_180A66CF0(__int64 a1, unsigned int a2)` | `raw` | `0x7FFBFF056B30` | `0xA66B30` | `40 53 48 83 EC ? 48 8B D9 83 FA ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 10` |
| `DrawScopeOverlay` | `__int64 __fastcall sub_18085D530(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEE4CE70` | `0x85CE70` | `48 8B C4 53 57 48 83 EC ? 48 8B FA` |
| `DrawSmokeVertex` | `__int64 __fastcall sub_180C7B290(__int64 a1, __int64 a2, int a3, int a4, __int64 a5, __int64 a6)` | `raw` | `0x7FFBFF26B740` | `0xC7B740` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 48 8B 9C 24 ? ? ? ? 4D 8B F8` |
| `EmitSoundByHandle` | `__int64 __fastcall sub_180B63B10(__int64 a1, int a2, int a3, __int64 a4)` | `raw` | `0x7FFBFF153950` | `0xB63950` | `40 53 48 83 EC 30 4C 89 4C 24 20 48 8B D9 45 8B C8 4C 8B C2 48 8B D1 48 8D 0D ?? ?? ?? ?? E8` |
| `FX_FireBullets` | `void sub_180C7E380(unsigned int a1, __int64 a2, __int64 a3, __int64 *a4, __int64 a5, int a6, int a7, ...)` | `raw` | `0x7FFBFF26E830` | `0xC7E830` | `48 8B C4 4C 89 48 20 48 89 50 10 55 53 57 41 54 41 55 48 8D A8 58 FB FF FF 48 81 EC A0 05` |
| `FindHudElement` | `_QWORD **__fastcall sub_180DC1D50(__int64 a1, unsigned __int8 a2)` | `raw` | `0x7FFBFF3B23C8` | `0xDC23C8` | `48 8D 15 ? ? ? ? 45 33 C0 B9 ? ? ? ? FF 15 ? ? ? ? EB ? 48 8B 15` |
| `FindHudElement_panorama` | `__int64 __fastcall sub_180DC3E70(const char *a1)` | `raw` | `0x7FFBFF3B43A0` | `0xDC43A0` | `4C 8B DC 53 48 83 EC 50 48 8B 05` |
| `FindSOCache` | `__int64 __fastcall sub_18181F080(__int64 a1, int *a2, __int64 a3, __int64 a4)` | `raw` | `0x7FFBFFE0F300` | `0x181F300` | `48 89 5C 24 08 57 48 83 EC 30 4C 8B 52 08 48 8B D9 8B 0A` |
| `FirstPersonLegs` | `void __fastcall sub_1810F0410(__int64 *a1, __int64 *a2, __int64 a3, __int64 a4, __int64 a5)` | `raw` | `0x7FFBFF6E0940` | `0x10F0940` | `40 55 53 56 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? F2 0F 10 42` |
| `FlashOverlay` | `void __fastcall sub_180DAB2C0(__int64 a1, int a2)` | `raw` | `0x7FFBFF39B7D0` | `0xDAB7D0` | `85 D2 0F 88 ? ? ? ? 48 89 4C 24` |
| `ForceButtonsDown` | `void __fastcall sub_1809D0130(_QWORD *a1, __int64 a2)` | `raw` | `0x7FFBFEFBFF20` | `0x9CFF20` | `40 53 57 41 56 48 81 EC ? ? ? ? 48 83 79` |
| `GameEventManager_AddListener` | `__int64 __fastcall sub_180939FF0(__int64 a1, __int64 a2, const char *a3, unsigned __int8 a4)` | `raw` | `0x7FFBFEF29E10` | `0x939E10` | `48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 50 41 0F B6 E9 48 8D 99 E0 00 00 00 49 8B F0` |
| `GameEventManager_UnserializeEvent` | `__int64 __fastcall sub_180992900(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEF82720` | `0x992720` | `48 8B C4 48 89 50 10 55 41 54 41 55 41 56 48 8D 68 D8 48 81 EC 08 01 00 00 48 89 58 D8 4C 8D B1` |
| `GetAttributeDefByName` | `` | `raw` | `0x7FFBFF63D3D0` | `0x104D3D0` | `48 89 5C 24 10 48 89 6C 24 18 57 41 56 41 57 48 83 EC 60 48 8D 05` |
| `GetBaseEntity` | `__int64 __fastcall sub_180967600(__int64 a1, int a2)` | `raw` | `0x7FFBFEF57420` | `0x967420` | `4C 8D 49 ? 81 FA` |
| `GetBonePositionByName` | `__int64 __fastcall sub_1808C81E0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEEB7FF0` | `0x8C7FF0` | `40 53 48 83 EC ? 48 8B 89 ? ? ? ? 48 8B DA 48 8B 01 FF 50 ? 48 8B C8` |
| `GetCSInvMgr_call` | `` | `rel32` | `0x7FFBFEDB6460` | `0x7C6460` | `E8 ? ? ? ? 48 8B D8 8B F7` |
| `GetChatObject` | `__int64 sub_1810C3670()` | `rel32` | `0x7FFBFF6B3BA0` | `0x10C3BA0` | `E8 ? ? ? ? 48 8B E8 48 85 C0 0F 84 ? ? ? ? 4C 8D 05` |
| `GetClientSystem` | `__int64 *sub_181036570()` | `rel32` | `0x7FFBFF626AA0` | `0x1036AA0` | `E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 8B D8 85 C0 74 33` |
| `GetControllerCmd` | `__int64 __fastcall sub_1808BDC00(__int64 a1, int a2)` | `raw` | `0x7FFBFEEADBA0` | `0x8BDBA0` | `40 53 48 83 EC 20 8B DA E8 ? ? ? ? 4C` |
| `GetEconItemSystem` | `__int64 sub_180379830()` | `raw` | `0x7FFBFE969830` | `0x379830` | `48 83 EC 28 48 8B 05 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 48 89 5C 24` |
| `GetEntityByIndex` | `__int64 __fastcall sub_180967600(__int64 a1, int a2)` | `raw` | `0x7FFBFEF57420` | `0x967420` | `4C 8D 49 ? 81 FA` |
| `GetEntityHandle` | `__int64 __fastcall sub_18094E8D0(__int64 a1)` | `raw` | `0x7FFBFEF3E6F0` | `0x94E6F0` | `48 85 C9 74 32 48 8B 49 10 48 85 C9 74 29 44 8B 41 10 BA` |
| `GetGlowColor` | `void __fastcall sub_180B0ABC0(__int64 a1, float *a2)` | `raw` | `0x7FFBFF0FAA00` | `0xB0AA00` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 48 8B 54 24` |
| `GetHitGroup` | `__int64 __fastcall sub_180A17C40(__int64 a1)` | `raw` | `0x7FFBFF007A80` | `0xA17A80` | `40 53 48 83 EC 20 48 83 79 10 00 48 8B D9 74 16 E8 ?? ?? ?? ?? 84 C0 75 0D 48 8B 43 10 8B 40 38` |
| `GetInt2_Event` | `__int64 __fastcall sub_1804AAB40(__int64 a1, unsigned int a2, int a3)` | `raw` | `0x7FFBFEA9AB40` | `0x4AAB40` | `48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 20 48 63 FA 41` |
| `GetInventoryManager` | `__int64 *sub_1807C6430()` | `rel32` | `0x7FFBFEDB6460` | `0x7C6460` | `E8 ? ? ? ? 48 8B D3 48 8B C8 4C 8B 00 41 FF 90 00 02` |
| `GetItemViewByID` | `uintptr_t __fastcall GetItemViewByID(uintptr_t, uint64_t)` | `raw` | `0x7FFBFF63FCD0` | `0x104FCD0` | `48 89 54 24 ? 53 48 83 EC ? 48 8B D9 48 85 D2 75 ? 33 C0 48 83 C4 ? 5B C3 48 83 C1 38 48 8D` |
| `GetLocalControllerById` | `__int64 __fastcall sub_1808E1070(int a1)` | `raw` | `0x7FFBFEED0E70` | `0x8E0E70` | `48 83 EC 28 83 F9 FF 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 08 48 63 C1 4C 8D 05` |
| `GetLocalPawn` | `__int64 __fastcall sub_1808E1070(int a1)` | `raw` | `0x7FFBFEED0E70` | `0x8E0E70` | `48 83 EC ? 83 F9 ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? ? ? ? FF 90 ? ? ? ? ? ? 48 63 C1 4C 8D 05` |
| `GetLocalPlayer_dispatcher` | `__int64 sub_180379200()` | `raw` | `0x7FFBFE969200` | `0x379200` | `48 83 EC 38 48 8B 05 ? ? ? ? 48 85 C0 0F 85 14 06 00 00 48 89 5C 24 40 B9 50 00 00 00 48 89` |
| `GetMatrixForView` | `double __fastcall sub_180169C50(__int64 a1, __int64 a2, __int64 a3)` | `raw` | `0x7FFBFE759C50` | `0x169C50` | `40 53 48 83 EC 60 0F 29 74 24 50 0F 57 DB F3 0F 10 ? ? ? ? ? 49 8B D8` |
| `GetPlayerByIndex_export` | `__int64 sub_180F00910()` | `raw` | `0x7FFBFF4F0E40` | `0xF00E40` | `48 83 EC 28 4C 8D 05 ? ? ? ? 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 4C 8D` |
| `GetPlayerInterp` | `float __fastcall sub_1808B9460(__int64 a1)` | `raw` | `0x7FFBFEEA9400` | `0x8B9400` | `40 53 48 83 EC ? 48 8B D9 48 8B 0D ? ? ? ? 48 83 C1` |
| `GetRemovedAimPunch_E8` | `__int64 __fastcall sub_18084D6E0(__int64 a1, __int64 a2)` | `rel32` | `0x7FFBFEE3D050` | `0x84D050` | `E8 ? ? ? ? 4C 8B C0 48 8D 55 ? 48 8B CB E8 ? ? ? ? 48 8D 0D` |
| `GetRemovedAimpunch` | `__int64 sub_1801128E0()` | `raw` | `0x7FFBFE702947` | `0x112947` | `F2 0F 10 44 24 ? F2 0F 11 84 24 ? ? ? ? FF 15` |
| `GetSurfaceData` | `__int64 __fastcall sub_180953540(__int64 a1)` | `rel32` | `0x7FFBFEF43360` | `0x953360` | `E8 ? ? ? ? 80 78 18 00` |
| `GetTickBase` | `__int64 __fastcall sub_1808BDA00(__int64 a1)` | `rel32` | `0x7FFBFEEAD9A0` | `0x8BD9A0` | `E8 ? ? ? ? EB ? 48 8B 05 ? ? ? ? 8B 40` |
| `GetTraceInfo` | `__int64 __fastcall sub_180806F50(__int64 a1, __int64 a2, float a3, unsigned __int64 *a4)` | `raw` | `0x7FFBFEDF6ED0` | `0x806ED0` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 0F 29 74 24 ? 48 8B CA` |
| `GetUserCmdManager` | `__int64 __fastcall sub_1808BDC90(__int64 a1)` | `raw` | `0x7FFBFEEADC30` | `0x8BDC30` | `41 56 41 57 48 83 EC ? 48 8D 54 24` |
| `GetViewAngles` | `__int64 *__fastcall sub_180AD5CA0(__int64 a1, int a2)` | `raw` | `0x7FFBFF0C5AE0` | `0xAD5AE0` | `4C 8B C1 85 D2 74 08 48 8D 05 ? ? ? ? C3` |
| `GetViewModelOffsets` | `void __fastcall sub_18084EE40(__int64 viewmodel, float *outOffsets, float *outFov)` | `raw` | `0x7FFBFEE3EE40` | `0x84EE40` | `40 55 53 56 41 56 41 57 48 8B EC 48 83 EC 20 4D 8B F8 4C 8B F2 48 8B F1 E8` |
| `GetWeaponInAccuracyRecoveryTime` | `__m128 __fastcall sub_180796600(__int64 a1)` | `rel32` | `0x7FFBFED86630` | `0x796630` | `E8 ? ? ? ? F3 0F 10 B7 ? ? ? ? F3 0F 5E F8` |
| `GetWorldFovResolver` | `float __fastcall sub_18080CEF0(__int64 a1)` | `raw` | `0x7FFBFEDFCE70` | `0x80CE70` | `40 53 48 83 EC 50 48 8B D9 E8 ? ? ? ? 48 85 C0 74 ? 48 8B C8 48 83 C4 50 5B E9` |
| `GlobalLightUpdateState` | `_BYTE *__fastcall sub_180A8B5A0(__int64 a1)` | `raw` | `0x7FFBFF07B3E0` | `0xA8B3E0` | `40 57 48 81 EC C0 00 00 00 48 8B F9 BA FF FF FF FF 48 8D 0D ? ? ? ? E8` |
| `GloveApply_PerTick` | `void __fastcall sub_180BC1460(int *a1)` | `raw` | `0x7FFBFF1B1310` | `0xBC1310` | `40 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B B9 A0 00 00 00` |
| `GlowObjectManager_GetInstance` | `__int64 sub_180B0ACD0()` | `raw` | `0x7FFBFF0FAB10` | `0xB0AB10` | `48 8B 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 8B 41 38 C3` |
| `HandleBulletPenetration` | `char __fastcall sub_1808211F0(__int64 a1, float *a2, __int64 a3, int a4, __int64 a5)` | `raw` | `0x7FFBFEE110E0` | `0x8210E0` | `48 8B C4 44 89 48 ? 48 89 50 ? 48 89 48 ? 55` |
| `HandleEntityList` | `__int64 __fastcall sub_1801C3700(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, int a6, int a7)` | `rel32` | `0x7FFBFE7B3700` | `0x1C3700` | `E8 ? ? ? ? 84 C0 74 ? 48 63 03` |
| `HandleTeamIntro` | `void __fastcall sub_180703EB0(__int64 a1, __int64 a2, char *a3)` | `raw` | `0x7FFBFECF3EE0` | `0x703EE0` | `48 83 EC ? ? ? ? ? 44 38 89` |
| `HudChatPrintf` | `__int64 sub_1810C10F0(__int64 a1, unsigned int a2, __int64 a3, ...)` | `rel32` | `0x7FFBFF6B1620` | `0x10C1620` | `E8 ? ? ? ? 49 8B 4E 20 BA ? ? ? ?` |
| `InfoForResourceTypeCCompositeMaterialKit_TypeManager` | `__int64 __fastcall sub_1813D90B0(int a1, __int64 a2)` | `stringref` | `0x7FFBFF9C97E0` | `0x13D97E0` | `"InfoForResourceTypeCCompositeMaterialKit"` |
| `InfoForResourceTypeCCompositeMaterial_TypeManager` | `__int64 __fastcall sub_1813D9600(int a1, __int64 a2)` | `raw` | `0x7FFBFF9C9D30` | `0x13D9D30` | `40 55 41 56 48 83 EC 68 48 8B EA 83 F9 06 0F 87 B4 02 00 00` |
| `InitFilter` | `__int64 __fastcall sub_18032BBF0(__int64 a1, _DWORD *a2, __int64 a3, char a4, char a5)` | `raw` | `0x7FFBFE91BBF0` | `0x32BBF0` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F B6 41 ? 33 FF 24 C9 C7 41 ?` |
| `InitPlayerMovementTraceFilter` | `__int64 __fastcall sub_180840660(__int64 a1, _DWORD *a2, __int64 a3, char a4)` | `raw` | `0x7FFBFEE30000` | `0x840000` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F B6 41 ? 33 FF C7 41 ?` |
| `InitTraceInfo` | `__int64 __fastcall sub_1815FC2A0(__int64 a1)` | `raw` | `0x7FFBFFBEC520` | `0x15FC520` | `40 55 41 55 41 57 48 83 EC` |
| `InsecureEmitter` | `` | `raw` | `0x7FFBFF23D030` | `0xC4D030` | `48 89 5C 24 20 56 48 83 EC 20 48 8B D9 48 89 6C 24 30 48 8B E9 48 8B 0D ? ? ? ? 48 8B 01` |
| `IsGlowing` | `__int64 __fastcall sub_180B0C300(__int64 a1)` | `rel32` | `0x7FFBFF0FC140` | `0xB0C140` | `E8 ? ? ? ? 33 DB 84 C0 0F 84 ? ? ? ? 48 8B 4F` |
| `KillFeedbackEmitter` | `__int64 __fastcall sub_18084B0F0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEE3AA60` | `0x84AA60` | `48 89 5C 24 08 48 89 74 24 18 48 89 7C 24 20 55 41 56 41 57 48 8B EC 48 81 EC 80 00 00 00 44 8B` |
| `LevelInit` | `__int64 __fastcall sub_1808D0100(__int64 a1)` | `raw` | `0x7FFBFEEBFF10` | `0x8CFF10` | `40 55 56 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48` |
| `LoadFileForMe` | `void __fastcall sub_18091BF40(__int64 a1)` | `raw` | `0x7FFBFEF0BD60` | `0x91BD60` | `40 55 57 41 56 48 83 EC 20 4C` |
| `LoadPath` | `void __fastcall sub_1806BB200(signed int *a1, signed int a2, unsigned int a3)` | `rel32` | `0x7FFBFECAB200` | `0x6BB200` | `E8 ? ? ? ? 8B 44 24 2C` |
| `LookupBone` | `__int64 __fastcall sub_1808C81E0(__int64 a1, __int64 a2)` | `rel32` | `0x7FFBFEEB7FF0` | `0x8C7FF0` | `E8 ? ? ? ? 48 8B 8D ? ? ? ? B3` |
| `ModulationUpdate` | `__int64 __fastcall sub_1809DA450(__int64 a1, char a2)` | `raw` | `0x7FFBFEFCA2A0` | `0x9DA2A0` | `48 89 5C 24 08 57 48 83 EC 20 8B FA 48 8B D9 E8 ? ? ? ? 84 C0 0F 84` |
| `NoClipOnChange` | `__int64 __fastcall sub_180166C00(__int64 a1)` | `raw` | `0x7FFBFE756C00` | `0x166C00` | `48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 48 8B EC 48 83 EC 30 48 8D 05` |
| `NoSpread1` | `__int64 __fastcall sub_180C7E2D0(__int64 a1, __int64 a2, int a3)` | `raw` | `0x7FFBFF26E780` | `0xC7E780` | `48 89 5C 24 08 57 48 81 EC F0 00` |
| `PanelConstructorPointer` | `` | `raw` | `0x7FFBFFC1CFA0` | `0x162CFA0` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F1 48 8B FA B9 ? ? ? ? E8 ? ? ? ? 48 8B D8 48 85 C0 74 ? 48` |
| `ParticleCollection` | `__int64 __fastcall sub_1801F4D90(__int64 a1)` | `raw` | `0x7FFBFE7E4D90` | `0x1F4D90` | `48 89 5C 24 ? 57 48 83 EC ? 0F 28 05` |
| `PhysicsRunThink_Ctrl` | `__int64 __fastcall sub_1808D7310(__int64 a1)` | `raw` | `0x7FFBFEEC7110` | `0x8D7110` | `48 89 5C 24 ? 57 48 81 EC ? ? ? ? ? ? ? 48 8B F9 FF 90` |
| `PhysicsRunThink_Pawn` | `char __fastcall sub_180B0ED50(__int64 a1)` | `raw` | `0x7FFBFF0FEB90` | `0xB0EB90` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 8B 81 ? ? ? ? 48 8B F9` |
| `PlayVSound_client` | `__int64 __fastcall sub_18150ED00(__int64 a1)` | `raw` | `0x7FFBFFAFF430` | `0x150F430` | `48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 33 FF` |
| `PointerToGetInaccuracyFunction` | `` | `raw` | `0x7FFBFED85BC0` | `0x795BC0` | `48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 44` |
| `PointerToGetSpreadFunction` | `` | `raw` | `0x7FFBFED86BE0` | `0x796BE0` | `48 83 EC ? 48 63 91` |
| `ProcessImpacts` | `__int64 __fastcall sub_1809CEA50(_QWORD *a1, __int64 a2, __int64 a3)` | `raw` | `0x7FFBFEFBE840` | `0x9CE840` | `48 8B C4 53 56 41 55` |
| `ProcessMovement` | `__int64 __fastcall sub_1809D9A30(__int64 a1, __int64 a2)` | `rel32` | `0x7FFBFEFC9880` | `0x9D9880` | `E8 ? ? ? ? 48 8B 06 48 8B CE FF 90 ? ? ? ? 48 85 DB` |
| `RegenerateWeaponSkin` | `void __fastcall sub_18078C2A0(__int64 a1, char a2)` | `raw` | `0x7FFBFED7C2D0` | `0x78C2D0` | `40 55 53 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 44 0F B6 FA 48 8B D9 BA ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ?` |
| `RegenerateWeaponSkin_v2` | `void __fastcall sub_18078C2A0(__int64 a1, char a2)` | `raw` | `0x7FFBFED7C2D0` | `0x78C2D0` | `40 55 53 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 44 0F B6 FA 48 8B D9 BA ? ? ? ? 48 8D 0D ? ? ? ? E8` |
| `RegenerateWeaponSkins` | `__int64 sub_1807B0D40()` | `raw` | `0x7FFBFEDA0D70` | `0x7B0D70` | `48 83 EC ? E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 48 8B 10` |
| `RenderDecals` | `_BYTE *__fastcall sub_1810ECA50(__int64 a1, __int64 **a2, char a3, char a4)` | `raw` | `0x7FFBFF6DCF80` | `0x10ECF80` | `44 88 4C 24 ? 55 53` |
| `ReportHit` | `char __fastcall sub_180602290(_QWORD *a1)` | `rel32` | `0x7FFBFEBF2290` | `0x602290` | `E8 ? ? ? ? 48 8B AC 24 D8 00 00 00 48 81 C4` |
| `RunCommand` | `void __fastcall sub_1809DBAF0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEFCB940` | `0x9DB940` | `48 8B C4 48 81 EC ? ? ? ? 48 89 58 10` |
| `RunCommand_processor` | `void __fastcall sub_1809DBAF0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEFCB940` | `0x9DB940` | `48 8B C4 48 81 EC C8 00 00 00 48 89 58 10 48 89 68 18 48 8B EA 48 89 70 20 48 8B F1 48 89 78 F8` |
| `SOCreated` | `void __fastcall SOCreated(uintptr_t, uint64_t, uintptr_t, int)` | `raw` | `0x7FFBFE977230` | `0x387230` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B FA 48 8B F1` |
| `Scope_callsite` | `__int64 __fastcall sub_18085D530(__int64 a1, __int64 a2)` | `rel32` | `0x7FFBFEE4CE70` | `0x85CE70` | `E8 ? ? ? ? 80 7C 24 34 ? 74 ?` |
| `SendChatMessage` | `__int64 sub_1810C10F0(__int64 a1, unsigned int a2, __int64 a3, ...)` | `rel32` | `0x7FFBFF6B1620` | `0x10C1620` | `E8 ? ? ? ? 49 8B 4E 20 BA ? ? ? ?` |
| `SetAbsOrigin_Pawn` | `__int64 __fastcall sub_18021EF50(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFE80EF50` | `0x21EF50` | `48 89 5C 24 ? 57 48 83 EC ? ? ? ? 48 8B FA 48 8B D9 FF 90 ? ? ? ? 84 C0 0F 85` |
| `SetBodyGroup_inv` | `void __fastcall sub_180D972A0(__int64 a1, int a2, const char *a3)` | `raw` | `0x7FFBFF3877B0` | `0xD977B0` | `85 D2 0F 88 ? ? ? ? 53 55` |
| `SetCollisionBounds` | `__int64 __fastcall sub_180803980(__int64 a1, __int64 *a2)` | `raw` | `0x7FFBFEDF3980` | `0x803980` | `48 83 EC ? F2 0F 10 02 8B 42 08` |
| `SetDynamicAttributeValue` | `__int64 __fastcall sub_181004F60(__int64 a1, __int64 a2, _DWORD *a3)` | `raw` | `0x7FFBFF5F5490` | `0x1005490` | `48 89 6C 24 ? 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B FA C7 44 24 ? ? ? ? ? 4D 8B F8` |
| `SetDynamicAttributeValue_raw` | `__int64 __fastcall sub_181004F60(__int64 a1, __int64 a2, _DWORD *a3)` | `raw` | `0x7FFBFF5F5490` | `0x1005490` | `48 89 6C 24 ? 57 41 56 41 57 48 81 EC ? ? ? ? 48 8B FA C7 44 24` |
| `SetMeshGroupMask` | `__int64 __fastcall sub_180A2DB50(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFF01D990` | `0xA2D990` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 99 ? ? ? ? 48 8B 71` |
| `SetModel` | `__int64 __fastcall sub_1808DB1C0(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFEECAFC0` | `0x8DAFC0` | `40 53 48 83 EC ? 48 8B D9 4C 8B C2 48 8B 0D ? ? ? ? 48 8D 54 24` |
| `SetPlayerReady` | `char __fastcall sub_180F1DD90(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFF50E2C0` | `0xF1E2C0` | `40 53 48 83 EC 20 48 8B DA 48 8D 15 ? ? ? ? 48 8B CB FF 15 ? ? ? ? 85 C0 75 14 BA` |
| `SetSelectedIndexFunctionPointer` | `` | `raw` | `0x7FFBFFC76E90` | `0x1686E90` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F1 8B DA 48 83` |
| `SetTraceData` | `__int64 __fastcall sub_1807D4810(int *a1, _OWORD *a2)` | `rel32` | `0x7FFBFEDC4840` | `0x7D4840` | `E8 ? ? ? ? 8B 85 ? ? ? ? 48 8D 54 24 ? F2 0F 10 45` |
| `SetTraceInit` | `` | `rel32` | `0x7FFBFF0E7F60` | `0xAF7F60` | `E8 ? ? ? ? F2 0F 10 ? 4C 8D ?` |
| `SetTypeKV3` | `unsigned __int64 *__fastcall sub_18181AEB0(unsigned __int64 *a1, unsigned __int8 a2, unsigned __int8 a3)` | `raw` | `0x7FFBFFE0B130` | `0x181B130` | `40 53 48 83 EC 30 4C 8B 11 41 B9 ? ? ? ? 49 83 CA 01 0F B6 C2 80 FA 06 48 8B D9 44 0F 45 C8` |
| `SetViewAngle` | `void __fastcall sub_180AE4CE0(__int64 a1, int a2, __int64 *a3)` | `raw` | `0x7FFBFF0D4B20` | `0xAE4B20` | `85 D2 75 3D 48 63 81 ? ? ? ?` |
| `SetupCmd` | `__int64 __fastcall sub_1808BAF20(__int64 a1)` | `raw` | `0x7FFBFEEAAEC0` | `0x8BAEC0` | `48 83 EC 28 E8 ? ? ? ? 8B 80` |
| `SetupMove` | `__int64 __fastcall sub_180D1D0E0(__int64 a1, int *a2)` | `raw` | `0x7FFBFF30D5E0` | `0xD1D5E0` | `48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B EA 4C 8B F1 E8 ? ? ? ? 48 8D 15` |
| `SetupMovementMoves` | `__int64 __fastcall sub_181186C10(__int64 a1, __int64 a2, __int64 a3, __int64 a4)` | `raw` | `0x7FFBFF7773BF` | `0x11873BF` | `48 8B ? E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 6C 24 ? 48 83 C4 30` |
| `SharedRandomFloat` | `` | `raw` | `0x7FFBFF01EC90` | `0xA2EC90` | `4C 8B DC 49 89 5B 08 49 89 73 10 57 48 81 EC 00 01 00 00 8B 05 ? ? ? ? 48 8D 54 24 40` |
| `ShowMessageBox` | `` | `raw` | `0x7FFBFF2958B0` | `0xCA58B0` | `44 88 4C 24 ? 53 41 56` |
| `SomeTimingFromPawn` | `float __fastcall sub_180A572B0(__int64 a1, int a2, unsigned int a3)` | `raw` | `0x7FFBFF0470F0` | `0xA570F0` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 63 D8 48 8B F1` |
| `Spawner_PerTickOrchestrator` | `char __fastcall sub_180BC3FE0(_QWORD *a1)` | `raw` | `0x7FFBFF1B3E90` | `0xBC3E90` | `48 8B C4 55 53 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 80 B9 B1 13 00 00 00` |
| `SpectatorInput` | `__int64 __fastcall sub_1807D92E0(_DWORD *a1, __int64 a2, unsigned int a3)` | `raw` | `0x7FFBFEDC9310` | `0x7D9310` | `48 89 5C 24 10 55 56 57 41 56 41 57 48 8B EC 48 83 EC 60 48 8B 01 41 8B F8 48 8B DA 48 8B F1 FF` |
| `SpreadSeedGen` | `__int64 __fastcall sub_180C7E2D0(__int64 a1, __int64 a2, int a3)` | `raw` | `0x7FFBFF26E780` | `0xC7E780` | `48 89 5C 24 08 57 48 81 EC F0 00 00 00 F3 0F 10 0A 48 8D 8C 24 10 01 00 00 41 8B D8 48 8B FA E8` |
| `TestSurfaces` | `void __fastcall sub_180806E30(__int64 a1, float a2, float a3, float a4, int a5, int a6, __int64 a7)` | `raw` | `0x7FFBFEDF6DB0` | `0x806DB0` | `40 53 57 41 56 48 83 EC 50 8B` |
| `ThirdPersonOffHandler` | `__int64 sub_180ACA2B0()` | `raw` | `0x7FFBFF0BA0F0` | `0xACA0F0` | `48 83 EC 28 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 08 03 00 00 83 7C 24 ? 00 75 ? 48 8B 05 ? ? ? ? C6 80 29 02 00 00 00 C7 80 A8 06 00 00 00` |
| `ThirdPersonOnHandler` | `__int64 sub_180ACA390()` | `raw` | `0x7FFBFF0BA1D0` | `0xACA1D0` | `48 83 EC 38 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 08 03 00 00 83 7C 24 ? 00 0F 85 ? ? ? ? 4C 8B 05 ? ? ? ? 41 8B 80 50 0B 00 00` |
| `TraceCreate` | `char __fastcall sub_180804900(__int64 a1, __int64 a2, int a3, __int64 a4, int a5, char a6)` | `raw` | `0x7FFBFEDF4860` | `0x804860` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 50 F2 0F 10 02` |
| `TraceGetInfo` | `__int64 __fastcall sub_180806F50(__int64 a1, __int64 a2, float a3, unsigned __int64 *a4)` | `raw` | `0x7FFBFEDF6ED0` | `0x806ED0` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 60 48 8B E9 0F 29 74 24` |
| `TraceHandleBulletPen` | `char __fastcall sub_1808211F0(__int64 a1, float *a2, __int64 a3, int a4, __int64 a5)` | `raw` | `0x7FFBFEE110E0` | `0x8210E0` | `48 8B C4 44 89 48 20 48 89 50 10 48 89 48 08 55 57 41 57` |
| `TraceInitData` | `__int64 __fastcall sub_180800580(__int64 a1)` | `raw` | `0x7FFBFEDF05B0` | `0x8005B0` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8D 79 ? 33 F6 C7 47` |
| `TraceInitFilter` | `__int64 __fastcall sub_18032BBF0(__int64 a1, _DWORD *a2, __int64 a3, char a4, char a5)` | `raw` | `0x7FFBFE91BBF0` | `0x32BBF0` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F B6 41 ? 33 FF 24` |
| `TraceInitInfo` | `__int64 __fastcall sub_1815FC2A0(__int64 a1)` | `raw` | `0x7FFBFFBEC520` | `0x15FC520` | `40 55 41 55 41 57 48 83 EC 30` |
| `TracePlayerBBox` | `__int64 __fastcall sub_180B70E30(__int64 a1, __int64 *a2, __int64 *a3)` | `raw` | `0x7FFBFF160C70` | `0xB70C70` | `48 89 5C 24 ? 55 57 41 54 41 55 41 56` |
| `TraceShape` | `bool __fastcall sub_18098EAA0(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4, _BYTE *a5, __int64 a6)` | `raw` | `0x7FFBFEF7E8C0` | `0x98E8C0` | `48 89 5C 24 ? 48 89 4C 24 ? 55 57` |
| `TraceShape_Client` | `bool __fastcall sub_18098EAA0(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4, _BYTE *a5, __int64 a6)` | `raw` | `0x7FFBFEF7E8C0` | `0x98E8C0` | `48 89 5C 24 20 48 89 4C 24 08 55 57 41 54 41 55 41 56 48 8D AC 24 10 E0 FF FF B8 F0 20 00 00` |
| `TraceToExit` | `char __fastcall sub_180804900(__int64 a1, __int64 a2, int a3, __int64 a4, int a5, char a6)` | `raw` | `0x7FFBFEDF4860` | `0x804860` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? F2 0F 10 02` |
| `UntrustedFlagSetter` | `` | `raw` | `0x7FFBFE746B45` | `0x156B45` | `74 26 C6 05 ? ? ? ? 01 33 C0 83 F8 01` |
| `UpdateGlobalVars` | `void *__fastcall sub_180AE4730(__int64 a1, void *a2)` | `raw` | `0x7FFBFF0D4570` | `0xAE4570` | `48 8B 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 85 D2` |
| `UpdateOnRemove` | `` | `raw` | `0x7FFBFFABA280` | `0x14CA280` | `48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B D9 C6 05 ? ? ? ? 01 48 8B 49` |
| `UpdatePostProcessing` | `void __fastcall sub_180F21F20(__int64 a1, _BYTE *a2)` | `raw` | `0x7FFBFF512450` | `0xF22450` | `48 85 D2 0F 84 ? ? ? ? 48 89 5C 24 08 57 48 83 EC 60 80` |
| `UpdateSkybox` | `__int64 __fastcall sub_18025A850(__int64 a1)` | `raw` | `0x7FFBFE84A850` | `0x25A850` | `48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? 48 8B 47` |
| `UpdateSubClass` | `void __fastcall sub_1801FA930(_QWORD *a1)` | `raw` | `0x7FFBFE7EA930` | `0x1FA930` | `4C 8B DC 53 48 81 EC ? ? ? ? 48 8B 41 10 48 8B D9 8B 50 30 C1 EA 04` |
| `UpdateTurningInAccuracy` | `float *__fastcall sub_1807AFDA0(float *a1)` | `rel32` | `0x7FFBFED9FDD0` | `0x7AFDD0` | `E8 ? ? ? ? F3 0F 10 87 ? ? ? ? 44 0F 2F C8` |
| `ViewModelHideZoomed` | `__int64 __fastcall sub_1807A0460(__int64 a1, __int64 a2, __int64 **a3)` | `raw` | `0x7FFBFED90490` | `0x7A0490` | `48 89 5C 24 20 55 56 57 41 54 41 56 48 8B EC 48 83 EC 50 48 8D 05` |
| `WriteSubtickFromEntry` | `` | `raw` | `0x7FFBFF246780` | `0xC56780` | `48 89 5C 24 ? 55 57 41 56 48 8D 6C 24 ? 48 81 EC B0 00 00 00 8B 01 48 8B F9 81 4A 10 00 02` |
| `create_move_v2` | `void __fastcall sub_180ACC120(__int64 *a1, int a2, char a3)` | `raw` | `0x7FFBFF0BBF60` | `0xACBF60` | `85 D2 0F 85 ? ? ? ? 48 8B C4 44 88 40` |
| `draw_smoke_array` | `__int64 __fastcall sub_180C7B380(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, unsigned int *a6)` | `raw` | `0x7FFBFF26B830` | `0xC7B830` | `40 55 41 54 41 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 8B E2` |
| `draw_view_punch_v2` | `float *__fastcall sub_1808041C0(int a1, __int64 a2, __int64 a3, float *a4, float *a5, float *a6)` | `raw` | `0x7FFBFEDF4120` | `0x804120` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 49 8B E9 49 8B F8` |
| `frame_stage_notify` | `__int64 __fastcall sub_180AD28A0(__int64 a1, int a2)` | `raw` | `0x7FFBFF0C2B71` | `0xAD2B71` | `4C 8B 0D ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 8F ? ? ? ? F3 41 0F 10 51 ? 45 8B 49 ? 0F 5A D2 66 49 0F 7E D0 FF 15 ? ? ? ? 48 8B 97 ? ? ? ? 48 8B 0D ? ? ? ? E8 ? ? ? ? E9` |
| `get_fov` | `float *__fastcall sub_1808041C0(int a1, __int64 a2, __int64 a3, float *a4, float *a5, float *a6)` | `raw` | `0x7FFBFEDF4120` | `0x804120` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 49 8B E9 49 8B F8` |
| `get_map_name` | `__int64 sub_180EDD4F0()` | `raw` | `0x7FFBFF4CDA20` | `0xEDDA20` | `48 83 EC ? 48 8B 0D ? ? ? ? ? ? ? FF 90 ? ? ? ? 48 8B C8 48 83 C4` |
| `get_view_angles_v2` | `void __fastcall sub_180AD4600(__int64 a1, int a2, __int64 a3)` | `raw` | `0x7FFBFF0C4440` | `0xAD4440` | `4D 85 C0 74 ? 85 D2 74` |
| `get_view_model` | `void __fastcall sub_18084F430(__int64 a1, float *a2, float *a3)` | `raw` | `0x7FFBFEE3EE40` | `0x84EE40` | `40 55 53 56 41 56 41 57 48 8B EC` |
| `is_demo_or_hltv` | `char sub_180EFE9B0()` | `raw` | `0x7FFBFF4EEEE0` | `0xEFEEE0` | `48 83 EC ? 48 8B 0D ? ? ? ? ? ? ? FF 90 ? ? ? ? 84 C0 75 ? 38 05` |
| `level_init_v2` | `__int64 __fastcall sub_180AFA990(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFF0EA7D0` | `0xAFA7D0` | `40 55 56 41 56 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 0D` |
| `level_shutdown` | `__int64 sub_180AFAC10()` | `raw` | `0x7FFBFF0EAA50` | `0xAFAA50` | `48 83 EC ? 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ? 45 33 C9 45 33 C0 ? ? ? FF 50 ? 48 85 C0 74 ? 48 8B 0D ? ? ? ? 48 8B D0 ? ? ? 41 FF 50 ? 48 83 C4` |
| `mark_interp_latch_flags_dirty` | `void __fastcall sub_180218070(__int64 a1, unsigned int a2)` | `raw` | `0x7FFBFE808070` | `0x218070` | `40 53 56 57 48 83 EC ? 80 3D ? ? ? ? 00` |
| `on_add_entity_v2` | `__int64 __fastcall sub_180968BB0(__int64 a1, __int64 a2, __int64 a3)` | `raw` | `0x7FFBFEF589D0` | `0x9689D0` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 8B 81 ? ? ? ? 49 8B F0` |
| `override_view_short` | `void __fastcall sub_180C5F840(__int64 a1, __int64 a2)` | `raw` | `0x7FFBFF24FC90` | `0xC5FC90` | `40 57 48 83 EC ? 48 8B FA E8 ? ? ? ? BA` |
| `paintkit_prefab` | `__int64 __fastcall sub_18105D3B0(__int64 *a1)` | `stringref` | `0x7FFBFF64D8E0` | `0x105D8E0` | `"set item texture prefab"` |
| `paintkit_seed` | `__int64 __fastcall sub_180EF1330(__int64 a1)` | `stringref` | `0x7FFBFF4E1860` | `0xEF1860` | `"set item texture seed"` |
| `paintkit_wear` | `__int64 __fastcall sub_180EF1330(__int64 a1)` | `stringref` | `0x7FFBFF4E1860` | `0xEF1860` | `"set item texture wear"` |
| `remove_legs` | `void __fastcall sub_1810F0410(__int64 *a1, __int64 *a2, __int64 a3, __int64 a4, __int64 a5)` | `raw` | `0x7FFBFF6E0940` | `0x10F0940` | `40 55 53 56 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? F2 0F 10 42` |
| `statTrak_killEater` | `__int64 __fastcall sub_180EF1330(__int64 a1)` | `stringref` | `0x7FFBFF4E1860` | `0xEF1860` | `"kill eater"` |
| `statTrak_scoreType` | `__int64 sub_18011B7F0()` | `stringref` | `0x7FFBFE70B7F0` | `0x11B7F0` | `"kill eater score type"` |
| `unlock_inventory` | `char __fastcall sub_1807011C0(__int64 a1)` | `raw` | `0x7FFBFECF11F0` | `0x7011F0` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B E9 48 8B 0D ? ? ? ? ? ? ? FF 50` |
| `update_global_vars` | `void *__fastcall sub_180AE4730(__int64 a1, void *a2)` | `raw` | `0x7FFBFF0D4570` | `0xAE4570` | `48 8B 0D ? ? ? ? 4C 8D 05 ? ? ? ? 48 85 D2` |
| `update_post_processing_v2` | `void __fastcall sub_180F264C0(__int64 a1)` | `raw` | `0x7FFBFF516A06` | `0xF26A06` | `48 89 AC 24 ? ? ? ? 45 33 ED` |

## `engine2.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CCommand_Tokenize` | `` | `raw` | `0x7FFC50FCD260` | `0x3FD260` | `48 89 6C 24 20 4C 89 44 24 18 56 57 41 54 41 56 41 57 48 83 EC 70 48 8B F2 49 8B E8 8B 51 08 4C` |
| `CGameClient_ClientCommand` | `char sub_1800A1240(__int64 a1, int a2, __int64 a3, ...)` | `raw` | `0x7FFC50C71240` | `0xA1240` | `48 8B C4 4C 89 40 18 4C 89 48 20 55 53 57 48 8D 68 A1 48 81 EC C0 00 00 00 33 FF 48 63 DA 48 39` |
| `CHLTVClient_ExecuteStringCommand` | `char __fastcall sub_180120D70(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50CF0D70` | `0x120D70` | `40 53 56 48 81 EC 48 07 00 00 48 8B F1 48 8B DA 48 8B 4A 48 48 83 E1 FC 48 83 79 18 0F 76 03 48` |
| `CNetworkGameClientBase_ForceDemoRecordingFullUpdateAfterNextDeltaPacket` | `char __fastcall sub_1800292B0(__int64 a1, const char *a2)` | `raw` | `0x7FFC50BF92B0` | `0x292B0` | `48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 1D ? ? ? ? 48 8B FA 48 8B F1 48 85 DB` |
| `CNetworkGameClient_ProcessTick` | `char __fastcall sub_18006AAF0(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50C3AAF0` | `0x6AAF0` | `48 89 5C 24 20 55 57 41 57 48 81 EC F0 00 00 00 8B 7A 50 45 33 FF 44 38 3D ? ? ? ? 48 8B EA` |
| `CServerSideClient_ExecuteStringCommand` | `__int64 __fastcall sub_1800BE120(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50C8E120` | `0xBE120` | `40 55 53 56 48 8D AC 24 50 FA FF FF 48 81 EC B0 06 00 00 48 8B D9 48 8B F2 48 8B 4A 48` |
| `CSplitScreenSlot` | `char __fastcall sub_18024A250(__int64 a1, __int64 a2, int a3, __int64 a4)` | `stringref` | `0x7FFC50E1A250` | `0x24A250` | `"CSplitScreenSlot"` |
| `Cvar_RegisterConCommand` | `_QWORD *__fastcall sub_1803FD270(_QWORD *a1, __int64 a2, __int128 *a3, __int64 a4, __int64 a5, __int128 *a6)` | `raw` | `0x7FFC50FCCDC0` | `0x3FCDC0` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 60 44 8B 15 ? ? ? ? 48 8B D9 65 48` |
| `Cvar_RegisterConVar` | `__int128 *__fastcall sub_1803FC080(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4, __int128 *a5)` | `raw` | `0x7FFC50FCBBD0` | `0x3FBBD0` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 81 EC D0 00 00` |
| `Cvar_RevertFlaggedCvars_OnSvCheatsChange` | `void __fastcall sub_18009C1F0(__int64 a1, __int64 a2, _BYTE *a3, char *a4)` | `raw` | `0x7FFC50C6C1F0` | `0x9C1F0` | `40 53 48 83 EC 20 48 8B 41 08 48 8B D9 8B 50 30 48 C1 EA 0C F6 C2 01 0F 85` |
| `DisablePvsAccessor` | `__int64 __fastcall sub_18023D2A0(_DWORD *a1, __int64 a2, int a3, char a4)` | `raw` | `0x7FFC50E0D3D2` | `0x23D3D2` | `48 8D 0D ? ? ? ? 33 D2 FF 50` |
| `Engine::CClient_SendMovePacket` | `char __fastcall sub_180064F80(__int64 a1)` | `raw` | `0x7FFC50C34F80` | `0x64F80` | `40 55 57 41 55 48 8D AC 24 90 E0 FF FF B8 70 20 00 00 E8 ? ? ? ? 48 2B E0 4C 8B E9 C7 44 24 20 FF FF FF FF` |
| `Engine::CGameEventSystem_PostEventAbstract` | `__int64 __fastcall sub_180215830(_BYTE *a1, unsigned int a2, char a3, int a4, __int64 *a5, __int64 a6, __int64 a7, __int64 a8, char a9)` | `raw` | `0x7FFC50DE5830` | `0x215830` | `48 89 5C 24 10 48 89 74 24 18 48 89 7C 24 20 55 41 54 41 55 41 56 41 57 48 8D 6C 24 F1 48 81 EC A0 00 00 00 4C 8B 65 67 4C 8B F1` |
| `Engine::CHLTVClient_SendSnapshot` | `char __fastcall sub_180121FC0(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50CF1FC0` | `0x121FC0` | `48 89 54 24 10 48 89 4C 24 08 55 53 56 57 41 56 41 57 48 8D 6C 24 88 48 81 EC 78 01 00 00 48 8D 05 ? ? ? ? 48 C7 45 18 7A 02 00 00` |
| `Engine::CHLTVClient_SetSignonState` | `char __fastcall sub_180123630(__int64 a1, int a2, __int64 a3, int a4)` | `raw` | `0x7FFC50CF3630` | `0x123630` | `40 55 53 41 55 41 56 41 57 48 8D 6C 24 C9 48 81 EC E0 00 00 00 45 8B E8 8B DA 4C 8B F9 45 33 F6` |
| `Engine::CHostStateMgr_HostStateRequest_Start` | `void __fastcall sub_180218DF0(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50DE8DF0` | `0x218DF0` | `40 53 48 83 EC 40 8B 01 48 8B D9 C6 41 18 01 83 F8 02 74 07 83 F8 04 75 21 EB 0D 8B 49 20 83 E9 06 74 17 83 F9 01 74 12` |
| `Engine::CInputService_ProcessConVar` | `void __fastcall sub_1801C30B0(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50D930B0` | `0x1C30B0` | `48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 55 41 54 41 55 41 56 41 57 48 8D AC 24 40 F3 FF FF 48 81 EC C0 0D 00 00` |
| `Engine::CNetworkGameClient_InternalProcessPacketEntities` | `void __fastcall sub_1800483A0(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50C183A0` | `0x483A0` | `40 55 56 57 41 56 41 57 48 8D AC 24 40 FF FF FF 48 81 EC C0 01 00 00 65 48 8B 04 25 58 00 00 00` |
| `Engine::CNetworkGameClient_ProcessServerInfo` | `char __fastcall sub_18006B120(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50C3B120` | `0x6B120` | `48 89 5C 24 08 57 48 83 EC 30 48 8B FA 48 8B D9 8B 0D ? ? ? ? BA 02 00 00 00 FF 15` |
| `Engine::CNetworkStringTableContainer_CreateStringTable` | `__int64 __fastcall sub_18010C690(__int64 a1, const char *a2, __int64 a3)` | `raw` | `0x7FFC50CDC690` | `0x10C690` | `40 53 41 56 48 83 EC 48 4C 8B F2 48 8B D9 48 8B 12 48 85 D2 0F 84 ? ? ? ? 80 79 34 00` |
| `Engine::CNetworkStringTableContainer_WriteUpdateMessageAtTick` | `__int64 __fastcall sub_18010D310(__int64 a1, __int64 a2, int a3, int a4, int a5)` | `raw` | `0x7FFC50CDD310` | `0x10D310` | `44 89 4C 24 20 44 89 44 24 18 48 89 4C 24 08 55 53 56 57 41 54 41 55 41 57 48 8D 6C 24 F0` |
| `Engine::CServerSideClient_ProcessServerInfo` | `char __fastcall sub_180084B00(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50C54B00` | `0x84B00` | `48 89 5C 24 20 55 56 57 41 54 41 56 48 8D AC 24 10 FE FF FF 48 81 EC F0 02 00 00` |
| `Engine::GetScreenAspectRatio` | `float __fastcall sub_1800769D0(__int64 a1, int a2, int a3)` | `raw` | `0x7FFC50C469D0` | `0x769D0` | `48 89 5C 24 08 57 48 83 EC 20 8B FA 48 8D 0D` |
| `Engine::Host_FilterTime` | `bool __fastcall sub_180210BF0(__int64 a1, float *a2)` | `raw` | `0x7FFC50DE0BF0` | `0x210BF0` | `48 89 5C 24 10 48 89 74 24 18 48 89 4C 24 08 57 48 81 EC A0 00 00 00 48 8B BC 24 D0 00 00 00` |
| `Engine::RunPrediction` | `void __fastcall sub_180066490(__int64 a1, unsigned int a2)` | `raw` | `0x7FFC50C36490` | `0x66490` | `40 55 41 56 48 83 EC ? 80 B9` |
| `Engine_Disconnect_main` | `__int64 *sub_1801D1510()` | `raw` | `0x7FFC50DA1510` | `0x1D1510` | `48 89 5C 24 20 55 57 41 54 48 8B EC 48 83 EC 70 45 33 E4 48 C7 05` |
| `Engine_HLTVClient_ExecuteStringCommand` | `char __fastcall sub_180120D70(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50CF0D70` | `0x120D70` | `40 53 56 48 81 EC 48 07 00 00 48 8B F1 48 8B DA 48 8B 4A 48 48 83 E1 FC 48 83 79 18 0F 76 03 48` |
| `Engine_HostStateMgr_QueueNewRequest` | `__int64 __fastcall sub_18021AFC0(__int64 a1, __int64 a2)` | `raw` | `0x7FFC50DEAFC0` | `0x21AFC0` | `48 89 6C 24 18 48 89 7C 24 20 41 56 48 83 EC 30 48 8B EA 48 8B F9 8B 0D ? ? ? ? BA 02 00 00` |
| `Engine_LoadGameInfo` | `char __fastcall sub_18018D760(__int64 a1, const char *a2)` | `raw` | `0x7FFC50D5D760` | `0x18D760` | `40 55 56 41 56 48 8D 6C 24 F0 48 81 EC 10 01 00 00 4C 8B F1 C7 44 24 40 00 00 00 00 48 8B CA 48` |
| `Engine_MountAddon` | `void __fastcall sub_180193440(__int64 a1, const char *a2, char a3)` | `raw` | `0x7FFC50D63440` | `0x193440` | `48 85 D2 0F 84 DA 0A 00 00 48 8B C4 44 88 40 18 55 57 41 54 41 57 48 8D A8 C8 FC FF FF 48 81 EC` |
| `Engine_NetTimeoutDisconnect` | `__int64 __fastcall sub_180069780(__int64 a1, unsigned int a2, __int64 a3)` | `raw` | `0x7FFC50C39780` | `0x69780` | `40 53 55 56 57 41 56 48 81 EC 80 00 00 00 0F 29 74 24 70 49 8B F8` |
| `Engine_NetworkGameClient_Connect` | `void __fastcall sub_18007F400(__int64 a1, int a2, unsigned int a3, __int64 a4, unsigned int a5, char a6)` | `raw` | `0x7FFC50C4F400` | `0x7F400` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 40 44 89 81 3C 02 00 00 49 8B E9 44 8B` |
| `Engine_NetworkGameClient_SetSignonState` | `char __fastcall sub_180060F80(__int64 a1, unsigned int a2, unsigned int a3, __int64 a4)` | `raw` | `0x7FFC50C30F80` | `0x60F80` | `44 89 44 24 18 89 54 24 10 55 53 56 57 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC D0 00 00 00 8B` |
| `Engine_RegisterConCommand` | `_QWORD *__fastcall sub_1803FD270(_QWORD *a1, __int64 a2, __int128 *a3, __int64 a4, __int64 a5, __int128 *a6)` | `raw` | `0x7FFC50FCCDC0` | `0x3FCDC0` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 60 44 8B 15` |
| `Engine_RegisterConVar` | `__int128 *__fastcall sub_1803FC080(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4, __int128 *a5)` | `raw` | `0x7FFC50FCBBD0` | `0x3FBBD0` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 81 EC D0 00 00` |
| `IsInGame` | `bool sub_180076450()` | `raw` | `0x7FFC50C46450` | `0x76450` | `48 8B 05 ? ? ? ? 48 85 C0 74 ? 80 B8 ? ? ? ? 00 75 ? 83 B8 ? ? ? ? ? 7C` |

## `inputsystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CInputSystem_AttachToWindow` | `int __fastcall sub_1800039F0(__int64 a1, HWND a2)` | `raw` | `0x7FFCFBD939F0` | `0x39F0` | `48 89 5C 24 20 55 48 83 EC 20 48 63 41 30 48 8B EA 33 D2 48 8B D9 85 C0 7E 20 4C 8B C0 8B CA` |
| `SDL_EventHandler` | `void __fastcall SDL_EventHandler(__int64 a1, SDL_Event* event)` | `raw` | `0x7FFCFBD94F01` | `0x4F01` | `53 48 81 EC ? ? ? ? 8B 02 48 8B DA 2D 00 04 00 00` |

## `matchmaking.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CMatchSessionOfflineCustom_InitializeGameSettings` | `char __fastcall sub_1800EE6A0(__int64 a1)` | `raw` | `0x7FFC5EADE6A0` | `0xEE6A0` | `40 53 48 81 EC 40 01 00 00 48 89 BC 24 58 01 00 00 48 8D 15 ? ? ? ? 48 8B F9 41 B0 01 48 8B 49 10 FF 15 ? ? ? ? 48 8B D8 48 85 C0 74 59` |
| `CMatchSessionOnlineHost_InitializeGameSettings` | `char __fastcall sub_1800F0460(__int64 a1)` | `raw` | `0x7FFC5EAE0460` | `0xF0460` | `48 8B C4 53 48 81 EC 80 01 00 00 48 89 70 10 48 8D 15 ? ? ? ? 48 89 78 18 4C 89 60 F0` |

## `materialsystem2.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CMaterial2_CompileComboAndGetVariables_DynamicShaderCompile` | `char __fastcall sub_180013FA0(__int64 a1, __int64 a2)` | `stringref` | `0x7FFCA3093FA0` | `0x13FA0` | `"CompileComboAndGetVariables_DynamicShaderCompile(), C:\buildworker\csgo_rel_win64\build\src\materialsystem2\material2.cpp:2786"` |
| `CMaterial2_GetMode` | `__int64 __fastcall sub_18000BD40(__int64 a1, unsigned int *a2)` | `raw` | `0x7FFCA308BD40` | `0xBD40` | `48 89 5C 24 18 57 48 83 EC 30 8B 02 48 8B D9 39 05 ? ? ? ? 48 8B 0D ? ? ? ? 48 89 74 24` |
| `CMaterial2_GetVertexShaderInputSignature` | `__int64 __fastcall sub_18000C8C0(__int64 a1)` | `raw` | `0x7FFCA308C8C0` | `0xC8C0` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 56 48 83 EC 30 F6 41 0B 01 4C 8B` |
| `CMaterial2_LoadShadersAndSetupModes` | `__int64 __fastcall sub_180010040(__int64 a1, __int64 a2, unsigned int a3)` | `raw` | `0x7FFCA3090040` | `0x10040` | `44 89 44 24 18 48 89 54 24 10 53 56 41 54 41 55 48 81 EC 88 00 00 00 4C 8B E9 48 C7 44 24 60` |
| `CMaterialLayer_ApplyMaterialVarsForBatch` | `` | `raw` | `0x7FFCA3098B80` | `0x18B80` | `4C 89 4C 24 20 4C 89 44 24 18 48 89 54 24 10 53 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 78` |
| `CMaterialLayer_BuildPassCommandData` | `int __fastcall sub_180018F80(__int64 a1, int a2, __int64 a3)` | `raw` | `0x7FFCA3098F80` | `0x18F80` | `89 54 24 10 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 58 FE FF FF 48 81 EC A8 02 00 00` |
| `CMaterialLayer_ComputeWorkItemsToSetupStaticCombosForMode` | `char __fastcall sub_180015BC0(unsigned __int16 *a1, unsigned int a2, int *a3)` | `stringref` | `0x7FFCA3095F3C` | `0x15F3C` | `"CMaterialLayer::ComputeWorkItemsToSetupStaticCombosForMode(3154): Failed call to FindOrLoadStaticComboData()!\n"` |
| `CMaterialLayer_CreateCommandBuffer` | `__int64 __fastcall sub_180019820(__int64 a1, __int64 a2, int a3, int a4, _DWORD *a5)` | `stringref` | `0x7FFCA3099820` | `0x19820` | `"\nCMaterialLayer::CreateCommandBuffer(4446): Find a graphics programmer! Trying to bind a "%s" shader that doesn't exist! for %s\n"` |
| `CMaterialSystem2_BindIdentityInstanceIDBufferAndSetRenderState` | `char __fastcall sub_180070000(__int64 *a1, __int64 a2, __int64 a3, __int64 a4)` | `stringref` | `0x7FFCA30F0000` | `0x70000` | `"BindIdentityInstanceIDBufferAndSetRenderState: GetMode == NULL? Can't Render\n"` |
| `CMaterialSystem2_DynamicShaderCompile_ProcessQueue` | `void __fastcall sub_18003A200(__int64 a1)` | `stringref` | `0x7FFCA30BA5E0` | `0x3A5E0` | `"Compiling %i shaders:"` |
| `CMaterialSystem2_DynamicShaderCompile_ReloadAndSync` | `void sub_1800355C0()` | `raw` | `0x7FFCA30B55C1` | `0x355C2` | `48 83 EC 20 48 8B 35 ? ? ? ? 48 8B CE E8 ? ? ? ? 48 8B CE E8 ? ? ? ? 80 BE A0 03 00 00 00 74 ?` |
| `CMaterialSystem2_DynamicShaderCompile_UnloadAllMaterials` | `__int64 __fastcall sub_180039AA0(__int64 a1)` | `stringref` | `0x7FFCA30B9AA0` | `0x39AA0` | `"CMaterialSystem2::DynamicShaderCompile_UnloadAllMaterials(1084): ERROR!!! Shaders not freed before shader reload! (See spew above)\n\n"` |
| `CMaterialSystem2_FrameUpdate` | `__int64 __fastcall sub_18003BAC0(__int64 *a1)` | `raw` | `0x7FFCA30BBAC0` | `0x3BAC0` | `48 89 4C 24 08 55 53 56 57 41 54 41 56 48 8B EC 48 83 EC 68 48 8D 05 ? ? ? ? 48 C7 45 C0` |
| `CMaterialSystem2_GetErrorMaterial` | `__int64 __fastcall sub_180016D10(__int64 a1, __int64 a2, __int64 a3, _QWORD *a4, char a5)` | `stringref` | `0x7FFCA30974D7` | `0x174D7` | `"CMaterialSystem2::GetErrorMaterial(529): GetErrorMaterial() called when m_pMaterialTypeManager == NULL!\n"` |
| `CMaterialSystem2_Init` | `__int64 __fastcall sub_180036E40(__int64 a1)` | `stringref` | `0x7FFCA30B6E40` | `0x36E40` | `"MaterialSystem2"` |
| `CMaterial_SetVariableAndRenderState` | `` | `stringref` | `0x7FFCA30AF9B0` | `0x2F9B0` | `"SetRenderStateValueFromVariable(1172): Unsupported render state type in material "%s"!\n"` |
| `CVfxProgramData_FindOrCreateStaticComboDataInCache` | `__int64 __fastcall sub_1800AE0E0(__int64 a1, __int64 a2)` | `stringref` | `0x7FFCA312E0E0` | `0xAE0E0` | `"CVfxProgramData::FindOrCreateStaticComboDataInCache(4448): Error! Ref count !=0 for static combo data cache entry!\n"` |
| `CVfxProgramData_FindOrCreateStaticComboData_CacheGate` | `__int64 __fastcall sub_1800AE950(__int64 a1, unsigned __int64 a2, __int64 a3, int a4, __int64 a5, int a6, char a7)` | `raw` | `0x7FFCA312E950` | `0xAE950` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 57 48 83 EC 60 80 39 00 45 8B D9` |
| `CVfxProgramData_FindOrLoadStaticComboData` | `__int64 __fastcall sub_1800BDAE0(__int64 a1, __int64 a2, __int64 a3, __int64 a4, char a5)` | `stringref` | `0x7FFCA313DAE0` | `0xBDAE0` | `"Shader %s attribute "%s" has inconsistent value or type across multiple shaders of a feature combo! ["` |
| `FindParameter` | `__int64 __fastcall sub_180011E30(__int64 a1, __int64 a2)` | `raw` | `0x7FFCA3091E30` | `0x11E30` | `48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B 59 20 48` |
| `MatSys::PrepareSceneMaterial` | `float __fastcall sub_180011BE0(__int64 a1, __int64 a2, float a3)` | `raw` | `0x7FFCA3091BE0` | `0x11BE0` | `48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 48 8B 59 ? 48 8B F2 48 63 79 ? 48 C1 E7 06` |
| `UpdateParameter` | `_QWORD *__fastcall sub_180012370(__int64 a1)` | `raw` | `0x7FFCA3092370` | `0x12370` | `48 89 7C 24 ? 41 56 48 83 EC ? 8B 81` |

## `networksystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CNetChan_ProcessMessages` | `` | `raw` | `0x7FFC48F9B280` | `0xBB280` | `48 8B C4 53 57 41 54 41 56 48 81 EC A8 00 00 00 48 89 70 D0 45 33 E4 4C 89 68 C8 48 8B D9 48 89` |
| `CNetChan_SendNetMessage` | `` | `raw` | `0x7FFC48F9D670` | `0xBD670` | `48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 40 41 0F B6 F0 48 8D 99 F8 73 00 00 4C 8B F2` |
| `CNetworkSystem_Init` | `` | `raw` | `0x7FFC48FCC0C0` | `0xEC0C0` | `40 55 53 57 41 54 41 55 41 57 48 8D AC 24 98 FC FF FF 48 81 EC 68 04 00 00 4C 8B E9` |
| `CNetworkSystem_RegisterNetMessageHandlerAbstract` | `` | `raw` | `0x7FFC48F9BC00` | `0xBBC00` | `48 89 5C 24 10 48 89 6C 24 18 57 41 56 41 57 48 83 EC 50 4C 8B B4 24 90 00 00 00 41 8B D9` |
| `NetSystem_CNetChan_ProcessMessages` | `` | `raw` | `0x7FFC48F9B280` | `0xBB280` | `48 8B C4 53 57 41 54 41 56 48 81 EC A8 00 00 00 48 89 70 D0 45 33 E4 4C 89 68 C8 48 8B D9 48 89` |
| `NetSystem_CNetChan_SendNetMessage` | `` | `raw` | `0x7FFC48F9D670` | `0xBD670` | `48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 40 41 0F B6 F0 48 8D 99 F8 73 00 00 4C 8B F2` |

## `panorama.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CUIEngine_DispatchEvent` | `void __fastcall sub_180098320(int *a1, unsigned __int8 a2, __int64 a3)` | `raw` | `0x7FFC328D8320` | `0x98320` | `48 8B C4 48 89 58 18 88 50 10 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 78 F7 FF FF 48 81 EC 50` |
| `CUIEngine_RunFrame` | `__int64 __fastcall sub_1800A95F0(_QWORD *a1)` | `raw` | `0x7FFC328E95F0` | `0xA95F0` | `48 89 5C 24 10 48 89 6C 24 18 56 57 41 54 41 56 41 57 48 81 EC 80 00 00 00 45 33 F6 48 8B F1` |
| `GetPanelPointerFunctionPointer` | `` | `raw` | `0x7FFC328EC800` | `0xAC800` | `4C 63 0A 4C 8B DA` |
| `MakeSymbolFunctionPointer` | `` | `raw` | `0x7FFC328D52D0` | `0x952D0` | `40 55 56 48 83 EC ? 48 63` |
| `OnDeletePanelFunctionPointer` | `` | `raw` | `0x7FFC328EC450` | `0xAC450` | `48 85 D2 0F 84 ? ? ? ? 48 89 ? 24 ? 57 48 83 EC ? 48` |
| `RegisterEventHandlerFunctionPointer` | `` | `raw` | `0x7FFC328ECB60` | `0xACB60` | `48 89 5C 24 ? 66 89 54 24 ? 55 56 57 41 56 41 57 48 83 EC ? 48 8D 05 ? ? ? ? 48 C7 44 24 28 ? ? ? ? 48 89 44 24 ? 4D` |
| `RunScriptFunctionPointer` | `` | `raw` | `0x7FFC328E7020` | `0xA7020` | `48 89 5C 24 ? 4C 89 4C 24 ? 48 89 54 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D` |

## `particles.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `Particles::CParticleSystemMgr_CreateParticleCollection` | `__int64 __fastcall sub_1800A0DD0(__int64 a1, const char *a2, __int64 a3, __int64 a4, char a5, int a6, int a7)` | `raw` | `0x7FFC3A410DD0` | `0xA0DD0` | `4C 8B DC 49 89 5B 10 49 89 6B 18 49 89 73 20 57 41 56 41 57 48 81 EC 80 00 00 00 49 C7 43 B0 ? ? 00 00 48 8D 05 ? ? ? ? 49 89 43 A8` |
| `Particles::CParticleSystemMgr_FindParticleSystem` | `__int64 *__fastcall sub_1800A0BC0(__int64 a1, __int64 *a2, const char *a3, char a4)` | `raw` | `0x7FFC3A410BC0` | `0xA0BC0` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 81 EC 40 01 00 00 48 8D 05 ? ? ? ? 48 C7 44 24 28 ? ? 00 00 48 89 44 24 20` |
| `Particles::DrawArray` | `_BYTE *__fastcall sub_1800220B0(__int64 a1, __int64 a2, __int64 a3, int a4, __int64 a5, __int64 a6, __int64 a7)` | `raw` | `0x7FFC3A3920B0` | `0x220B0` | `40 55 53 56 57 48 8D 6C 24` |
| `Particles::FindKeyVar` | `__int64 __fastcall sub_18003A650(const char *a1, unsigned int a2, int a3)` | `raw` | `0x7FFC3A3AA650` | `0x3A650` | `48 89 5C 24 ? 57 48 81 EC ? ? ? ? 33 C0 8B DA` |
| `Particles::SetMaterialShaderType` | `void __fastcall sub_18009D8D0(__int64 a1, int *a2)` | `raw` | `0x7FFC3A40D8D0` | `0x9D8D0` | `48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 4C 63 32` |

## `rendersystemdx11.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CRenderDeviceBase_CreateConstantBuffer` | `` | `stringref` | `0x7FFC5CC5F500` | `0x2F500` | `"CRenderDeviceBase::CreateConstantBuffer(1571): "` |
| `CRenderDeviceDx11_BeginSubmittingDisplayLists` | `` | `stringref` | `0x7FFC5CC6C4E0` | `0x3C4E0` | `"CRenderDeviceDx11::BeginSubmittingDisplayLists(1162): "` |
| `CRenderDeviceDx11_CompileShaderSourceMain` | `` | `stringref` | `0x7FFC5CC6FAF0` | `0x3FAF0` | `"Shader compilation failed! Reported no errors.\n"` |
| `CSwapChainDx11_QueuePresentAndWait` | `` | `raw` | `0x7FFC5CC64650` | `0x34650` | `40 55 53 57 41 54 41 55 48 8D 6C 24 C9 48 81 EC C0 00 00 00 48 8D 05 ? ? ? ? 4C 89 B4 24` |
| `CSwapChainDx11_ResizeBuffers` | `` | `raw` | `0x7FFC5CC6DD20` | `0x3DD20` | `48 8B C4 55 53 56 57 41 54 48 8B EC 48 83 EC 70 4C 89 68 10 4D 8B E0 4C 89 70 18 4C 8B EA 4C 89` |
| `RenderSystemDx11_QueuePresentAndWait` | `` | `raw` | `0x7FFC5CC64650` | `0x34650` | `40 55 53 57 41 54 41 55 48 8D 6C 24 C9 48 81 EC C0 00 00 00 48 8D 05 ? ? ? ? 4C 89 B4 24` |
| `RenderSystemDx11_SetHardwareGammaRamp` | `` | `raw` | `0x7FFC5CC6F790` | `0x3F790` | `48 89 5C 24 18 57 B8 B0 40 00 00 E8 ? ? ? ? 48 2B E0 0F 29 BC 24 90 40 00 00 0F 57 C9 0F 28` |
| `RenderSystemDx11_SetMode` | `` | `raw` | `0x7FFC5CC699E0` | `0x399E0` | `44 89 4C 24 20 44 89 44 24 18 89 54 24 10 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC D8 02 00` |

## `resourcesystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `ResourceSystem_BlockingLoadResourceByName` | `` | `raw` | `0x7FFCBB9E7360` | `0x17360` | `40 53 55 57 48 81 EC 80 00 00 00 48 8B 01 49 8B E8 48 8B FA 48 8B D9 FF 90 98 01 00 00 83 F8 03` |
| `ResourceSystem_FindOrRegisterResourceByName` | `` | `raw` | `0x7FFCBB9E6D80` | `0x16D80` | `48 89 5C 24 18 48 89 74 24 20 57 48 81 EC A0 00 00 00 F7 02 FF FF FF 3F 41 0F B6 F8 48 8B DA 48` |
| `ResourceSystem_FrameUpdate` | `` | `raw` | `0x7FFCBB9EC010` | `0x1C010` | `44 88 4C 24 20 44 89 44 24 18 89 54 24 10 55 56 41 54 41 55 41 56 48 8D 6C 24 A0 48 81 EC 60 01` |

## `scenesystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `AllocateAttributeListFunctionPointer` | `` | `raw` | `0x7FFC3AC17D00` | `0xC7D00` | `40 55 48 83 EC ? 48 83 BA` |
| `BuildSceneInfoGpu` | `` | `raw` | `0x7FFC3ABD50A0` | `0x850A0` | `4C 89 4C 24 20 4C 89 44 24 18 48 89 4C 24 08 55 48 8D AC 24 00 E3 FF FF B8 00 1E 00 00` |
| `CSceneAnimatableObject::GeneratePrimitives` | `` | `raw` | `0x7FFC3ABC34A0` | `0x734A0` | `48 8B C4 48 89 58 08 48 89 50 10 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ?` |
| `CSceneAnimatableObject_GeneratePrimitives` | `` | `raw` | `0x7FFC3ABC34A0` | `0x734A0` | `48 8B C4 48 89 58 08 48 89 50 10 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ?` |
| `CSceneSkyBoxObject_DrawSkyboxArray` | `` | `raw` | `0x7FFC3AC9FA70` | `0x14FA70` | `45 85 C9 0F 8E ? ? ? ? 4C 8B DC 55 41 56 49 8D AB 58 FC FF FF 48 81 EC 98 04 00 00` |
| `CSceneSystem_CreateStaticShape` | `` | `raw` | `0x7FFC3AC01A70` | `0xB1A70` | `48 8B C4 48 89 48 08 55 41 54 41 56 48 8D 68 D8 48 81 EC 10 01 00 00 4C 8B 65 50 48 8D 4D 80` |
| `CSceneSystem_DeleteObjectForReal` | `` | `raw` | `0x7FFC3AC1A530` | `0xCA530` | `40 53 56 41 54 48 83 EC 50 0F B6 82 9B 00 00 00 45 33 E4 48 8B DA 48 8B F1 F0 FF 8C 81 CC 30 00 00` |
| `CSceneSystem_FrameUpdate` | `` | `raw` | `0x7FFC3AC31C30` | `0xE1C30` | `48 8B C4 88 50 10 48 89 48 08 55 53 41 54 41 55 48 8D 68 A1 48 81 EC 98 00 00 00` |
| `CSceneSystem_InitGfxObjects` | `` | `raw` | `0x7FFC3AC03DB0` | `0xB3DB0` | `40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 08 FE FF FF 48 81 EC F8 02 00 00` |
| `CSceneSystem_RenderViewLayer_Dispatch` | `` | `raw` | `0x7FFC3AC3DD00` | `0xEDD00` | `48 8B C4 48 89 48 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 B8 FE FF FF 48 81 EC 08 02 00` |
| `CSceneSystem_Thread_CullView` | `` | `stringref` | `0x7FFC3AC39270` | `0xE9270` | `"CSceneSystem::Thread_CullView(), C:\buildworker\csgo_rel_win64\build\src\scenesystem\scenesystem.cpp:3312"` |
| `DeleteSceneObjectFunctionPointer` | `` | `raw` | `0x7FFC3AC1B430` | `0xCB430` | `48 85 D2 0F 84 ? ? ? ? 48 8B C4 48 89 50` |
| `DrawAggregateSceneObjectArray` | `` | `raw` | `0x7FFC3AB8BCB0` | `0x3BCB0` | `48 8B C4 48 89 50 ? 48 89 48 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70` |
| `DrawObject_legacy` | `` | `raw` | `0x7FFC3ABA5B70` | `0x55B70` | `48 8B C4 53 57 41 54 48 81 EC D0 00 00 00 49 63 F9 49` |
| `DrawSkyboxArray` | `` | `raw` | `0x7FFC3AC9FA70` | `0x14FA70` | `45 85 C9 0F 8E ? ? ? ? 4C 8B DC 55` |
| `SceneSystem::DrawAggeregateObject` | `` | `raw` | `0x7FFC3AC7CE30` | `0x12CE30` | `48 8B C4 4C 89 48 20 4C 89 40 ? 48 89 50 ? 55 53 41 57 48 8D A8` |
| `SceneSystem::DrawArrayLight` | `` | `raw` | `0x7FFC3ABCAA40` | `0x7AA40` | `48 89 5C 24 ? 48 89 6C 24 ? 48 89 54 24` |
| `SceneSystem_Thread_RenderSceneDrawList` | `` | `raw` | `0x7FFC3AC3D9B0` | `0xED9B0` | `40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 E1 48 81 EC D8 00 00 00 4C 8B 71 28 48 8B D9` |

## `schemasystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CSchemaSystem_InstallSchemaBindings` | `` | `raw` | `0x7FFCBB9875D0` | `0x375D0` | `40 53 48 83 EC 20 48 8B DA 48 8B D1 48 8D 0D ? ? ? ? E8 ? ? ? ? 85 C0 74 08 32 C0` |
| `CSchemaSystem_RegisterModuleAndBuiltins` | `` | `raw` | `0x7FFCBB9606F0` | `0x106F0` | `48 89 54 24 10 53 56 57 41 55 41 56 41 57 48 83 EC 48 45 33 ED 49 63 C0 33 FF 44 89 AC 24 90 00` |
| `CSchemaSystem_VerifySchemaBindingConsistency` | `` | `raw` | `0x7FFCBB9558F0` | `0x58F0` | `88 54 24 10 55 53 57 41 54 41 55 48 8B EC 48 81 EC 80 00 00 00 65 48 8B 04 25 58 00 00 00` |

## `server.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CCSGameRules_TerminateRound` | `_BYTE *__fastcall sub_1808EFA50(__int64 a1, __int64 a2, unsigned int a3, __int64 a4)` | `raw` | `0x7FFC15BEFA90` | `0x8EFA90` | `48 8B C4 4C 89 48 20 48 89 48 08 55 56 41 56 41 57 48 8D 68 A1 48 81 EC E8 00 00 00 4C 8D B1` |
| `CCSGameRules_Think` | `double __fastcall sub_1808D80F0(__int64 a1)` | `raw` | `0x7FFC15BD8130` | `0x8D8130` | `40 55 53 41 55 41 57 48 8D 6C 24 C1 48 81 EC A8 00 00 00 80 79 48 00 4C 8B F9 4C 8B 2D` |
| `CCSPlayerPawnBase_SwitchTeam` | `__int64 __fastcall sub_180A0D380(__int64 a1, unsigned int a2)` | `raw` | `0x7FFC15D0D3C0` | `0xA0D3C0` | `40 53 57 48 81 EC 88 00 00 00 48 8B D9 8B FA 8B CA E8 ? ? ? ? 48 85 C0 0F 84 3A 02 00 00` |
| `CCSPlayerPawn_GiveNamedItem` | `__int64 __fastcall sub_180A2AC60(__int64 a1, const char *a2, int a3, __int64 a4, char a5, unsigned __int64 *a6)` | `raw` | `0x7FFC15D2A730` | `0xA2A730` | `48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 20 44 89 44 24 18 55 41 54 41 55 41 56 41 57 48 8D AC 24 40 FF FF FF 48 81 EC C0 01 00 00 4D 8B E1 45 8B E8` |

## `soundsystem.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CSosOperatorSystem_StartSoundEvent` | `` | `raw` | `0x7FFC43577AD0` | `0x1B7AD0` | `40 53 55 56 48 83 EC 20 83 B9 ?? ?? ?? ?? 00 49 8B D8 48 8B F2 48 8B E9 74 ?? C7 02 00 00 00 00` |
| `SoundSystem::PlayVSound` | `_UNKNOWN **__fastcall sub_180349840(__int64 a1, __int64 a2, int a3, int a4)` | `raw` | `0x7FFC43709840` | `0x349840` | `48 8B C4 48 89 58 08 57 48 81 EC ? ? ? ? 33 FF 48 8B D9` |
| `SoundSystem::SomeUtlSymbolFunc` | `__int64 __fastcall sub_1800B0740(__int64 a1, unsigned int a2)` | `raw` | `0x7FFC43470740` | `0xB0740` | `48 89 74 24 18 57 48 83 EC 20 48 63 F2 48 8B F9 3B 71 30` |

## `tier0.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `Tier0::CreateInterface` | `void *__fastcall CreateInterface(const char *pName, int *pReturnCode)` | `raw` | `0x7FFC64990B90` | `0x210B90` | `4C 8B 0D ? ? ? ? 4C 8B D2 4C 8B D9 4D 85 C9 74 2E 49 8B 41 08 4D 8B C3 4C 2B C0` |
| `Tier0::LoadKeyValues` | `` | `rel32` | `0x7FFC648A8F50` | `0x128F50` | `E8 ? ? ? ? 8B 4C 24 34 0F B6 D8` |
| `Tier0::Plat_FloatTime` | `double __fastcall Plat_FloatTime()` | `raw` | `0x7FFC648C6AF0` | `0x146AF0` | `48 83 EC 28 48 83 3D ? ? ? ? 00 75 05 E8 ? ? ? ? 48 8D 4C 24 30 FF 15 ? ? ? ? 48 8B 4C 24 30 48 8B 05 ? ? ? ? 48 3B C8 73 05 48 8B C8 EB 07 48 89 0D ? ? ? ? 48 2B 0D ? ? ? ? 0F 57 C0 78 12` |
| `Tier0::Plat_GetTime` | `unsigned __int64 __fastcall Plat_GetTime()` | `raw` | `0x7FFC648C6930` | `0x146930` | `48 83 EC 28 48 8D 4C 24 30 E8 ? ? ? ? 48 8B 44 24 30 48 83 C4 28 C3` |
| `Tier0::Plat_MSTime` | `unsigned __int64 __fastcall Plat_MSTime()` | `raw` | `0x7FFC648C6B70` | `0x146B70` | `40 53 48 83 EC 20 48 8B 1D ? ? ? ? 48 85 DB 75 0C E8 ? ? ? ? 48 8B 1D ? ? ? ? 48 8D 4C 24 30 FF 15 ? ? ? ? 48 8B 44 24 30 48 8B 0D ? ? ? ? 48 3B C1 73 05 48 8B C1 EB 07 48 89 05 ? ? ? ? 48 2B 05 ? ? ? ? 33 D2 48 F7 F3 48 8B C8 48 69 C2 E8 03 00 00 69 C9 E8 03 00 00` |
| `Tier0::UtlBuffer` | `` | `raw` | `0x7FFC647D3F10` | `0x53F10` | `48 89 5C 24 ? 57 48 83 EC ? 8B 41 ? 8D 7A` |

## `vphysics2.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `VPhysics2_Startup` | `` | `raw` | `0x7FFC48A0AF20` | `0x6AF20` | `48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 54 41 56 41 57 48 83 EC 70 48 83 3D` |

## `worldrenderer.dll`

| Name | Prototype | Resolve | VA | RVA | Pattern |
| --- | --- | --- | --- | --- | --- |
| `CWorldRendererMgr_ServiceWorldRequests` | `__int64 __fastcall sub_18002B4A0(__int64 a1)` | `raw` | `0x7FFC6345B4A0` | `0x2B4A0` | `48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 83 EC 40 48 8B D9 0F 29 74 24 30 48 8D 0D ? ? ? ? 0F 29 7C 24 20 BA FF FF FF FF` |

