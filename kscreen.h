# ifndef __K_SCREEN_H__
# define __K_SCREEN_H__

# include <stdarg.h>

enum Colors {
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGrey,
	DarkGrey,
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightMagenta,
	Yellow,
	White
};

void clear();

void writeChar(char ch);

void writeString(char *str);

void setColor(char back, char fore);

void setCursor(int xpos, int ypos);

/* - kprintf - */

void kprintf(char *fmt, ...);

void ksprintf(char *buffer, char *fmt, ...);

void kvprintf(char *fmt, va_list args);

void kvsprintf(char *buffer, char *fmt, va_list args);

# endif /* kscreen.h */