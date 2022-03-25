#include "../define.h"
asm
( //HOOK GetDepositsAroundPoint
  ".section h0; .set h0,0x842E8A;"
  "mov eax, "QU(UGDAPRegDesc)";"
);