#include "../define.h"
asm
( //HOOK SetFocusArmy
  ".section h0; .set h0,0x708A9A;"
  "mov eax, "QU(SSFARegDesc)";"
);