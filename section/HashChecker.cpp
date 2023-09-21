#include "include/magic_classes.h"

typedef __stdcall int VirtualProtect_t(void *lpAddress, int dwSize, int flNewProtect, int *lpflOldProtect);

#define CreateFileA	WDecl(0xC0F540, __stdcall void* (*)(const char* lpFileName,\
    uint32_t dwDesiredAccess, uint32_t dwShareMode, void* lpSecurityAttributes,\
    uint32_t dwCreationDisposition, uint32_t dwFlagsAndAttributes, void* hTemplateFile))

#define ReadFile	WDecl(0xC0F560, __stdcall bool (*)(void* hFile, void* lpBuffer,\
    uint32_t nNumberOfBytesToRead, uint32_t* lpNumberOfBytesRead, void* lpOverlapped))

#define WriteFile	WDecl(0xC0F51C, __stdcall bool (*)(void* hFile, const void* lpBuffer,\
    uint32_t nNumberOfBytesToWrite, uint32_t* lpNumberOfBytesWritten, void* lpOverlapped))

#define GetFileSize	WDecl(0xC0F550, __stdcall uint32_t (*)(void* hFile, uint32_t* lpFileSizeHigh))

#define CloseHandle	WDecl(0xC0F590, __stdcall bool (*)(void* hObject))

#define GENERIC_READ			0x80000000
#define GENERIC_WRITE			0x40000000
#define FILE_FLAG_SEQUENTIAL_SCAN	0x08000000
#define FILE_SHARE_READ			1
#define CREATE_ALWAYS			2
#define OPEN_EXISTING			3

int mode = 0;
int hashIndex;
void* file = 0;
VirtualProtect_t *VirtualProtect;

void HashWarn() {
    WarningF("Hash %d not equal", hashIndex);
}

void HashCheckerStop() {
    uint32_t oldProt;
    VirtualProtect((void*)(0x7433F4), 4, 0x40, &oldProt);
    *(uint32_t*)(0x7433F4) = 0xD8;
    VirtualProtect((void*)(0x7433F4), 4, oldProt, &oldProt);

    VirtualProtect((void*)(0x746271), 5, 0x40, &oldProt);
    *(uint8_t*)(0x746271) = 0xC2;
    *(uint32_t*)(0x746272) = 0xCCCC0004;
    VirtualProtect((void*)(0x746271), 5, oldProt, &oldProt);

    VirtualProtect((void*)(0x8E5782), 5, 0x40, &oldProt);
    *(uint8_t*)(0x8E5782) = 0xC2;
    *(uint32_t*)(0x8E5783) = 0xCCCC0008;
    VirtualProtect((void*)(0x8E5782), 5, oldProt, &oldProt);

    if (file) {
        CloseHandle(file);
        WarningF("%s", "HashChecker stop");
        file = 0;
    }
}

void HashHook() {
    register uint64_t* hash1 asm("esi");
    if (mode == 1) {
        WriteFile(file, hash1, 16, 0, 0);
    } else {
        uint64_t hash2[2];
        ReadFile(file, hash2, 16, 0, 0);
        if (hash1[0] != hash2[0] || hash1[1] != hash2[1]) {
            HashCheckerStop();
            HashWarn();
        }
        hashIndex++;
    }
    asm("add esp,0x34; pop esi; pop ebp; ret 8;");
}

void SimDestroyHook() {
    HashCheckerStop();
    asm("add esp,0x8; pop ebp; ret 4;");
}

void SimCreateHook() {
    if (mode == 1)
        file = CreateFileA("HashChecker.hash", GENERIC_WRITE,
            FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, 0); else
        file = CreateFileA("HashChecker.hash", GENERIC_READ,
            FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, 0);
    if (file == -1) {
        WarningF("%s", "CreateFileA error");
        asm("add esp,0x34; pop ebx; pop ebp; jmp 0x7434D0;");
        return;
    }
    hashIndex = 0;

    uint32_t oldProt;
    VirtualProtect((void*)(0x746271), 5, 0x40, &oldProt);
    *(uint8_t*)(0x746271) = 0xE9;
    *(uint32_t*)(0x746272) = &SimDestroyHook - 0x746271 - 5;
    VirtualProtect((void*)(0x746271), 5, oldProt, &oldProt);

    VirtualProtect((void*)(0x8E5782), 5, 0x40, &oldProt);
    *(uint8_t*)(0x8E5782) = 0xE9;
    *(uint32_t*)(0x8E5783) = &HashHook - 0x8E5782 - 5;
    VirtualProtect((void*)(0x8E5782), 5, oldProt, &oldProt);

    WarningF("%s", "HashChecker init");
    asm("add esp,0x34; pop ebx; pop ebp; jmp 0x7434D0;");
}

int HashChecker(lua_State *L) {
    if (file) {
        WarningF("%s", "HashChecker already active");
        return 0;
    }
    mode = luaL_checknumber(L, 1);
    void *Kernel = GetModuleHandleA("KERNEL32");
    VirtualProtect = GetProcAddress(Kernel, "VirtualProtect");
    HashCheckerStop();
    if (mode) {
        uint32_t oldProt;
        VirtualProtect((void*)(0x7433F4), 4, 0x40, &oldProt);
        *(uint32_t*)(0x7433F4) = &SimCreateHook - 0x7433F3 - 5;
        VirtualProtect((void*)(0x7433F4), 4, oldProt, &oldProt);
        if (mode == 2)
            WarningF("Use break point on 0x%X", HashWarn);
    }
    WarningF("Set mode %d", mode);
    return 0;
}

UIRegFunc UHPRegDesc {
    "HashChecker",
    "HashChecker(mode) 0 off, 1 save, 2 check",
    HashChecker};