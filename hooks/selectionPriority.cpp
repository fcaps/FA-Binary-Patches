#include "../define.h"
asm
( //HOOK selectionPriority
  ".section h0; .set h0,0x863C13;"
  "jmp "QU(selectionPriority)";"
  "nop;"
);
