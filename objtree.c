#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>


typedef struct
{
    int16_t ob_next;    /* The next object               */
    int16_t ob_head;    /* First child                   */
    int16_t ob_tail;    /* Last child                    */
    uint16_t ob_type;   /* Object type                   */
    uint16_t ob_flags;  /* Manipulation flags            */
    uint16_t ob_state;  /* Object status                 */
    uint32_t ob_spec;      /* More under object type        */
    uint16_t ob_x;      /* X-coordinate of the object    */
    uint16_t ob_y;      /* Y-coordinate of the object    */
    uint16_t ob_width;  /* Width of the object           */
    uint16_t ob_height; /* Height of the object          */
} OBJECT;

#define WORD(x) (((x & 0xFF) << 8)|((x & 0xFF00) >> 8))
#define SWORD(x) ((int16_t)(((x & 0xFF) << 8)|((x & 0xFF00) >> 8)))
#define LONG(x) ( \
     ((x & 0xFF) << 24) \
    |((x & 0xFF00) << 8) \
    |((x & 0xFF0000) >> 8) \
    |((x & 0xFF000000) >> 24) \
)


void disp_obj(OBJECT *p, int i)
{
    OBJECT *x = p + i;
    //printf("Object %d\n", offset);
    //printf("    Type %d (0x%x)\n",
    //    WORD(x->ob_type), WORD(x->ob_type));
    //printf("    Next %d\n", SWORD(x->ob_next));
    //printf("    Head %d\n", SWORD(x->ob_head));
    //printf("    Tail %d\n", SWORD(x->ob_tail));

    printf("tree[%d].ob_type = %d;\n", i, WORD(x->ob_type));
    printf("tree[%d].ob_next = %d;\n", i, SWORD(x->ob_next));
    printf("tree[%d].ob_head = %d;\n", i, SWORD(x->ob_head));
    printf("tree[%d].ob_tail = %d;\n", i, SWORD(x->ob_tail));

    printf("tree[%d].ob_flags = %d;\n", i, WORD(x->ob_flags));
    printf("tree[%d].ob_state = %d;\n", i, WORD(x->ob_state));


    printf("tree[%d].ob_x = 0x%x;\n", i, WORD(x->ob_x));
    printf("tree[%d].ob_y = 0x%x;\n", i, WORD(x->ob_y));
    printf("tree[%d].ob_width = 0x%x;\n", i, WORD(x->ob_width));
    printf("tree[%d].ob_height = 0x%x;\n", i, WORD(x->ob_height));

    switch (WORD(x->ob_type))
    {
        case 28:
        case 32:
            printf("tree[%d].ob_spec = (void *)\"%s\";\n", i, 
                ((char *)p) + LONG(x->ob_spec) - 64);
            break;

        default:
            printf("tree[%d].ob_spec = (void *)0x%08x;\n", i, LONG(x->ob_spec));
    }

    
    //printf("    Size %d+%d, %d+%d\n",
    //    WORD(x->ob_width) & 0xFF,
    //    WORD(x->ob_width) >> 8,
    //    WORD(x->ob_height) & 0xFF,
    //    WORD(x->ob_height) >> 8);

    //int n = WORD(x->ob_head);
    //if (n != 0xFFFF)
    //{
    //    printf("\n    Contents: ");
    //    while (n != 0xFFFF)
    //    {
    //        printf("%d ", n);
    //        n = WORD(p[n].ob_next);
    //        if (n == i)
    //            break;
    //    }
    //    printf("\n");
    //}
    
    printf("\n");
}

int main(int argc, char **argv)
{
    char buf[1024];
    FILE *infile;
    size_t length;
    
    //printf("Size of OBJECT: %lu\n", sizeof(OBJECT));
    
    infile = fopen(argv[1], "r");
    fseek(infile, 0, SEEK_END);
    length = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    
    fread(buf, 1, length, infile);
    
    fclose(infile);

    int max = 15;
    for (int i = 0; i <= max; i++)
    {
        disp_obj((OBJECT *)buf, i);
    }

    return 0;
}
