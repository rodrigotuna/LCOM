#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "ball.h"
#include "player.h"

int is_ball_out_of_bounds(ball_t * ball);

int shoot_ball(ball_t *ball);

bool can_shoot(ball_t * ball, player_t *player);
