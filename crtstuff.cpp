#include <stdint.h>

#define ATEXIT_MAX_FUNCS 16

extern "C" {
#include "libc.h"
}

void *operator new(size_t n)
{
    return malloc(n);
}

void *operator new[] (size_t n)
{
    return ::operator new(n);
}

void operator delete(void *p)
{
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
  void *__dso_handle = nullptr;

	__attribute__((section(".ctors"))) func_ptr ctors_start = (func_ptr)-1;
	__attribute__((section(".dtors"))) func_ptr dtors_end = (func_ptr)0;

	struct atexit_func_entry_t
	{
		void (*destructor_func)(void *);
		void *obj_ptr;
		void *dso_handle;
	};
	atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
	uint8_t __atexit_func_count = 0;

	void __do_global_ctors_aux()
  {
		func_ptr *p;
		for (p = __CTOR_END__ - 1; *p != (func_ptr) -1; p--) {
			(*p)();
		}
	}

	void __do_global_dtors_aux()
	{
		func_ptr *p;
		for (p = __DTOR_LIST__; *p; p++) {
			(*p)();
		}
	}

	// NOTE: These __cxa_* functions are taken from wiki.osdev.org
	void __cxa_pure_virtual()
	{
	}

	int __cxa_atexit(void (*f)(void *), void *objptr, void *dso)
	{
		if (__atexit_func_count >= ATEXIT_MAX_FUNCS)
			return -1;
		__atexit_funcs[__atexit_func_count].destructor_func = f;
		__atexit_funcs[__atexit_func_count].obj_ptr = objptr;
		__atexit_funcs[__atexit_func_count].dso_handle = dso;
		__atexit_func_count++;
		return 0;
	}

	void __cxa_finalize(void *f)
  {
		uint16_t i = __atexit_func_count;
		if (!f) {
			while (i--) {
				if (__atexit_funcs[i].destructor_func) {
					(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
				}
			}
			return;
		}

		while (i--) {
			if (__atexit_funcs[i].destructor_func == f) {
				(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
				__atexit_funcs[i].destructor_func = 0;
			}
		}
	}
}
