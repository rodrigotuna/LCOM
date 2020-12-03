#pragma once

#include <stdint.h>

#include "sprite.h"
#include "i8042.h"

struct player{
  int16_t x_upper_lim, x_lower_lim;
  int16_t y_upper_lim, y_lower_lim;

  animated_sprite_t * asprite;
};

typedef struct player player_t;

int change_player_velocity(player_t * player, uint8_t scancode);

int keep_player_in_bounds(player_t * player);

void set_bounds(player_t* player, int16_t x_low, int16_t x_up, int16_t y_low, int16_t y_up);

int change_player_position(player_t * player);
