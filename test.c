#include <tos.h>
#include <aes.h>

#include <libc.h>

extern int16_t screen_phandle;
extern int16_t screen_vhandle;

// System timer
#define _hz_200 ((volatile uint32_t *)0x4ba)

int16_t open_vwork(int16_t phys_handle)
{
	int16_t work_in[11];
	int16_t work_out[57];
	int16_t new_handle;
	int16_t i;
	
	for (i = 0; i < 10; i++) {
		work_in[i] = 1;
	}
	work_in[10] = 2;
	new_handle = phys_handle;
	v_opnvwk(work_in, &new_handle, work_out);
	return new_handle;
}

int main(int argc, char **argv)
{
	int app_id;
	int16_t gr_wchar, gr_hchar;
	int16_t gr_wbox, gr_hbox;

	printf("Started up OK.\n");

	app_id = appl_init();
	if (app_id < 0) {
		Cconws("***> Initialization error.\n");
		Cconws("Press any key to continue.\n");
		Cnecin();
		exit(1);
	}

	printf("Application ID: 0x%08x\n", app_id);
	
	screen_phandle = graf_handle(&gr_wchar, &gr_hchar, &gr_wbox, &gr_hbox);
	printf("Screen phandle: 0x%08x\n", screen_phandle);
	Cnecin();

	screen_vhandle = open_vwork(screen_phandle);
	printf("Screen vhandle: 0x%08x\n", screen_vhandle);
		
	//set_screen_attr();
	printf("Resolution: %d\n", Getrez());
	
	if (0) 
	{
	  //Cconws(test_string);
	  printf("Size of char is: %ld\n", sizeof(char));
	  printf("Size of short int is: %ld\n", sizeof(short int));
	  printf("Size of int is: %ld\n", sizeof(int));
	  printf("Size of long int is: %ld\n", sizeof(long int));
	  printf("Size of pointer int is: %ld\n", sizeof(void *));
	
	  //for (p = test_string; *p; p++)
		//  Cconout(*p);
		
	  printf("Hello %% Atari #%c.\n", '2');
	  printf("Hello %% Atari #%d.\n", 123456789);
	  printf("Hello %% Atari 0x%x.\n", 0x12345678);

	  printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	  char *buf = Malloc(32 * 1024);
	  printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	  Mfree(buf);
	  printf("Largest allocatable block: %ld bytes\n", (long int)Malloc(-1));
	
	  printf("Random: 0x%06x\n", Random());
	  printf("Random: 0x%06x\n", Random());
	  printf("Random: 0x%06x\n", Random());	
	
	  Cnecin();
  }
  
	/* End */
	Cnecin();
	v_clsvwk(screen_vhandle);
	appl_exit();
  
	return 0;
}
