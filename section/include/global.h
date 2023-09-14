#pragma once

#include <cstdint>
#include "../../workflow.cpp"

#define GPtr(addr, type) \
  (*(type*)addr)

#define GDecl(addr, type) \
  ((type)addr)

#define WDecl(addr, type) \
  ((type)*(uintptr_t*)addr)

#define FDecl(addr, name, type) \
  const auto name = (type)addr;

#define VALIDATE_SIZE(struc, size) \
  static_assert(sizeof(struc) == size, "Invalid structure size of " #struc);

#define g_CSimDriver			GPtr(0x10C4F50, CSimDriver*)
#define g_SWldSessionInfo		GPtr(0x10C4F58, SWldSessionInfo*)
#define g_CWldSession			GPtr(0x10A6470, CWldSession*)
#define g_Sim				GPtr(0x10A63F0, Sim*)
#define g_EntityCategoryTypeInfo	GPtr(0x10C6E70, EntityCategoryTypeInfo*)
#define g_CAiBrainTypeInfo		GPtr(0x10C6FA0, CAiBrainTypeInfo*)
#define g_CUIManager			GPtr(0x10A6450, CUIManager*)
#define g_EngineStats			GPtr(0x10A67B8, EngineStats*)
#define g_WRenViewport			GPtr(0x10C7C28, WRenViewport*)
#define g_ConsoleLuaState		GPtr(0x10A6478, LuaState*)
#define g_Device			GPtr(0x0F8E284, Device*)

#define ui_ProgressBarColor		GDecl(0x0F57BB8, int)
#define ui_SelectTolerance		GDecl(0x0F57A90, float)
#define ui_ExtractSnapTolerance		GDecl(0x0F57A94, float)
#define ui_DisableCursorFixing		GDecl(0x10A6464, bool)
#define ui_RenderIcons			GDecl(0x0F57B27, bool)
#define range_RenderSelected		GDecl(0x10A640A, bool)
#define range_RenderHighlighted		GDecl(0x10A640B, bool)
#define range_RenderBuild		GDecl(0x10A6414, bool)
#define d3d_WindowsCursor		GDecl(0x10A636E, bool)
#define debugSelect			GDecl(0x10A645E, bool)

#define s_FACTORY			GDecl(0xE19824, const char*)
#define s_EXPERIMENTAL			GDecl(0xE204B8, const char*)
#define s_global			GDecl(0xE00D90, const char*) // "<global>"
#define s_ExpectedButGot		GDecl(0xE0A220, const char*) // "%s\n  expected %d args, but got %d"
#define s_ExpectedBetweenButGot		GDecl(0xE0A270, const char*) // "%s\n  expected between %d and %d args, but got %d"
#define s_Global			GDecl(0xE00D90, const char*) // "<global>"
#define s_CMauiBitmap			GDecl(0xE37438, const char*) // "CMauiBitmap"
#define s_UserUnit			GDecl(0xE4D090, const char*) // "UserUnit"
#define s_ExpectedAGameObject		GDecl(0xE09860, const char*) // "Expected a game object. (Did you call with '.' instead of ':'?)"
#define s_GameObjectHasBeenDestroyed	GDecl(0xE098A0, const char*) // "Game object has been destroyed"
#define s_IncorrectTypeOfGameObject	GDecl(0xE098C0, const char*) // "Incorrect type of game object.  (Did you call with '.' instead of ':'?)"
#define s_UnknownColor			GDecl(0x4B2D54, const char*) // "Unknown color: %s"
#define s_c_object			GDecl(0xE016DC, const char*) // "_c_object"

#define g_ExeVersion1			GDecl(0x876666, const int)
#define g_ExeVersion2			GDecl(0x87612d, const int)
#define g_ExeVersion3			GDecl(0x4d3d40, const int)

void AbortF(wchar_t *fmt, ...) asm("0x9C4940");
int LogF(const char *fmt, ...) asm("0x937CB0");
int WarningF(const char *fmt, ...) asm("0x937D30");
int SpewF(const char *fmt, ...) asm("0x937C30");
int ConsoleLogF(const char *fmt, ...) asm("0x41C990");
int FileWrite(int fileIndex, const char *str, int strlen) asm("0xA9B4E6"); //index 3 is log.
void* shi_new(size_t size) asm("0xA825B9");
void* FArealloc(void *ptr, size_t new_size) asm("0x957B00");
void* FAmalloc(size_t size) asm("0x958B20");
void FAfree(void *ptr) asm("0x958C40");
size_t FAmsize(void *memblock) asm("0x957EA0");
void* FAcalloc(size_t num, size_t size) asm("0x957AB0");
void* FAmemset(void *dest, int ch, size_t count) asm("0xA89110");
void* FAmemcpy(void *dest, const void *src, size_t count) asm("0xA89190");
float FAsqrtf(float arg) asm("0x452FC0");
size_t FAstrlen(const char *str) asm("0xA94450");
int FAstrcmp(const char *str1, const char *str2) asm("0xAA549E");
int FAsprintf_s(char *Buffer, size_t BufferCount, const char *Format, ...) asm("0xA82F32");

__thiscall void InitString(void *this_, const char *str) asm("0x405550");
__thiscall void AssignString(void *this_, const char *str, size_t size) asm("0x4059E0");

#define GetModuleHandle   WDecl(0xC0F378, __stdcall void* (*)(const char *lpLibFileName))
#define GetProcAddress    WDecl(0xC0F48C, __stdcall void* (*)(void* hModule, const char *lpProcName))
#define GetCurrentProcess WDecl(0xC0F58C, __stdcall void* (*)())

#define QueryPerformanceCounter   WDecl(0xC0F470, __stdcall bool (*)(int64_t*))
#define QueryPerformanceFrequency WDecl(0xC0F46C, __stdcall bool (*)(int64_t*))

#define DebugLog(_s) LogF("%s", (_s))

template <typename T>
struct Result
{
    T *object = nullptr;
    const char *reason = nullptr;

    constexpr static Result<T> Fail(const char *reason) { return {nullptr, reason}; }
    constexpr static Result<T> Success(void *data) { return {(T *)data, nullptr}; }

    inline bool IsFail() { return reason != nullptr; }
};