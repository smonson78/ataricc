using namespace std;

#include <cstdint>

extern "C" {
#include <libc.h>
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
