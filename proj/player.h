#pragma once

#include <stdint.h>

#include "i8042.h"

struct player{
  uint32_t x_pos,y_pos;

  int32_t x_velocity, y_velocity;

  uint32_t x_upper_lim, x_lower_lim;
  uint32_t y_upper_lim, y_lower_lim;
};

typedef struct player player_t;

int change_player_velocity(player_t * player, uint8_t scancode);

int keep_player_in_bounds(player_t * player);

int change_player_position(player_t * player);
