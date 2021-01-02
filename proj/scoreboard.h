#pragma once

#include <lcom/lcf.h>
#include "rtc.h"
#include "sprite.h"

/** @defgroup scoreboard scoreboard
 * @{
 * Functions for the scoreboard
*/

///File path of the scoreboard file
#define SCOREBOARDPATH "/home/lcom/labs/proj/scoreboard.txt"
///Make code of the backspace key
#define BACKSPACE_MAKECODE 0x0E
///Array of the keycodes of all relevant characters 
static char keycodes[51][2] = {"","","1","2","3","4","5","6","7","8","9","0","","","","","Q","W","E","R","T","Y","U","I","O","P","","","","","A","S","D","F","G","H","J","K","L","","","","","","Z","x","C","V","B","N","M"};


/**
 * @brief Checks for a highscore in the scoreboard file
 * 
 * @param points points to be checked in the scoreboard
 * @return Returns the place in the scoreboard upon success and 0 otherwise
 */
int check_highscore(int points);

/**
 * @brief Adds a new score to the scoreboard file
 * 
 * @param name c-string of the name of the player
 * @param points points made by the player
 * @param place place of the player's score in the scoreboard
 * @return Returns 0 upon success and non-zero otherwise
 */
int add_new_score(char * name, int points, int place);

/**
 * @brief Displays the scoreboard on screen
 * 
 * @param font font sprite object to be used
 * @return Returns 0 upon success and non-zero otherwise
 */
int display_scores(sprite_t * font);

/**
 * @brief Changes the string of the name of the player
 * 
 * @param name c-string of the player's input
 * @param scancode scancode sent by user
 * @return Returns the string with the player's input
 */
char * write_name(char * name, uint8_t scancode);
/**@}*/
