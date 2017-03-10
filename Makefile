CC=m68k-elf-gcc
CXX=m68k-elf-g++
OBJCOPY=m68k-elf-objcopy

CFLAGS=-Os -g -m68000 -Wall -fomit-frame-pointer -fno-builtin -I. -ffreestanding
CXXFLAGS=-Os -g -m68000 -Wall -fomit-frame-pointer -fno-builtin -I. -fno-exceptions -fno-rtti -fno-implicit-templates -ffreestanding
LDFLAGS=-lgcc

INSTALL=/home/simon/dev/XSteem/hd/C
TARGET=TEST.PRG
# This is where m68k-elf-gcc was built
LIBGCC=/home/simon/gcc-m68k/lib/gcc/m68k-elf/5.3.0/m68000/libgcc.a
TOSLIBS=tos.o aes.o xbios.o aes_window.o
APPLIBS=app_app.o app_window.o
ALLLIBS=crt0.o libc.o $(TOSLIBS) $(APPLIBS) $(LIBGCC)

$(TARGET): test.elf
	@# Strip out .discard section and make .text writable before passing to vlink
	#$(OBJCOPY) --remove-section=.discard --writable-text test.elf ready.o
	/home/simon/dev/vlink/vlink test.elf -b ataritos -o $(TARGET)
	@$(RM) ready.o

$(APPLIBS): app_app.h app_window.h aes.h tos.h aes_window.h

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
	m68k-elf-ld -Tatari.ld --relocatable $^ -o test.elf

debug: test.o $(ALLLIBS)
	m68k-elf-ld -Tdebug.ld $^ -o info.elf

install: $(TARGET)
	cp --target-directory=$(INSTALL) $(TARGET)
