CC=m68k-elf-gcc
CXX=m68k-elf-g++
OBJCOPY=m68k-elf-objcopy

STD_CFLAGS=-m68000 -fomit-frame-pointer -fno-builtin -I. -ffreestanding -ffunction-sections
CFLAGS=-Os -g -Wall $(STD_CFLAGS)
CXXFLAGS=-Os -g -Wall -fno-exceptions -fno-rtti $(STD_CFLAGS)
LDLIBS=-lgcc
LDFLAGS=-m68000 -nostdlib -Wl,--relocatable
# -Wl,--gc-sections -Wl,--entry=_start

INSTALL=/home/simon/atari-hd
TARGET=TEST
LIBGCC:=$(shell $(CXX) $(CFLAGS) --print-libgcc-file-name)
TOSLIBS=tos.o aes.o xbios.o aes_window.o gemdos.o
APPLIBS=app.o app_window.o MenuBar.o Menu.o MenuItem.o LinkedList.o
ALLLIBS=crt0.o crtstuff.o libc.o libcpp.o $(TOSLIBS) $(APPLIBS) dlmalloc.o

# For later
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

all: $(TARGET).PRG

$(TARGET).PRG: $(TARGET).elf
	@# Strip out .discard section and make .text writable before passing to vlink
	@#$(OBJCOPY) --remove-section=.discard --writable-text $^ ready.o
	/home/simon/dev/vlink/vlink $^ -b ataritos -o $@
	@#$(RM) ready.o

$(APPLIBS): app.h app_window.h aes.h tos.h aes_window.h
$(APPLIBS): LinkedList.h LinkedListNode.h

dlmalloc.o: dlmalloc.c
	$(CC) $(STD_CFLAGS) -O3 -DLACKS_SYS_TYPES_H -DHAVE_MORECORE=0 -DNO_MALLOC_STATS -DLACKS_ERRNO_H \
		-DLACKS_TIME_H -DLACKS_STDLIB_H -DLACKS_SYS_MMAN_H -DLACKS_FCNTL_H -DLACKS_UNISTD_H \
		-DLACKS_SYS_PARAM_H -DLACKS_ERRNO_H -DNO_MALLINFO -DMMAP_CLEARS=0 -DNO_MALLOC_STATS \
		-DDEFAULT_TRIM_THRESHOLD=131072 -DNO_SEGMENT_TRAVERSAL -DHAVE_MREMAP=0 -g -c -o $@ $^

clean:
	$(RM) $(TARGET) *.o *.elf test.bin
	$(RM) *~

dasm: $(TARGET)
	@dd bs=1 skip=28 if=$(TARGET) of=test.bin
	@m68k-elf-objdump -m m68k -D -b binary test.bin
	@$(RM) test.bin

info: debug
	@m68k-elf-objdump -h info.elf

elf: $(TARGET).elf
$(TARGET).elf: test.o $(ALLLIBS)
	@# Run linker, generate a relocatable object file of the whole project
	$(CXX) -Tatari.ld $(LDFLAGS) $^ $(LDLIBS) -o $(TARGET)1.elf
	$(OBJCOPY) --set-section-flags .data=ALLOC,READONLY,DATA \
		--set-section-flags .text*=ALLOC,CODE \
		$(TARGET)1.elf $@

debug: test.o $(ALLLIBS)
	$(CXX) -Tdebug.ld $(LDFLAGS) $^ $(LDLIBS) -o info.elf

install: $(TARGET).PRG
	cp --target-directory=$(INSTALL) $^
