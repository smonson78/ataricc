#ifndef __AES_OBJECT_H
#define __AES_OBJECT_H

typedef struct
{
    int16_t ob_next;   /* The next object               */
    int16_t ob_head;   /* First child                   */
    int16_t ob_tail;   /* Last child                    */
    uint16_t ob_type;  /* Object type                   */
    uint16_t ob_flags; /* Manipulation flags            */
    uint16_t ob_state; /* Object status                 */
    void *ob_spec;     /* More under object type        */
    int16_t ob_x;      /* X-coordinate of the object    */
    int16_t ob_y;      /* Y-coordinate of the object    */
    int16_t ob_width;  /* Width of the object           */
    int16_t ob_height; /* Height of the object          */
} OBJECT;

typedef enum {
    MENU_HIDE = 0,
    MENU_SHOW
} Menu_Operation;

#endif
