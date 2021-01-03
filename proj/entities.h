#pragma once

#include<lcom/lcf.h>

#include <stdint.h>

#include "sprite.h"

/** @defgroup entities entities
 * @{
 * Functions for the entities inside the game
*/

/**
 * @brief Represents the ball object
 */
struct ball{
  double real_x_pos; /**< @brief The real position of the ball in the x-axis */
  double real_y_pos; /**< @brief The real position of the ball in the y-axis */
  double x_velocity; /**< @brief The velocity of the ball in the x-axis */
  double y_velocity; /**< @brief The velocity of the ball in the y-axis */
  double velocity_norm; /**< @brief The norm of the velocity */
  int last_player; /**< @brief Variable indicating the last player to hit the ball */
  bool valid_shot; /**< @brief Indicates wether the last shot was valid or not*/
  sprite_t *sp; /**< @brief Sprite of the ball*/
};

typedef struct ball ball_t;

/**
 * @brief Changes the velocity of the ball in order to reach a given point and updates variable    
 *        last_player
 * 
 * @param ball object being updated
 * @param x x-axis position where the ball will go
 * @param y y-axis position where the ball will go
 * @param player the player that hit the ball
 * @return Return 0 upon success and non-zero otherwise
 */
int go_to_selected_point(ball_t * ball, uint16_t x, uint16_t y, int player);

/**
 * @brief Updates the position of the ball
 * 
 * @param ball object being updated
 * @return Return 0 upon success and non-zero otherwise
 */
int change_ball_position(ball_t * ball);

/**
 * @brief Shoots the ball to a random point inside the lower side of the field
 * 
 * @param ball object being shot
 * @return Return 0 upon success and non-zero otherwise
 */
int shoot_ball(ball_t *ball);

/**
 * @brief Represents the player object
 */
struct player{
  int x_velocity; /**< @brief The velocity of the player in the x-axis*/
  int y_velocity; /**< @brief The velocity of the player in th e-axis */
  int points;  /**< @brief The points scored by the player*/
  animated_sprite_t  *asprite; /**< @brief Animated sprite of the player*/
};

typedef struct player player_t;

/**
 * @brief Changes a player velocity
 * 
 * @param player object to be updated
 * @param scancode scancode sent by user
 * @return Return 0 upon success and non-zero otherwise
 */
int change_player_velocity(player_t * player, uint8_t scancode);

/**
 * @brief Changes the velocity of the remote player
 * 
 * @param player object to be updated
 * @param scancode scancode sent by user
 * @return Return 0 upon success and non-zero otherwise
 */
int change_remote_player_velocity(player_t * player, uint8_t scancode);

/**
 * @brief Updates the position of the player
 * 
 * @param player object being updated
 * @return Return 0 upon success and non-zero otherwise
 */
int change_player_position(player_t * player);

/**
 * @brief Changes the side of the player's racket to match the ball
 * 
 * @param ball ball object 
 * @param player player object
 */
void change_racket_side(ball_t * ball, player_t * player);

/**
 * @brief Changes the position of the entities to serivce positions
 * 
 * @param ball ball object
 * @param player1 player object reprsenting player 1
 * @param player2 player object reprsenting player 2
 * @param turn variable indicating who is serving
 */
void service_positions(ball_t * ball, player_t *player1, player_t *player2, bool turn);
/**@}*/
