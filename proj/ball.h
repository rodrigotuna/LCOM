#pragma once

#include<lcom/lcf.h>

#include <stdint.h>
#include "math.h"

#include "sprite.h"
#include "mouse.h"
#include "crosshair.h"

struct ball{
  double real_x_pos;
  double real_y_pos;
  double x_velocity;
  double y_velocity;
  sprite_t sp;
};

typedef struct ball ball_t;

int go_to_selected_point(ball_t * ball, uint16_t x, uint16_t y);

int change_ball_position(ball_t * ball);
