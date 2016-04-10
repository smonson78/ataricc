#include <tos.h>

int main(int argc, char **argv)
{
	char temp[16];
	Cconws("HELLO ATARI!\r\n");
	Cconws("Size of int is: ");
	temp[0] = sizeof(int) + '0';
	temp[1] = '\r';
	temp[2] = '\n';
	temp[3] = '\0';	
	Cconws(temp);
	
	temp[0] = Cnecin();
	Cconws(temp);
	Cnecin();

	return 0;
}
