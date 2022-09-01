int SimSetFocusArmy(void* L)
{
    asm(
        "MOV EAX,[ESI+0xC];"
        "CVTTSS2SI EAX,[EAX+0x4];" // ArmyIndex
        "MOV ECX,[0x10C4F50];"     // g_STIDriver
        "MOV [ECX+0x0B0],EAX;"
        "XOR EAX,EAX;"             // Num return values
        "RET;"
    );
}