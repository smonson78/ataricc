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
		*(.rodata*)
		*(.data*)
		. = ALIGN(2);
		PROVIDE(_edata = .);
	}
	.bss : {
		*(.bss)
		. = ALIGN(2);
		PROVIDE(_end = .);
	}
	. = . + 0x4000;
	stack = ALIGN(2);
	
	.discard : {
		*(.comment)
		*(.debug*)
	}
}

