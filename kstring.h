# ifndef __K_STRING_H__
# define __K_STRING_H__

# ifndef NULL
#	define NULL 0
# endif /* NULL */

# ifndef _TYPE_SIZE_T
#	define _TYPE_SIZE_T
	typedef signed long ssize_t;
	typedef unsigned long size_t;
# endif /* size_t */

__inline__
int memcmp(const void *p1, const void *p2, size_t ct) {
	if(p1 && p2 && ct) {
		char *a = (char *)p1;
		char *b = (char *)p2;
		while(ct--) {
			int diff = *b++ - *a++;
			if(diff) return diff;
		}

		// Final comparison
		return *b - *a;
	}

	// Check for nulls
	return (int)p2 - (int)p1;
}

__inline__
void *memcpy(void *dst, const void *src, size_t ct) {
	if(dst && src && ct) {
		char *a = (char *)dst;
		char *b = (char *)src;
		while(ct--) *a++ = *b++;
	}

	return dst;
}

__inline__
void *memset(void *dst, int value, size_t ct) {
	if(dst && ct) {
		char *a = dst;
		while(ct--) *a++ = (char)value;
	}

	return dst;
}

__inline__
int strcmp(char *str1, char *str2) {
	if(str1 && str2) {
		while(*str1 && *str2) {
			int diff = *str2++ - *str1++;
			if(diff) return diff;
		}

		// Final comparison
		return *str2 - *str1;
	}

	// Check for nulls
	return (int)str2 - (int)str1;
}

__inline__
char *strcpy(char *dst, char *src) {
	if(dst && src) {
		char *a = dst, *b = src;
		do *a++ = *b++; while(*b);
	}

	return dst;
}

__inline__
int strncmp(const char *str1, const char *str2, size_t ct) {
	return memcmp(str1, str2, ct);
}

__inline__
char *strncpy(char *dst, const char *src, size_t ct) {
	return memcpy(dst, src, ct);
}

__inline__
int strlen(const char *str) {
	int len = 0;
	while(*str++) len++;
	return len;
}

# endif /* kstring.h */