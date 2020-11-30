#pragma once

#include <stdint.h>

#include "video.h"
#include "i8042.h"

struct sprite{
  int x_pos, y_pos; //x and y positions

  int x_velocity, y_velocity; //x and y velocities

  int width, height;  // dimensions
  uint32_t * map;     // the pixmap
};

typedef struct sprite sprite_t;

sprite_t * create_sprite(xpm_map_t map, int x, int y, int xv, int yv);

void destroy_sprite(sprite_t * sp);

int display_sprite(sprite_t * sp);

int check_collisions(sprite_t * sp);
