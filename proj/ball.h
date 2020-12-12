#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "sprite.h"
#include "mouse.h"

struct ball{
  double real_x_pos;
  double real_y_pos;
  double x_velocity;
  double y_velocity;
  sprite_t sp;
};

typedef struct ball ball_t;

int go_to_slected_point(ball_t * ball, )