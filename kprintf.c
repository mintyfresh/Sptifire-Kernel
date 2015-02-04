
# include "kscreen.h"

typedef void (* writer)(char);

static void bulkWrite(writer out, char *str) {
	if(!str) str = "<NULL>";
	while(*str) out(*str++);
}

static void swap(char *a, char *b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

static char *reverseStr(char *str, int length) {
	int pos;
	for(pos = 0; pos < length / 2; pos++)
		swap(&str[pos], &str[length - pos - 1]);
	return str;
}

static char *intToStr(char *str, signed int value, int base) {
	static char *chars = "0123456789ABCDEF";

	if(value == 0 || base < 2 ||
			base > 16) {
		str[0] = '0';
		str[1] = '\0';
		return str;
	} else {
		int negate = 0, pos = 0;

		if(value < 0) {
			value = -value;
			negate = 1;
		}

		while(value != 0) {
			int curr = value % base;
			str[pos++] = chars[curr];
			value /= base;
		}

		if(negate)
			str[pos++] = '-';
		str[pos] = '\0';

		// Flip the number around
		return reverseStr(str, pos);
	}
}

static char *uintToStr(char *str, unsigned int value, int base) {
	static char *chars = "0123456789ABCDEF";

	if(base < 2 || base > 16) {
		str[0] = '0';
		str[1] = '\0';
		return str;
	} else {
		int pos = 0;
		while(value != 0) {
			int curr = value % base;
			str[pos++] = chars[curr];
			value /= base;
		}

		str[pos] = '\0';

		// Flip the number around
		return reverseStr(str, pos);
	}
}

static void printfImpl(writer out, char *fmt, va_list args) {
	char ch;

	if(!fmt) return;
	while((ch = *fmt++)) {
		if(ch != '%') {
			out(ch);
		} else {
			switch((ch = *fmt++)) {
				// Single char
				case 'c': {
					out((char)va_arg(args, int));
					break;
				}
				// String
				case 's': {
					char *str = va_arg(args, char *);
					bulkWrite(out, str);
					break;
				}
				// Escaped
				case '%': {
					out('%');
					break;
				}
				// Newline
				case 'n': {
					out('\n');
					break;
				}
				// Integer
				case 'd': {
					char buffer[36];
					signed int value = va_arg(args, signed int);
					bulkWrite(out, intToStr(buffer, value, 10));
					break;
				}
				// Unsigned
				case 'u': {
					char buffer[36];
					unsigned int value = va_arg(args, unsigned int);
					bulkWrite(out, uintToStr(buffer, value, 10));
					break;
				}
				// Hexadecimal
				case 'p':
				case 'x': {
					char buffer[36];
					unsigned int value = va_arg(args, unsigned int);
					bulkWrite(out, uintToStr(buffer, value, 16));
					break;
				}
				// Unknown
				default: {
					out(ch);
					break;
				}
			}
		}
	}
}

void kprintf(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	kvprintf(fmt, args);
	va_end(args);
}

void kvprintf(char *fmt, va_list args) {
	printfImpl(writeChar, fmt, args);
}
