#include <stdint.h>

extern "C" {
#include "libc.h"
}

void *operator new(size_t n)
{
    //printf("operator new\n");
    return malloc(n);
}

void *operator new[] (size_t n)
{
    return ::operator new(n);
}

void operator delete(void *p)
{
    //printf("operator delete\n");
    free(p);
}

void operator delete[] (void *p)
{
    ::operator delete(p);
}

void operator delete(void *p, size_t n)
{
    ::operator delete(p);
}

void operator delete[] (void *p, size_t n)
{
    ::operator delete(p);
}

extern "C" {

typedef void (*func_ptr) (void);
extern func_ptr __CTOR_END__[];
extern func_ptr __DTOR_LIST__[];

__attribute__((section(".ctors"))) func_ptr ctors_start = (func_ptr)-1;
__attribute__((section(".dtors"))) func_ptr dtors_end = (func_ptr)0;

void __do_global_ctors_aux() {
	func_ptr *p;
	for (p = __CTOR_END__ - 1; *p != (func_ptr) -1; p--) {
		//printf("Global constructor: %p\n", p);
		(*p)();
	}
}

void __do_global_dtors_aux()
{
	//printf("dtors\n");
	func_ptr *p;
	for (p = __DTOR_LIST__; *p; p++) {
		//printf("Global Destructor: %p\n", p);
		(*p)();
	}
}
}

