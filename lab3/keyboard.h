#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <minix/sysutil.h>

#include <stdint.h>
#include <stdbool.h>

#include "i8042.h"
#include "kbc.h"

int hook_id;
uint8_t scancode[2];
uint8_t size;
bool code_completed;

int(kb_subscribe_int)(uint8_t *bit_no);

int(kb_unsubscribe_int)();

void (kbc_ih)(void);

int kb_poll();
