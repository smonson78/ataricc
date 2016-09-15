CC=m68k-elf-gcc
CFLAGS=-g -m68000 -Wall -fomit-frame-pointer -fno-builtin -I.
LDFLAGS=-lgcc

INSTALL=/home/simon/dev/XSteem/hd
TARGET=TEST.PRG
LIBGCC=/home/simon/gcc-m68k/lib/gcc/m68k-elf/5.3.0/m68000/libgcc.a

$(TARGET): test.elf
	@# Strip out .discard section and make .text writable before passing to vlink
	m68k-elf-objcopy --remove-section=.discard --writable-text test.elf ready.o
	/home/simon/dev/vlink/vlink ready.o -b ataritos -o $(TARGET)
	@$(RM) ready.o
	
test.o: test.c
crt0.o: crt0.c

clean:
	$(RM) $(TARGET) *.o *.elf test.bin
	$(RM) *~

dasm: $(TARGET)
	@dd bs=1 skip=28 if=$(TARGET) of=test.bin
	@m68k-elf-objdump -m m68k -D -b binary test.bin
	@$(RM) test.bin

info: debug
	@m68k-elf-objdump -h info.elf

elf: test.elf
test.elf: crt0.o test.o tos.o libc.o aes.o xbios.o $(LIBGCC)
	@# Run linker, generate a relocatable object file of the whole project
	m68k-elf-ld -Tatari.ld --relocatable $^ -o test.elf
	#m68k-elf-ld -Tatari.ld $^ -o info.elf

debug: crt0.o test.o tos.o libc.o aes.o $(LIBGCC)
	m68k-elf-ld -Tdebug.ld $^ -o info.elf

install: $(TARGET)
	cp --target-directory=$(INSTALL) $(TARGET)
