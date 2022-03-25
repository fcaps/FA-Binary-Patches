#include "../define.h"
asm
( //HOOK make the error message print once
  ".section h0; .set h0,0x4D9A60;"
  "jmp "QU(xact_3d_apply)";"
  "nop;"
);

  