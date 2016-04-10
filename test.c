#include <tos.h>
#include <libc.h>

int main(int argc, char **argv)
{
	char temp[16];
	char *test_string = "HELLO ATARI!\r\n";
	char *p;
	
	Cconws(test_string);
	Cconws("Size of int is: ");
	temp[0] = sizeof(int) + '0';
	temp[1] = '\r';
	temp[2] = '\n';
	temp[3] = '\0';	
	Cconws(temp);
	
	for (p = test_string; *p; p++)
		Cconout(*p);
		
	printf("Hello %% Atari #%c.\n", '2');
		
	Cnecin();

	return 0;
}
