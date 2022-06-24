# FA Engine Patches Repository

This are some binary patches for Supreme Commander Forged Alliance.

To apply them build or get the patcher itself from here

https://github.com/FAForever/FA_Patcher

This are just the patch files for this game. I decided to separate them from patcher source code.

# Change List
## Fixes
- Zeroing GuardScanRadius if the unit's order is not Patrol/AttackMove. Increases performance.
    - hooks/HGuardFix.cpp
    - section/GuardFix.cpp
- Prevents the crash with 'None' collisions of air. #3235
    - hooks/AirNoneCollisionFix.cpp
- Prevents commander exploding for no reason. #3406
    - hooks/NegativeIncomeFix.cpp
- Range ring performance improvement (don't render each ring twice)
    - hooks/RangeRings.cpp
    - section/RangeRings.cpp
- Camera performance improvements
    - hooks/CameraPerf.cpp
- Fix replays desyncing when a player leaves the game
    - hooks/DesyncFix.cpp
    - section/ext_sector.cpp
    - section/gpg_net.cpp
    - section/moho_decode.cpp
    - section/moho_input.cpp
- Kill exception during map loading
    - hooks/Kill_maploader_except.cpp
- Make xact3d the error message print once
    - hooks/xact_3dapply.cpp
    - section/ext_sector.cpp
- Prevent blueprint editor being used without cheat mode
    - hooks/FixOpenBPEditor.cpp
- Can't become an observer while your human allies are still alive
    - hooks/ObserverFix.cpp
- Stop the engine calling lua every time a plane turns
    - hooks/OnMotionTurnEvent.cpp
- Optimised some AI actions
    - hooks/aiinitattack.cpp
- Fix a crash when units arrive at waypoints
    - hooks/WayPointArrive.cpp

## Additions
- GetSessionClients also output maximum sim speed(maxSP)
    - hooks/HOutputMaxSP.cpp
    - section/OutputMaxSP.cpp
- Console command: "cam_DefaultMiniLOD 0" now completely disable mesh renderer for minimap
    - hooks/MinimapMesh.cpp
    - section/MinimapMesh.cpp
- Allow players to double-click to select Walls
    - hooks/Walls.cpp
- Similar to GetSystemTimeSecondsOnlyForProfileUse
  Allows to deal with the loss of accuracy. It is present in the Sim and UI
    - section/GetTimeForProfile.cpp
    - section/ext_sector.cpp
- Adds optimized table.getsize2(~25 times faster) and table.empty2
  Added getn2 as alias getn. Entry point to math functions queue
    - hooks/GetTableSize.cpp
    - section/ext_sector.cpp
- Maximum sim rate up to 50
    - hooks/DelClampMaxSimRate.cpp
- Adds an amphibious mode toggle to the Salem
    - hooks/luaSimGetStat.cpp
    - section/luaSimGetStat.cpp
- Make `LOWSELECTPRIO` apply to units under construction
    - hooks/selectionPriority.cpp
    - section/selectionPriority.cpp
- Allow the getting of Mass or Energy spots around a location & Entry point to ui functions queue
    - hooks/UserGetDepositsAroundPoint.cpp
    - section/SimGetDepositsAroundPoint.cpp
    - section/ext_sector.cpp
- Allow devs to write console commands to the log
    - hooks/ConsoleLog.cpp
    - section/ConsoleLog.cpp
- Unlock an "Ultra" graphics preset
    - hooks/UnlockUltraPreset.cpp
- Allow armies to be shared by multiple players & Entry point to sim functions queue
    - hooks/SimSetFocusArmy.cpp
    - section/SimSetFocusArmy.cpp
- Allow upgrades to be queued on units under construction
    - hooks/BuildUnit.cpp
    - section/BuildUnit.cpp
    - section/SelectUnit.cpp
    - section/SimArmyCreate.cpp