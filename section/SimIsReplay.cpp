void SimSessionIsReplay()
{
    asm
    (
        "MOV EAX,[0x10A6470];"
        "MOVZX EAX,byte ptr[EAX+0x484];"
        "PUSH EAX;"
        "PUSH ESI;"
        "CALL 0x0090CF80;" // lua_pushbool
        "ADD ESP,0x8;"
        "MOV EAX,0x1;"
    );
}