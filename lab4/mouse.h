#pragma once

#include <stdint.h>
#include <lcom/lcf.h>

#include "mouse_macros.h"
//#include "i8042.h"
#include "kbc.h"

int mouse_hook_id;
uint8_t mouse_packet[3];
uint8_t mouse_count;

int mouse_subscribe_int(uint8_t *bit_no);

int mouse_unsubscribe_int();

struct packet make_packet();

void (mouse_ih)(void);

int mouse_read(uint8_t *data);

void mouse_poll();

int mouse_poll_byte(uint8_t *data);

int mouse_set_arg(uint8_t arg);
