
extern "C" {
#include <gemdos.h>
#include <xbios.h>
#include <libc.h>
}

#define SHIFTER_BASE (uint16_t *)(0xFF8240)

#include "app.h"
#include "LinkedListNode.h"

int super()
{
  int i;
  for (i = 18; i < 32; i += 2) {
    uint16_t temp1 = *(SHIFTER_BASE + i);
    uint16_t temp2 = *(SHIFTER_BASE + i + 1);

    *(SHIFTER_BASE + i) = i;
    *(SHIFTER_BASE + i + 1) = i + 1;

    printf("%p %04x    %p %04x\n",
      SHIFTER_BASE + i, *(SHIFTER_BASE + i),
      SHIFTER_BASE + i + 1, *(SHIFTER_BASE + i + 1)
    );

    *(SHIFTER_BASE + i) = 0x1000 + i;
    *(SHIFTER_BASE + i + 1) = 0x2000 + i + 1;

    printf("%p %04x    %p %04x\n",
      SHIFTER_BASE + i, *(SHIFTER_BASE + i),
      SHIFTER_BASE + i + 1, *(SHIFTER_BASE + i + 1)
    );

    *(SHIFTER_BASE + i) = temp1;
    *(SHIFTER_BASE + i + 1) = temp2;

  }
  return 0;
}

int main(int argc, char **argv)
{
  printf("Testing shifter registers\n");

  xbios_supexec(super);



  Cnecin();

  return 0;
}
