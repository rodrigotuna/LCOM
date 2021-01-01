#pragma once

#include <lcom/lcf.h>

/** @defgroup game game
 * @{
 * Functions that implement the different types of games
*/

/**
 * @brief The single player mode
 * 
 * @return Number of points scored
 */
int single_player();

/**
 * @brief The multiplayer mode in the perspective of player 1
 * 
 * @return Result of the game
 */
int multi_player_1();

/**
 * @brief The multiplayer mode in the perspective of player 2
 * 
 * @return Result of the game
 */
int multi_player_2();
/**@}*/
