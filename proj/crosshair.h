#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "sprite.h"
#include "mouse.h"

struct crosshair{
  int16_t acum_delta_x;
  int16_t acum_delta_y;
  sprite_t sp;
};

typedef struct crosshair crosshair_t;

int read_deviation(crosshair_t * cross, struct packet *pp);

int change_crosshair_position(crosshair_t * cross);
