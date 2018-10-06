SECTIONS {
	. = 0;
	.text : {
		crt0.o (.entry)
		/* Normal .text */
		*(.text)
		/* C++ static methods seem to go into their own segment */
		*(.text.*)
		PROVIDE(_etext = .);
	}
	.data : {
		*(.data*)
		*(.rodata*)
		. = ALIGN(4);
		PROVIDE(__CTOR_LIST__ = .);
		crtstuff.o(.ctors)
		*(.ctors)
		PROVIDE(__CTOR_END__ = .);
		PROVIDE(__DTOR_LIST__ = .);
		*(.dtors)
		crtstuff.o(.dtors)
		PROVIDE(__DTOR_END__ = .);
		PROVIDE(_edata = .);
	}
	.bss : {
		*(.bss)
		. = ALIGN(2);
		PROVIDE(_end = .);
	}
	/* Allow a 16KB stack */
	. = . + 0x4000;
	stack = ALIGN(2);

	/DISCARD/ : {
		*(.group)
		*(.comment)
		*(.debug*)
	}
}
