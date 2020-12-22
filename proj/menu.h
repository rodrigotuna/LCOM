#pragma once

#include <lcom/lcf.h>

#include "drivers.h"
#include "game.h"

typedef enum {NO_MODE, SINGLEPLAYER, MULTIPLAYER, SCORES, QUIT} menu_state_t;

int main_menu();

menu_state_t check_button_bounds(sprite_t * cursor, animated_sprite_t * menu, menu_state_t button);

