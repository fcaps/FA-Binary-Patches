void X3DAudioCalculateRet() {
  asm(
    "CALL [0xC0F968];"
    "ADD ESP,0x14;"
    "MOV EAX,ESI;"
    "POP ESI;"
  );
}