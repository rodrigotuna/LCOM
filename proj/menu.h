#pragma once

#include <lcom/lcf.h>

#include "sprite.h"

/** @defgroup menu menu
 * @{
 * Functions that implement the different menus throughout the game
*/

/**
 * @brief Represents the different sizes of the buttons
 */
typedef enum{SMALL, BIG} button_sizes_t;

/**
 * @brief Represents the different modes of the game
 */
typedef enum {NO_MODE, SINGLEPLAYER, MULTIPLAYER, SCORES, QUIT, PLAYAGAIN, HOME, DONE, CREATE, JOIN} button_state_t;

/**
 * @brief The main menu
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int main_menu();

/**
 * @brief The menu for entering the player's name upon a new highscore 
 * 
 * @param place place that the player finished the game
 * @param points points made by the player
 * @return Return 0 upon success and non-zero otherwise
 */
int entername_menu(int place, int points);

/**
 * @brief The gameover menu 
 * 
 * @param points points made by the player
 * @param type type of the gameover menu (Won or Lost, or gameover for singleplayer)
 * @return Return 0 if the next mode is PLAYAGAIN or 1 otherwise
 */
int gameover_menu(int points, int type);

/**
 * @brief The menu for choosing the player in multiplayer mode 
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int choose_player_menu();

/**
 * @brief The connecting menu for player 1 
 * 
 * @return True if the other player is connected, false otherwise
 */
int connect_player1_menu();

/**
 * @brief The connecting menu for player 1 
 * 
 * @return True if the other player is connected, false otherwise
 */
int connect_player2_menu();

/**
 * @brief The scoreboard menu
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int scoreboard_menu();


/**
 * @brief Checks which main menu mode is selected
 * 
 * @param cursor cursor's sprite object
 * @param menu menu's animated sprite object
 * @param button the menu mode to be updated
 * @return The main menu mode selected
 */
button_state_t main_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t button);

/**
 * @brief Checks which enter name menu mode is selected
 * 
 * @param cursor cursor's sprite object
 * @param menu menu's animated sprite object
 * @param button the menu mode to be updated
 * @return The enter name menu mode selected
 */
button_state_t name_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

/**
 * @brief Checks which gameover menu mode is selected
 * 
 * @param cursor cursor's sprite object
 * @param menu menu's animated sprite object
 * @param button the menu mode to be updated
 * @return The gameover menu mode selected
 */
button_state_t gameover_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

/**
 * @brief Checks which choose player menu mode is selected
 * 
 * @param cursor cursor's sprite object
 * @param menu menu's animated sprite object
 * @param button the menu mode to be updated
 * @return The choose player menu mode selected
 */
button_state_t chooseplayer_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

/**
 * @brief Checks which scoreboard menu mode is selected
 *
 * @param cursor cursor's sprite object
 * @param menu menu's animated sprite object
 * @param button the menu mode to be updated
 * @return The scoreboard menu mode selected
 */
button_state_t scoreboard_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode);

/**
 * @brief Checks if the cursor is inside the button bounds
 * 
 * @param cursor_x cursor x-axis position
 * @param cursor_y cursor y-axis position
 * @param xi x-axis position of the first pixel of the button 
 * @param yi y-axis position of the first pixel of the button 
 * @param size button size
 * @return True if the cursor is in bounds, false otherwise
 */
bool check_button_bounds(int16_t cursor_x, int16_t cursor_y, int xi,int yi, button_sizes_t size);
/**@}*/
