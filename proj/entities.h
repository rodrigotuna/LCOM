#pragma once

#include<lcom/lcf.h>

#include <stdint.h>
#include "math.h"

#include "sprite.h"
#include "mouse.h"
#include "i8042.h"

struct ball{
  double real_x_pos;
  double real_y_pos;
  double x_velocity;
  double y_velocity;
  double velocity_norm;
  sprite_t *sp;
};

typedef struct ball ball_t;

int go_to_selected_point(ball_t * ball, uint16_t x, uint16_t y);

int change_ball_position(ball_t * ball);

struct player{
  int x_velocity, y_velocity; //x and y velocities
  int points;
  animated_sprite_t  *asprite;
};

typedef struct player player_t;

int change_player_velocity(player_t * player, uint8_t scancode);

int change_remote_player_velocity(player_t * player, uint8_t scancode);

int change_player_position(player_t * player);

void change_racket_side(ball_t * ball, player_t * player);
