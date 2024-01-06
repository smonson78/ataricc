#include "libc.h"


void show_malloc()
{
    struct memblock_t *p = malloc_head;
    printf("\n");
    while (p) {
        if (p->prev)
            printf("%p <-- ", p->prev);
        else
            printf("    null <-- ", p->prev);
        
        printf("%p (%d)", p, p->size);
        
        if (p->next)
            printf(" --> %p", p->next);
        else
            printf(" --> null", p->next);
 
        printf("\n");
        p = p->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    show_malloc();
    
    char *temp = (char *)malloc(1024);
    char *temp2 = (char *)malloc(1024);

    show_malloc();

    free(temp);
    
    show_malloc();
    free(temp2);

    show_malloc();

    Cnecin();
  
	return 0;
}
