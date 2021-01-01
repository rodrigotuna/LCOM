#pragma once

#include<lcom/lcf.h>

uint8_t mess[4];
int len;
bool from_player;

/** @defgroup communication communication
 * @{
 * Functions for the communication protocol via serial port
 */

/**
 * @brief Sends a message related to the player
 * 
 * @param scancode the scancode pressed by the user
 * @return Return 0 upon success and non-zero otherwise
 */
int send_player_message(uint8_t scancode);

/**
 * @brief Sends a message related to the ball
 * 
 * @param x_pos the position in the x-axis selected to send the ball to
 * @param y_pos the position in the y-axis selected to send the ball to
 * @return Return 0 upon success and non-zero otherwise
 */
int send_ball_message(uint16_t x_pos, uint16_t y_pos);

/**
 * @brief Handles the byte recieved
 * 
 * @param c the byte recieved
 * @return Retrun 1 if the message is completed, 0 otherwise
 */
int handle_message(uint8_t c);

/**
 * @brief Resets the communication variables
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int reset_communication();
/**@}*/
