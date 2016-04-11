#include <stdint.h>

#include "tos.h"


void Cconws(const char* s)
{
    __asm__ __volatile__
    (
        "move.l %0,-(%%sp)\n\t"
        "move.w #9,-(%%sp)\n\t"
        "trap #1\n\t"
        "addq.l #6,%%sp\n\t"
    : /* outputs */
    : "g"(s) /* inputs */
    : "d0", "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
}

void Cconout(const uint16_t ch)
{
    __asm__ __volatile__
    (
		"move.w %0,-(%%sp)\n\t"
		"move.w #2,-(%%sp)\n\t"
		"trap #1\n\t"
		"addq.l #4,%%sp\n\t"
		: /* outputs */
        : "r"(ch) /* inputs */
        : "d0", "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
	);
}	

int32_t Cnecin()
{
	register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
        "move.w #7,-(%%sp)\n\t"
        "trap #1\n\t"
        "addq.l #2,%%sp\n\t"
    : "=r"(val) /* outputs */
    : /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}

void *Malloc(int32_t number)
{
	register void *val __asm__("d0");
    __asm__ __volatile__
    (
		"move.l %1,-(%%sp)\n\t"
		"move.w #72,-(%%sp)\n\t"
		"trap #1\n\t"
		"addq.l #6,%%sp\n\t"
		: "=r"(val) /* outputs */
        : "r"(number) /* inputs */
        : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
	);
	return val;
}	

int32_t Mfree(void *block)
{
	register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
    	"move.l %1,-(%%sp)\n\t"
        "move.w #73,-(%%sp)\n\t"
        "trap #1\n\t"
        "addq.l #6,%%sp\n\t"
    : "=r"(val) /* outputs */
    : "r"(block) /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}

int32_t Mshrink(void *block, int32_t newsize)
{
	register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
    	"move.l %2,-(%%sp)\n\t"
    	"move.l %1,-(%%sp)\n\t"
        "move.w #74,-(%%sp)\n\t"
        "trap #1\n\t"
        "add.l #10,%%sp\n\t"
    : "=r"(val) /* outputs */
    : "r"(block), "r"(newsize) /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}


int32_t Random()
{
	register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
        "move.w #17,-(%%sp)\n\t"
        "trap #14\n\t"
        "addq.l #2,%%sp\n\t"
    : "=r"(val) /* outputs */
    : /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}


