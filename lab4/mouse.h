#pragma once

#include <stdint.h>
#include <lcom/lcf.h>

#include "mouse_macros.h"
#include "i8042.h"
#include "kbc.h"

int mouse_hook_id;
uint8_t mouse_packet[3];
uint8_t mouse_count = 0;

int mouse_subscribe_int(uint8_t *bit_no);

int mouse_unsubscribe_int();

int mouse_data_report(bool mode);

struct packet make_packet();

void (mouse_ih)(void);

uint16_t sign_extend(bool sign, uint8_t byte);
