#include "include/moho.h"
#include "include/desync_fix_global.h"

// New unit categories.
//const char* sCQUEMOV = "CQUEMOV";
//const char* sSTAYONWATSUR = "STAYONWATSUR";

void SimSessionIsReplay();
luaFuncDescReg SSIRRegDesc =  {0x00E45E90,          // Std register func
                               0x00E4AFBC,          // "SessionIsReplay"
                               0x00E00D90,          // "<global>"
                               0x00E4AF84,          // "Return true if the active session is a replay session."
                               0x010B8AE8,          // Next reg desc: ArmyGetHandicap
                               SimSessionIsReplay,  // Func ptr
                               0x00000000};         // C++ class vtable ptr

void SimSetCommandSource();
luaFuncDescReg SSCSRegDesc =  {0x00E45E90,
                               "SetCommandSource",
                               0x00E00D90,
                               "(targetArmyIndex, sourceHumanIndex, Set or Unset)",
                               &SSIRRegDesc,
                               SimSetCommandSource,
                               0x00000000};

#define s_GDAPName "GetDepositsAroundPoint"
#define s_GDAPDesc "(X, Z, Radius, Type)"
void SimGetDepositsAroundPoint();
luaFuncDescReg SGDAPRegDesc = {0x00E45E90,
                               s_GDAPName,
                               0x00E00D90,
                               s_GDAPDesc,
                               &SSCSRegDesc,
                               SimGetDepositsAroundPoint,
                               0x00000000};

#define s_GTFPName "GetTimeForProfile"
#define s_GTFPDesc "(OriginTime)"
void GetTimeForProfile();
luaFuncDescReg SGTFPRegDesc = {0x00E45E90,
                               s_GTFPName,
                               0x00E00D90,
                               s_GTFPDesc,
                               &SGDAPRegDesc,
                               GetTimeForProfile,
                               0x00000000};

void SimSetFocusArmy();
luaFuncDescReg SSFARegDesc =  {0x00E45E90,          // Std register func
                               0x00E43408,          // "SetFocusArmy"
                               0x00E00D90,          // "<global>"
                               0x00E451FC,          // "SetFocusArmy(armyIndex or -1)"
                               &SGTFPRegDesc,       // Next reg desc
                               SimSetFocusArmy,     // Func ptr
                               0x00000000};         // C++ class vtable ptr

luaFuncDescReg UGTFPRegDesc = {0x00E45E90,
                               s_GTFPName,
                               0x00E00D90,
                               s_GTFPDesc,
                               0x010C3CA4,          // Next reg desc: SetFocusArmy
                               GetTimeForProfile,
                               0x00000000};

luaFuncDescReg UGDAPRegDesc = {0x00E45E90,
                               s_GDAPName,
                               0x00E00D90,
                               s_GDAPDesc,
                               &UGTFPRegDesc,       // Next reg desc
                               SimGetDepositsAroundPoint,
                               0x00000000};

register int eax asm("eax");

bool game_ended = false;

void EndGame()
{
	game_ended = true;
	asm("mov dword ptr [0x011FD23F], 0xB;"); //remove block when last player remains.
	asm
	(
		"push esi;"
		"mov esi,eax;"
		"mov eax,dword ptr [esi];"
		"push edi;"
		"mov edi,dword ptr [0x10BA600];"
		"push eax;"
		"call 0x90C590;"
		"add esp,0x4;"
		"test eax,eax;"
		"je L0xABEL_0x0074B8DB;"
		"push eax;"
		"push 0x0;"
		"push edi;"
		"push 0xE0A220;"
		"push esi;"
		"call 0x90C1D0;"
		"add esp,0x14;"
		"L0xABEL_0x0074B8DB:;"
		"mov esi,dword ptr [esi];"
		"push esi;"
		"call 0x924050;"
		"mov edx,dword ptr [eax];"
		"mov ecx,eax;"
		"mov eax,dword ptr [edx+0x5C];"
		"add esp,0x4;"
		"call eax;"
		"pop edi;"
		"xor eax,eax;"
		"pop esi;"
		"ret;"
	);
}

void xact_3d_apply()
{
	static bool once = true;
	asm
	(
		"push ebx;"
		"push edi;"
		"mov ebx,ecx;"
		"mov edi,eax;"
		"mov eax,dword ptr [ebx];"
		"cmp dword ptr [eax+0x34],0x0;"
		"je L0xABEL_0x004D9B2A;"
		"push esi;"
		"push 0x64;"
		"lea esi,dword ptr [eax+0xAC];"
		"push 0x0;"
		"push esi;"
		"call 0xA89110;"
		"xorps xmm0,xmm0;"
		"mov dword ptr [esi+0x3C],0x1;"
		"mov dword ptr [esi],0x0;"
		"fld dword ptr [edi];"
		"fstp dword ptr [esi+0x1C];"
		"fld dword ptr [edi+0x4];"
		"fstp dword ptr [esi+0x20];"
		"fld dword ptr [edi+0x8];"
		"movss dword ptr [esi+0x28],xmm0;"
		"movss dword ptr [esi+0x2C],xmm0;"
		"fstp dword ptr [esi+0x24];"
		"movss dword ptr [esi+0x30],xmm0;"
		"movss xmm0,dword ptr [0xDFEC20];"
		"movss dword ptr [esi+0x5C],xmm0;"
		"movss dword ptr [esi+0xC],xmm0;"
		"movss dword ptr [esi+0x14],xmm0;"
		"mov ecx,dword ptr [ebx];"
		"lea edi,dword ptr [ecx+0x7C];"
		"lea eax,dword ptr [ecx+0xAC];"
		"lea edx,dword ptr [ecx+0x38];"
		"add ecx,0x110;"
		"push ecx;"
		"call 0x4D81E0;"
		"add esp,0x10;"
		"test eax,eax;"
		"jge L0xABEL_0x004D9B04;"
		"call 0x4D8A50;"
	);

	asm
	(
		"push eax;"
		"push 0xE0B410;"
		"call 0x937D30;"
		"add esp,0x8;"
	);

	asm
	(
		"pop esi;"
		"pop edi;"
		"pop ebx;"
		"ret 0x4;"
		"L0xABEL_0x004D9B04:;"
		"mov ebx,dword ptr [ebx];"
		"mov esi,dword ptr [esp+0x10];"
		"lea edi,dword ptr [ebx+0x7C];"
		"call 0x4D82A0;"
		"test eax,eax;"
		"jge L0xABEL_0x004D9B29;"
		"call 0x4D8A50;"
	);
	if(once)
	{
		asm
		(
			"push eax;"
			"push 0xE0B430;"
			"call 0x937D30;"
			"add esp,0x8;"
		);
		once = false;
	}

	asm
	(
		"L0xABEL_0x004D9B29:;"
		"pop esi;"
		"L0xABEL_0x004D9B2A:;"
		"pop edi;"
		"pop ebx;"
		"ret 0x4;"
	);
}