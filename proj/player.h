#pragma once

#include <stdint.h>

#include "sprite.h"
#include "i8042.h"

struct player{
  animated_sprite_t * asprite;
};

typedef struct player player_t;

int change_player_velocity(player_t * player, uint8_t scancode);

int change_player_position(player_t * player);
