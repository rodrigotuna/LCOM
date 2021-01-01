#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "entities.h"

typedef enum{INSIDE, OUT_OF_BOUNDS} ball_state_t;

typedef enum{SERVICE, PLAYING, WIN, LOSE} game_state_t;

typedef enum{PLAYER1, PLAYER2} won_service_t;

ball_state_t get_ball_state(ball_t *ball);

won_service_t get_winner_of_set(ball_t *ball);

bool valid_shot(uint16_t x_pos, uint16_t y_pos, int player);

bool can_shoot(ball_t *ball, player_t *player);

bool update_score(player_t *winner, player_t *loser);

char * multiplayer_score(player_t *player);

