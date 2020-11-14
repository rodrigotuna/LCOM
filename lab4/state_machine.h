#include <lcom/lcf.h>
#include "mouse_macros.h"

typedef enum{ INITIAL, UP, VERTIX, DOWN, END} States;

States state_machine(struct mouse_ev *ev, uint8_t x_len, uint8_t tolerance);

struct mouse_ev* mouse_detect_ev( struct packet * pp);
