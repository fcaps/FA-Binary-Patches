#include "../define.h"
asm
( //HOOK luaSimGetStat
  ".section h0; .set h0,0x6CC759;"
  "jmp "QU(luaSimGetStat)";"
  "nop;"
  "nop;"
);