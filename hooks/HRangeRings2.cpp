#include "../define.h"
asm
(
  ".section h0; .set h0,0x73D4A0;"
  "CALL "QU(HeightCylinders)";"

  ".section h1; .set h1,0x7EE2BC;"
  ".4byte "QU(MinCHeight)";"

  ".section h2; .set h2,0x7EE33A;"
  ".4byte "QU(MaxCHeight)";"

  ".section h3; .set h3,0x81C38E;"
  ".4byte "QU(MinCHeight)";"

  ".section h4; .set h4,0x81C3C5;"
  ".4byte "QU(MaxCHeight)";"
);