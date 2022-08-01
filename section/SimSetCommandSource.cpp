int SimSetCommandSource(void* L)
{
    asm
    (
	"MOV EDI,[ESI+0xC];"
	"MOV EAX,[0x10A63F0];"
	"MOV EAX,[EAX+0x910];"
	"CVTTSS2SI ECX,[EDI+0x4];"       // targetArmyIndex
	"MOV EAX,[ECX*0x4+EAX];"
	"CVTTSS2SI ECX,[EDI+0x0C];"      // sourceHumanIndex
	"MOV EDX,ECX;"
	"SHR EDX,0x5;"
	"SUB EDX,[EAX+0x130];"
	"MOV EBX,[EAX+0x138];"
	"LEA EBX,[EDX*0x4+EBX];"
	"CMP EBX,[EAX+0x13C];"
	"JB L1;"
	"MOV DWORD PTR [EBX],0x0;"
	"ADD DWORD PTR [EAX+0x13C],0x4;"
	"L1:;"
	"AND CL,0x1F;"
	"MOV EDX,0x1;"
	"SHL EDX,CL;"
	"XOR EAX,EAX;"                   // Num return values
	"CMP DWORD PTR [EDI+0x14],0x1;"  // Set or Unset
	"JL L2;"
	"OR [EBX],EDX;"
	"RET;"
	"L2:;"
	"NOT EDX;"
	"AND [EBX],EDX;"
	"RET;"
    );
}

/*
extern "C" int cxx_SetCommandSourceId(lua_state* lua, int armyId, int sourceId, bool set_or_unset)
{
	Sim* sim = g_Sim;
	SimArmy* army = (SimArmy*)sim->armies[armyId];

	if(set_or_unset)
		army->mValidCommandSources.add(sourceId);
	else
		army->mValidCommandSources.remove(sourceId);
	return 1;
}
*/
