#include <tos.h>
#include <libc.h>

int main(int argc, char **argv)
{
	char *test_string = "HELLO ATARI!\r\n";
	char *p;
	char *buf;
	
	Cconws(test_string);
	printf("Size of char is: %ld\n", sizeof(char));
	printf("Size of short int is: %ld\n", sizeof(short int));
	printf("Size of int is: %ld\n", sizeof(int));
	printf("Size of long int is: %ld\n", sizeof(long int));
	printf("Size of pointer int is: %ld\n", sizeof(void *));
	
	for (p = test_string; *p; p++)
		Cconout(*p);
		
	printf("Hello %% Atari #%c.\n", '2');
	printf("Hello %% Atari #%d.\n", 123456789);
	printf("Hello %% Atari 0x%x.\n", 0x12345678);

	printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	buf = Malloc(32 * 1024);
	printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	Mfree(buf);
	printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	
	printf("Random: 0x%06x\n", Random());
	printf("Random: 0x%06x\n", Random());
	printf("Random: 0x%06x\n", Random());	
	
	Cnecin();

	return 0;
}
