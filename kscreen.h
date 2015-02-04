# ifndef __K_SCREEN_H__
# define __K_SCREEN_H__

void clear();

void writeChar(char ch);

void writeString(char *str);

void setColor(char back, char fore);

void setCursor(int xpos, int ypos);

# endif /* kscreen.h */