CC=m68k-elf-gcc
CXX=m68k-elf-g++
OBJCOPY=m68k-elf-objcopy

CFLAGS=-Os -g -m68000 -Wall -fomit-frame-pointer -fno-builtin -I. -ffreestanding
CXXFLAGS=-Os -g -m68000 -Wall -fomit-frame-pointer -fno-builtin -I. -fno-exceptions -fno-rtti -fno-implicit-templates -ffreestanding
LDLIBS=-lgcc
LDFLAGS=-nostdlib

INSTALL=/home/simon/dev/atari-hd
TARGET=TEST.PRG
LIBGCC:=$(shell $(CXX) $(CFLAGS) --print-libgcc-file-name)
TOSLIBS=tos.o aes.o xbios.o aes_window.o
APPLIBS=app.o app_window.o MenuBar.o Menu.o MenuItem.o
ALLLIBS=crt0.o crtstuff.o libc.o $(TOSLIBS) $(APPLIBS)

all: $(TARGET)

$(TARGET): test.elf
	@# Strip out .discard section and make .text writable before passing to vlink
	#$(OBJCOPY) --remove-section=.discard --writable-text test.elf ready.o
	/home/simon/dev/vlink/vlink test.elf -b ataritos -o $(TARGET)
	@$(RM) ready.o

$(APPLIBS): app.h app_window.h aes.h tos.h aes_window.h

clean:
	$(RM) $(TARGET) *.o *.elf test.bin
	$(RM) *~

dasm: $(TARGET)
	@dd bs=1 skip=28 if=$(TARGET) of=test.bin
	@m68k-elf-objdump -m m68k -D -b binary test.bin
	@$(RM) test.bin

info: debug
	@m68k-elf-objdump -h test.elf

elf: test.elf
test.elf: test.o $(ALLLIBS)
	@# Run linker, generate a relocatable object file of the whole project
	$(CC) -Tatari.ld -Wl,--relocatable $(LDFLAGS) $^ $(LDLIBS) -o test.elf

debug: test.o $(ALLLIBS)
	m68k-elf-ld -Tdebug.ld $^ -o info.elf

install: $(TARGET)
	cp --target-directory=$(INSTALL) $(TARGET)
