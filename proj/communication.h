#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "uart.h"
#include "utilities.h"
#include "entities.h"

uint8_t mess[4];
int len;
bool from_player;

int send_player_message(uint8_t scancode);

int send_ball_message(uint16_t x_pos, uint16_t y_pos);

int handle_message(uint8_t c);
