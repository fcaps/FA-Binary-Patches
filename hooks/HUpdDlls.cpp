#include "../define.h"
asm(
  ".section h0; .set h0,0xD55E5C;"
  ".word 'M','s','f','t','e','d','i','t',0,0,'R','i','c','h','E','d','i','t','5','0','W',0;"

  //D3DX9_43
  ".section h1; .set h1,0xF2CF6C;"
  ".byte '4','3';"

  //XACT 2_10
  ".section h2; .set h2,0xE0B754;"
  ".byte 0xA4,0x22,0xD8,0x65,0x99,0x47,0xC6,0x42,0x9B,0x18,0xD2,0x6C,0xF6,0x6D,0xD3,0x20;"
  ".byte 0x4B,0x99,0xC3,0x5A,0x77,0xAC,0x40,0x4C,0xB9,0xFD,0x7D,0x5A,0xFB,0xE9,0x64,0xC5;"

  ".section h3; .set h3,0xF2CAE8;"
  ".ascii \"X3DAudioInitialize\";"
  ".int 0,0;"
  ".ascii \"X3DAudioCalculate\";"
  ".byte 0,0,0,0,0;"
  ".ascii \"X3DAudio1_7.dll\";"

  //X3DAudioInitialize __cdecl
  ".section h4; .set h4,0x4D81D1;"
  "ADD ESP,0xC;"
  "MOV EAX,ESI;"
  "POP ESI;"
  "ADD ESP,0x2C;"
  "RET;"

  //X3DAudioCalculate __cdecl
  ".section h5; .set h5,0x4D8245;"
  "JMP "QU(X3DAudioCalculateRet)";"
);