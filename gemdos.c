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

int16_t Fcreate(const int8_t *fname, int16_t attr)
{
  register uint16_t val __asm__("d0");
  __asm__ __volatile__
  (
    "move.w    %2,-(%%sp)\n\t"
    "pea       (%1)\n\t"
    "move.w    #60,-(%%sp)\n\t"
    "trap      #1\n\t"
    "addq.l    #8,%%sp\n\t"
  : "=r"(val) /* outputs */
  : "p"(fname), "r"(attr) /* inputs */
  : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );
  return val;
}

int32_t Fopen(const char *fname, int16_t mode)
{
    register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
      "move.w    %2,-(%%sp)\n\t"
      "pea       (%1)\n\t"
      "move.w    #61,-(%%sp)\n\t"
      "trap      #1\n\t"
      "addq.l    #8,%%sp\n\t"
    : "=r"(val) /* outputs */
    : "p"(fname), "r"(mode) /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}

void Fclose(const FILE handle)
{
    __asm__ __volatile__
    (
      "move.w    %0,-(%%sp)\n\t"
      "move.w    #62,-(%%sp)\n\t"
      "trap      #1\n\t"
      "addq.l    #4,%%sp\n\t"
    :  /* outputs */
    : "r"(handle) /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
}

int32_t Fwrite(FILE handle, int32_t count, void *buf)
{
  register int32_t val __asm__("d0");
  __asm__ __volatile__
  (
    "pea       (%3)\n\t"
    "move.l    %2,-(%%sp)\n\t"
    "move.w    %1,-(%%sp)\n\t"
    "move.w    #64,-(%%sp)\n\t"
    "trap      #1\n\t"
    "lea       12(%%sp),%%sp\n\t"
  : "=r"(val) /* outputs */
  : "r"(handle), "r"(count), "p"(buf) /* inputs */
  : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );
  return val;
}

int32_t Fread(FILE handle, int32_t count, void *buf)
{
  register int32_t val __asm__("d0");
  __asm__ __volatile__
  (
    "pea       (%3)\n\t"
    "move.l    %2,-(%%sp)\n\t"
    "move.w    %1,-(%%sp)\n\t"
    "move.w    #63,-(%%sp)\n\t"
    "trap      #1\n\t"
    "lea       12(%%sp),%%sp\n\t"
  : "=r"(val) /* outputs */
  : "r"(handle), "r"(count), "p"(buf) /* inputs */
  : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );
  return val;
}

uint32_t Tgettime()
{
  register uint32_t val __asm__("d0");
  __asm__ __volatile__
  (
    "move.w    #44,-(%%sp)\n\t"
    "trap      #1\n\t"
    "addq.l    #2,%%sp\n\t"
  : "=r"(val) /* outputs */
  : /* inputs */
  : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
  );
  return val;
}
