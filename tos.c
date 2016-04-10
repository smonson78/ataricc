#include <stdint.h>
#include <stdarg.h>

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

int32_t Cnecin()
{
	register int32_t val __asm__("d0");
    __asm__ __volatile__
    (
        "move.w #7,-(%%sp)\n\t"
        "trap #1\n\t"
        "addq.l #2,%%sp\n\t"
    : "=r"(val)/* outputs */
    : /* inputs */
    : "d1", "d2", "a0", "a1", "a2" /* clobbered regs */
    );
    return val;
}

#if 1
typedef struct {
} FILE;

FILE *stdout = (FILE *)1;

int vfprintf(FILE *stream, const char *format, va_list arg)
{
	return 0;
}

int __printf (const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);
   done = vfprintf (stdout, format, arg);
   va_end (arg);

   return done;
}



#endif
