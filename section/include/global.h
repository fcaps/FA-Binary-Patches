#pragma once

#include <cstdint>
#include "../../workflow.cpp"

#define GDecl(addr, type) \
  (*(type*)addr)

#define WDecl(addr, type) \
  ((type)*(uintptr_t*)addr)

#define FDecl(addr, name, type) \
  const auto name = (type)addr;

#define VALIDATE_SIZE(struc, size) \
  static_assert(sizeof(struc) == size, "Invalid structure size of " #struc);

#define g_CSimDriver			GDecl(0x10C4F50, CSimDriver*)
#define g_SWldSessionInfo		GDecl(0x10C4F58, SWldSessionInfo*)
#define g_CWldSession			GDecl(0x10A6470, CWldSession*)
#define g_Sim				GDecl(0x10A63F0, Sim*)
#define g_EntityCategoryTypeInfo	GDecl(0x10C6E70, EntityCategoryTypeInfo*)
#define g_CAiBrainTypeInfo		GDecl(0x10C6FA0, CAiBrainTypeInfo*)
#define g_CUIManager			GDecl(0x10A6450, CUIManager*)
#define g_EngineStats			GDecl(0x10A67B8, EngineStats*)
#define g_WRenViewport			GDecl(0x10C7C28, WRenViewport*)
#define g_ConsoleLuaState		GDecl(0x10A6478, LuaState*)
#define g_Device			GDecl(0x0F8E284, Device*)

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

#define g_ExeVersion1			GDecl(0x876666, const int)
#define g_ExeVersion2			GDecl(0x87612d, const int)
#define g_ExeVersion3			GDecl(0x4d3d40, const int)

FDecl(0x9C4940, AbortF,		void (*)(wchar_t *fmt, ...))
FDecl(0x937CB0, LogF,		int (*)(const char *fmt, ...))
FDecl(0x937D30, WarningF,	int (*)(const char *fmt, ...))
FDecl(0x937C30, SpewF,		int (*)(const char *fmt, ...))
FDecl(0x41C990, ConsoleLogF,	int (*)(const char *fmt, ...))
FDecl(0xA9B4E6, FileWrite,	int (*)(int fileIndex, const char *str, int strlen)) //index 3 is log.
FDecl(0xA825B9, shi_new,	void* (*)(size_t size))
FDecl(0x957B00, FArealloc,	void* (*)(void *ptr, size_t new_size))
FDecl(0x958B20, FAmalloc,	void* (*)(size_t size))
FDecl(0x958C40, FAfree,		void (*)(void *ptr))
FDecl(0x957EA0, FAmsize,	size_t (*)(void *memblock))
FDecl(0x957AB0, FAcalloc,	void* (*)(size_t num, size_t size))
FDecl(0xA89110, FAmemset,	void* (*)(void *dest, int ch, size_t count))
FDecl(0xA89190, FAmemcpy,	void* (*)(void *dest, const void *src, size_t count))
FDecl(0x452FC0, FAsqrtf,	float (*)(float arg))
FDecl(0xA94450, FAstrlen,	size_t (*)(const char *str))
FDecl(0xAA549E, FAstrcmp,	int (*)(const char *str1, const char *str2))
FDecl(0xA82F32, FAsprintf_s,	int (*)(char *Buffer, size_t BufferCount, const char *Format, ...))

FDecl(0x405550, InitString,	__thiscall void (*)(void *this_, const char *str))
FDecl(0x4059E0, AssignString,	__thiscall void (*)(void *this_, const char *str, size_t size))

#define GetModuleHandle   WDecl(0xC0F378, __stdcall void* (*)(const char *lpLibFileName))
#define GetProcAddress    WDecl(0xC0F48C, __stdcall void* (*)(void* hModule, const char *lpProcName))
#define GetCurrentProcess WDecl(0xC0F58C, __stdcall void* (*)())

#define QueryPerformanceCounter   WDecl(0xC0F470, __stdcall bool (*)(int64_t*))
#define QueryPerformanceFrequency WDecl(0xC0F46C, __stdcall bool (*)(int64_t*))

#define DebugLog(_s) LogF("%s", (_s))