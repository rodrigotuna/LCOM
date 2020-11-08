#include <lcom/lcf.h>
#include "mouse_macros.h"

typedef enum{ INITIAL, UP, DOWN, END} States;

States state_machine(struct packet *pp);


