
ifdef XCC
# XCC - Cross Compiler
CC = $(XCC)
endif

# Cross Compiler Flags
CFLAGS  = -Wall -Werror -Wextra \
	-ffreestanding -std=c11 -O2
LDFLAGS = -T linker.ld -nostdlib \
	-ffreestanding -O2 -o
LDLIBS  = -lgcc

# Intermediate Files
objects =			\
	kstart.o		\
	kmain.o			\
	kscreen.o		\

# Output files
bin     = ./bin
kernel  = $(bin)/kernel.bin

all: $(kernel)

.PHONY: clean
clean:
	rm -f $(objects)

$(bin)/%.bin: $(objects)
	$(CC) $(LDFLAGS) $@ $^ $(LDLIBS)

%.o: %.asm
	$(AS) $< -o $@
