#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "sprite.h"
#include "mouse.h"

struct crosshair{
  sprite_t sp;
};

typedef struct crosshair crosshair_t;

int change_crosshair_position(crosshair_t * cross, struct packet *pp);
