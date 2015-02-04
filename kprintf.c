
# include "kscreen.h"

typedef void (* writer)(char, void **);

static void writeScreen(char ch, void **buffer) {
	writeChar(ch);
	((void)buffer);
}

static void writeBuffer(char ch, void **buffer) {
	void *tmp = *buffer;
	*((char *)tmp) = ch;
	*buffer = tmp + 1;
}

static void bulkWrite(writer out, void **buffer, char *str) {
	if(!str) str = "<NULL>";
	while(*str) out(*str++, buffer);
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

static void printfImpl(writer out, void *buffer, char *fmt, va_list args) {
	char ch;

	if(!fmt) return;
	while((ch = *fmt++)) {
		if(ch != '%') {
			out(ch, &buffer);
		} else {
			switch((ch = *fmt++)) {
				// Single char
				case 'c': {
					out((char)va_arg(args, int), &buffer);
					break;
				}
				// String
				case 's': {
					char *str = va_arg(args, char *);
					bulkWrite(out, &buffer, str);
					break;
				}
				// Escaped
				case '%': {
					out('%', &buffer);
					break;
				}
				// Newline
				case 'n': {
					out('\n', &buffer);
					break;
				}
				// Integer
				case 'd': {
					char tmp[36];
					signed int value = va_arg(args, signed int);
					bulkWrite(out, &buffer, intToStr(tmp, value, 10));
					break;
				}
				// Unsigned
				case 'u': {
					char tmp[36];
					unsigned int value = va_arg(args, unsigned int);
					bulkWrite(out, &buffer, uintToStr(tmp, value, 10));
					break;
				}
				// Hexadecimal
				case 'p':
				case 'x': {
					char tmp[36];
					unsigned int value = va_arg(args, unsigned int);
					bulkWrite(out, &buffer, uintToStr(tmp, value, 16));
					break;
				}
				// Unknown
				default: {
					out(ch, &buffer);
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

void ksprintf(char *buffer, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	kvsprintf(buffer, fmt, args);
	va_end(args);
}

void kvprintf(char *fmt, va_list args) {
	printfImpl(writeScreen, 0, fmt, args);
}

void kvsprintf(char *buffer, char *fmt, va_list args) {
	printfImpl(writeBuffer, buffer, fmt, args);
}
