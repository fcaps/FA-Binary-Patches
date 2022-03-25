void ConsoleLog()
{//Writes called console commands to the log.
    asm
    (
        "MOV DWORD PTR SS:[EBP-4],2;"
        "PUSH [ESP+0xF4];"
        "CALL 0x00937CB0;"
        "ADD ESP,4;"
        "JMP 0x0041CE11;"
    );
}