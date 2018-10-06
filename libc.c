#include <libc.h>
#include <tos.h>
#include <stdarg.h>

FILE *stdout = (FILE *)1;

static int16_t fmt_uint(uint32_t val, int16_t base, char *buf)
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

static int16_t fmt_int(int32_t val, int16_t base, char *buf)
{
	static const char *digits = "0123456789abcdef";
	char temp[10];
	int16_t size = 0;
	int16_t i;
	int16_t neg;

	/* Handle special case of 0 */
	if (val == 0) {
		buf[0] = '0';
		buf[1] = 0;
		return 1;
	}

	if (val < 0) {
		neg = 1;
		val = -val;
		buf[0] = '-';
	} else {
		neg = 0;
	}

	/* Convert number to series of digits */
	while (val)	{
		temp[size++] = digits[val % base];
		val /= base;
	}

	/* Reverse digits into output buffer */
	for (i = 0; i < size; i++) {
		buf[size - i - 1 + neg] = temp[i];
	}

	buf[size + neg] = 0;
	return size + neg;
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
					length = fmt_int(va_arg(arg, long int), 10, temp);
				else
					length = fmt_int(va_arg(arg, int), 10, temp);
				break;

      case 'u':
				if (longarg)
					length = fmt_uint(va_arg(arg, long int), 10, temp);
				else
					length = fmt_uint(va_arg(arg, int), 10, temp);
				break;

			case 'x':
				if (longarg)
					length = fmt_uint(va_arg(arg, long int), 16, temp);
				else
					length = fmt_uint(va_arg(arg, int), 16, temp);
				break;

			case 'p':
				length = fmt_uint(va_arg(arg, long int), 16, temp);
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

void memcpy(void *dest, const void *src, size_t bytes)
{
	while (bytes--) {
		*((char *)dest++) = *((char *)src++);
	}
}

size_t strlen(const char *s)
{
	const char *p = s;
	while (*p)
		p++;
	return (size_t)p - (size_t)s;
}

void exit(uint16_t retval)
{
	_exit(retval);
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
