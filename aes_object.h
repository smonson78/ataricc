#ifndef __AES_OBJECT_H
#define __AES_OBJECT_H

#include <stdint.h>

typedef struct
{
    int16_t ob_next;    /* The next object               */
    int16_t ob_head;    /* First child                   */
    int16_t ob_tail;    /* Last child                    */
    uint16_t ob_type;   /* Object type                   */
    uint16_t ob_flags;  /* Manipulation flags            */
    uint16_t ob_state;  /* Object status                 */
    void *ob_spec;      /* More under object type        */
    uint16_t ob_x;      /* X-coordinate of the object    */
    uint16_t ob_y;      /* Y-coordinate of the object    */
    uint16_t ob_width;  /* Width of the object           */
    uint16_t ob_height; /* Height of the object          */
} OBJECT;

typedef enum {
    MENU_HIDE = 0,
    MENU_SHOW
} Menu_Operation;

#endif

/*
    64 byte header
    0 next -1 head 1 tail 5 type 25 (IBOX) flags 0 state 0 spec 0 pos 0,0 80x25
    1 next 5 head 2 tail 2 type 20 (GBOX) flags 0 state 0 spec 0x1100 pos 0,0 80x0x201
    2 next 1 head 3 tail 4 type 25 (IBOX) flags 0 state 0 spec 0 pos 2,0 15x0x301
    3 next 4 head -1 tail -1 type 32 (GTITLE) flags 0 state 0 spec 0x1d8 pos 0,0 9x0x301
    4 next 2 head -1 tail -1 type 32 ... pos 9,0 6x0x301
    5 next 0 head 6 tail 15 type 25 (IBOX) flags 0 state 0 spec 0 pos 0,0x301 23x8
    6 next 15 head 7 tail 14 type 20 (GBOX) flags 0 state 0 spec 0x00ff1100 pos 2,0 25x8
    7 next 8 head -1 tail -1 type 28 (GSTRING) flags 0 state 0 spec 0x1e7 pos 0,0 21,1
    8 next 9 head -1 tail -1 type 28 (GSTRING) flags 0 state 8 spec 0x1f6 pos 0,1 21,1
    
    0 IBOX (root)
    1 GBOX (the bar)               5 IBOX (the screen)
    2 IBOX (the active)            6        15 GBOX
    3 4 TITLE (Program, File)      7 8 9
    
    
*/
