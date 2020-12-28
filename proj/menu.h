#pragma once

#include <lcom/lcf.h>

#include "drivers.h"
#include "game.h"

typedef enum{SMALL, MEDIUM, BIG} button_sizes_t;
typedef enum {NO_MODE, SINGLEPLAYER, MULTIPLAYER, SCORES, QUIT} menu_state_t;

int main_menu();

menu_state_t main_menu_mode(sprite_t * cursor, animated_sprite_t * menu, menu_state_t button);

bool check_button_bounds(int16_t cursor_x, int16_t cursor_y, int xi,int yi, button_sizes_t size);

int connect_player1_menu();

int connect_player2_menu();
