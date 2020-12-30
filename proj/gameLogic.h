#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "entities.h"

typedef enum{INSIDE, OUT_OF_BOUNDS_TOP, OUT_OF_BOUNDS_BOT} ball_state_t;

typedef enum{SERVICE, PLAYING, WIN, LOSE} game_state_t;

ball_state_t get_ball_state(ball_t *ball);

int shoot_ball(ball_t *ball);

bool can_shoot(ball_t *ball, player_t *player);

bool update_score(player_t *winner, player_t *loser);

char * multiplayer_score(player_t *player);
