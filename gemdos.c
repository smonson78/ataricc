#include "gemdos.h"

int32_t gem_super(void *stack)
{
  register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
      "pea      (%1)\n\t"
      "move.w    #32,-(%%sp)\n\t"
      "trap      #1\n\t"
      "addq.l    #6,%%sp\n\t"
    : "=r"(val) /* outputs */
    : "p"(stack) /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}
