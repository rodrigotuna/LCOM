#pragma once

#include <lcom/lcf.h>

#include "drivers.h"
#include "game.h"
#include "scoreboard.h"

typedef enum{SMALL, BIG} button_sizes_t;
typedef enum {NO_MODE, SINGLEPLAYER, MULTIPLAYER, SCORES, QUIT, PLAYAGAIN, HOME, DONE, CREATE, JOIN} button_state_t;

int main_menu();

int entername_menu(int place, int points);

int gameover_menu(int points);

int choose_player_menu();

int connect_player1_menu();

int connect_player2_menu();

int scoreboard_menu();

button_state_t main_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t button);

button_state_t name_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

button_state_t gameover_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

button_state_t chooseplayer_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

button_state_t scoreboard_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

bool check_button_bounds(int16_t cursor_x, int16_t cursor_y, int xi,int yi, button_sizes_t size);
