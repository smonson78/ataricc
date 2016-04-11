#include <libc.h>
#include <tos.h>
#include <stdarg.h>

FILE *stdout = (FILE *)1;

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
		temp[size++] = val % base;
		val /= base;
	}
	
	/* Reverse digits into output buffer */
	for (i = 0; i < size; i++) {
		buf[size - i - 1] = digits[(int)temp[i]];
	}

	//buf[size] = 0;
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
			while (*format >= '0' && *format <= '9')
			{
				width *= 10;
				width += (*format) % 10;
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

int printf (const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);
   done = vfprintf (stdout, format, arg);
   va_end (arg);

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
