
# include "kscreen.h"

# define vram ((vram_data *)0xC00B8000)
# define xlim 80
# define ylim 25

static int  xpos  = 0;
static int  ypos  = 0;
static char color = White;

typedef struct {
	char ch;
	char color;
} vram_data;

void scroll() {
	if(ypos >= ylim) {
		int row, col, pos;

		// Shift rows upwards
		for(row = 0; row < ylim - 1; row++) {
			for(col = 0; col < xlim; col++) {
				vram_data *old, *new;
				pos = row * xlim + col;

				new = &vram[pos];
				old = &vram[pos + xlim];

				new->ch = old->ch;
				new->color = old->color;
			}
		}

		// Clear final row
		for(; row < ylim; row++) {
			for(col = 0; col < xlim; col++) {
				vram_data *ptr;
				pos = row * xlim + col;

				ptr = &vram[pos];
				ptr->ch = '\0';
				ptr->color = color;
			}
		}
	}
}

void clear() {
	int pos;
	xpos = ypos = 0;
	for(pos = 0; pos < xlim * ylim; pos++) {
		vram[pos].ch = '\0';
		vram[pos].color = color;
	}
}

void writeChar(char ch) {
	if(ch == '\n') {
		xpos = 0;
		ypos++;
	} else {
		int pos = xpos + ypos * xlim;
		vram_data *data = &vram[pos];

		data->ch = ch;
		data->color = color;

		// Increment position
		if(xpos++ >= xlim) {
			xpos = 0;
			ypos++;
		}
	}

	// Scroll if necessary
	scroll();
}

void writeString(char *str) {
	if(!str) str = "<NULL>";
	while(*str) writeChar(*str++);
}

void setColor(char back, char fore) {
	color = ((back & 0xF) << 4) | (fore & 0xF);
}

void setCursor(int _xpos, int _ypos) {
	xpos = _xpos;
	ypos = _ypos;
}
