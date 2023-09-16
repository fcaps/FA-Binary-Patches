#include "include/LuaAPI.h"

struct LuaExts {
    LuaExts() {
        if (FAJit) {
            WarningF("%s", "Used FAExt.dll");
            lua_createtable = GetProcAddress(FAJit, "lua_createtable");
            offsetTSizeArray = GetProcAddress(FAJit, "offsetSizeArray");
            offsetTSizeNode = GetProcAddress(FAJit, "offsetSizeNode");
        } else {
            //PatcherList_LCreateTable
            extern void *LCreateTable[];
            if (LCreateTable[0])
                lua_createtable = LCreateTable[0];
        }
    }
} luaexts;