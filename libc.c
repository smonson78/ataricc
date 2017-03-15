#include <libc.h>
#include <tos.h>
#include <stdarg.h>

FILE *stdout = (FILE *)1;

struct memblock_t *malloc_head;
size_t malloc_total_size;

void malloc_init(size_t memsize)
{
    malloc_head = (struct memblock_t *)Malloc(memsize);
    if (malloc_head) {
        malloc_total_size = memsize;
        malloc_head->size = memsize - sizeof(struct memblock_t);
        malloc_head->next = NULL;
        malloc_head->prev = NULL;
        malloc_head->used = 0;
    }
    else
        malloc_total_size = 0;
}

static int16_t fmt_int(uint32_t val, int16_t base, int16_t neg, char *buf)
{
	static const char *digits = "0123456789abcdef";
	char temp[10];
	int16_t size = 0;
	int16_t i;
	
	/* Handle special case of 0 */
	if (val == 0) {
		buf[0] = '0';
		buf[1] = 0;
		return 1;
	}
	
	/* Convert number to series of digits */
	while (val)	{
		temp[size++] = digits[val % base];
		val /= base;
	}
	
	/* Reverse digits into output buffer */
	for (i = 0; i < size; i++) {
		buf[size - i - 1] = temp[i];
	}

	buf[size] = 0;
	return size;
}

int vfprintf(FILE *stream, const char *format, va_list arg)
{
	char temp[11];
	uint16_t i;
	
	while (*format)
	{
		if (*format == '%')
		{
			int16_t width = 0;
			int16_t neg = 0;
			int16_t fill = ' ';
			int16_t ljust = 0;
			uint16_t done = 0;
			uint16_t longarg = 0;
			int16_t length;

			format++;
			
			/* Get modifiers first */
			while (!done)
			{
				switch (*format)
				{
				case '-':
					format++;
					ljust = 1; break;
				case '0':
					format++;
					fill = '0'; break;
				default:
					done = 1; 	break;
				}
			}

			/* Field width */
			while (isdigit(*format))
			{
				width *= 10;
				width += *format - '0';
				format++;
			}
			
			if (*format == 'l') {
				longarg = 1;
				format++;
			}
			
			switch (*format)
			{
			case '%':
				temp[0] = '%';
				length = 1;
				break;
					
			case 'c':
				temp[0] = (char)va_arg(arg, int);
				length = 1;
				break;
				
			case 'd':
			case 'i':
				if (longarg)
					length = fmt_int(va_arg(arg, long int), 10, neg, temp);
				else
					length = fmt_int(va_arg(arg, int), 10, neg, temp);
				break;
				
			case 'x':
				if (longarg)
					length = fmt_int(va_arg(arg, long int), 16, neg, temp);
				else
					length = fmt_int(va_arg(arg, int), 16, neg, temp);
				break;

			case 'p':
				length = fmt_int(va_arg(arg, long int), 16, 0, temp);
				width = 8;
				fill = '0';
				break;
				
		    case 's':
		        // FIXME: this has to skip the 'temp' stuff
		        Cconws(va_arg(arg, const char *));
		        length = 0;
                break;
                
			default:
				/* It's an error! */
				continue;
			}
			
			temp[length] = 0;
			if (ljust)
				Cconws(temp);
				
			for (i = length; i < width; i++)
				Cconout(fill);
			
			if (!ljust)
				Cconws(temp);
		}
		else
		{
			if (*format == '\n')
				Cconout('\r');
			Cconout(*format);
		}
		
		format++;
	}
	
	return 0;
}

int16_t isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int printf(const char *format, ...)
{
   va_list arg;
   int done;

   va_start(arg, format);
   done = vfprintf(stdout, format, arg);
   va_end(arg);

   return done;
}

int puts(const char *s)
{
	for (; *s; s++)
	{
		if (*s == '\n')
			Cconout('\r');
		Cconout(*s);
	}
	return 0;
}

void memcpy(void *dest, void *src, size_t bytes)
{
	while (bytes--) {
		*((char *)dest++) = *((char *)src++);
	}
}

void exit(uint16_t retval)
{
	_exit(retval);
}

//#define MALLOC_DEBUG
void *malloc(size_t size) {
    struct memblock_t *p, *next;
    
    if (size < MALLOC_MIN_ALLOCATION)
        size = MALLOC_MIN_ALLOCATION;

#if defined MALLOC_DEBUG
    printf("malloc called\n");
    printf("  searching for a block of size %d\n", size);
#endif

    p = malloc_head;
    while (p && (p->size < size || p->used)) {

#if defined MALLOC_DEBUG
        printf("  skipping block of size %d\n", p->size);
#endif
    	p = p->next;
    }
    
    if (!p) {
#if defined MALLOC_DEBUG
        printf("  insufficient free memory available.\n");
#endif
    	return 0;
    }

#if defined MALLOC_DEBUG
    printf("  Found unused block of size %d\n", p->size);
#endif
    
    if (p->size > size + sizeof(struct memblock_t) + MALLOC_MIN_ALLOCATION) {
        //printf("  Block is big enough to split (excess: %d bytes)\n",
        //    p->size - sizeof(struct memblock_t) - size);

        next = (void *)p + sizeof(struct memblock_t) + size;
        next->prev = p;
        next->next = p->next;
        next->size = p->size - size - sizeof(struct memblock_t);
        next->used = 0;
        p->next = next;
        p->size = size;
        //printf("  p = %p\n", p);
        //printf("  next = %p\n", next);
    }
    
    p->used = 1;
    return (void *)p + sizeof(struct memblock_t);
}

void free (void *m) {
    //printf("free called (%p)\n", m);
    struct memblock_t *p = m - sizeof(struct memblock_t);
    struct memblock_t *other;
    
    //printf("  freeing block at %p\n", p);
    if (p->used != 1) {
        printf("  error: free() called on unknown block %p (%d)\n", p, p->used);
        return;
    }
    
    if (p->prev && p->prev->used == 0) {
        //printf("  prev block is free, can combine\n");
        other = p->prev;
        other->next = p->next;
        other->size += p->size + sizeof(struct memblock_t);
        if (p->next)
            p->next->prev = other;
        p = other;
    }
    
    if (p->next && p->next->used == 0) {
        //printf("  next block is free, can combine\n");
        other = p->next;
        p->next = other->next;
        p->size += other->size + sizeof(struct memblock_t);
        if (p->next)
            p->next->prev = p;
    }
    
    p->used = 0;
}

void abort() {
    printf("abort called\n");
}

void memset(void *dest, int c, size_t bytes) {
    while (bytes--) {
        *((char *)dest++) = (char)c;
    }
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    while (n--) {
        if (*(uint8_t *)s1 != *(uint8_t *)s2)
            return *(uint8_t *)s1 - *(uint8_t *)s2;
        s1++;
        s2++;
    }
    return 0;
}

int strlen(const char *src) {
    printf("strlen called\n");
    return 0;
}

