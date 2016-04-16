SECTIONS {
	. = 0;
	.text : {
		crt0.o (.entry)
		*(.text.startup)
		*(.text)
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
	
	.comment : {
		*(.comment)
	}
	.debug : {
		*(.debug*)
	}
}

