#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "entities.h"

/** @defgroup gameLogic gameLogic
 * @{
 * Functions that implement the rules of the games
*/

/**
 * @brief Represents the different states of the ball
 */
typedef enum{INSIDE, OUT_OF_BOUNDS} ball_state_t;

/**
 * @brief Represents the different states of the game
 */
typedef enum{SERVICE, PLAYING, WIN, LOSE} game_state_t;

/**
 * @brief Represents the possible outcomes of a service
 */
typedef enum{PLAYER1, PLAYER2} won_service_t;

/**
 * @brief Gets the state of the ball
 * 
 * @param ball ball object
 * @return The state of the ball
 */
ball_state_t get_ball_state(ball_t *ball);

/**
 * @brief Gets the winner of the service
 * 
 * @param ball ball object with information about legal moves and las player to hit the ball
 * @return The winner of the service
 */
won_service_t get_winner_of_set(ball_t *ball);

/**
 * @brief Determines wether a shot was valid or not
 * 
 * @param x_pos x-axis position of the shot
 * @param y_pos y-axis position of the shot
 * @param player integer indicating which playr made the shot
 * @return True if the shot was valid, False otherwise
 */
bool valid_shot(uint16_t x_pos, uint16_t y_pos, int player);

/**
 * @brief Determines if the ball is close enough to the player to make the shot
 * 
 * @param ball ball object
 * @param player player object
 * @return True if the player can shoot, false otherwise
 */
bool can_shoot(ball_t *ball, player_t *player);

/**
 * @brief Updates the score of the multiplayer game
 * 
 * @param winner player object of the winner of the service
 * @param loser player object of the loser of the service
 * @return True if the game is over, false otherwise
 */
bool update_score(player_t *winner, player_t *loser);

/**
 * @brief Transforms the score of the player to the respective string
 * 
 * @param player player object whose score will be transformed
 * @return String with the score transformed
 */
char * multiplayer_score(player_t *player);
/**@}*/
