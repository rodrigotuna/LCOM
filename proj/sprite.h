#pragma once
#include<lcom/lcf.h>
#include <stdint.h>

/** @defgroup sprites sprites
 * @{
 * Functions for the sprites inside the game
*/

/**
 * @brief Represents a sprite object
 */
struct sprite{
  int16_t x_pos; /**< @brief Sprite x-axis position*/
  int16_t y_pos; /**< @brief Sprite y-axis position*/

  uint16_t width; /**< @brief Sprite width*/
  uint16_t height; /**< @brief Sprite height*/
  uint32_t transparency_color; /**< @brief Sprite transparency color*/

  int16_t x_upper_lim; /**< @brief Sprite x-axis upper limit*/
  int16_t x_lower_lim; /**< @brief Sprite x-axis lower limit*/
  int16_t y_upper_lim; /**< @brief Sprite y-axis upper limit*/
  int16_t y_lower_lim; /**< @brief Sprite y-axis lower limit*/

  uint32_t * current_pic; /**< @brief Sprite map*/
};

typedef struct sprite sprite_t;

/**
 * @brief Represents an animated sprite object
 */
struct animated_sprite{
  sprite_t *sp; /**< @brief Animated sprite sprite*/

  int frame_count; /**< @brief Frame count*/
  int frame_delay; /**< @brief Frame delay*/
  int frame_index; /**< @brief Frame index*/
  int set_index;   /**< @brief Set index*/
  int no_frames;   /**< @brief Number of frames*/
  int no_sets;     /**< @brief Number of sets*/

  uint32_t * *map; /**< @brief Array of maps*/
};

typedef struct animated_sprite animated_sprite_t;

/**
 * @brief Creates a sprite object
 * 
 * @param xpm_map pixmap of the sprite
 * @param x x-axis position of the sprite
 * @param y y-axis position of the sprite
 * @return A pointer to the sprite object created
 */
sprite_t * create_sprite(xpm_map_t xpm_map, int x, int y);

/**
 * @brief Creates an animated sprite object
 * 
 * @param xpm_map array of pixmaps of the sprite's animation
 * @param nsets number of sets of animation to go through
 * @param nframes number of frames in each frame set
 * @param delay delay between frames
 * @param x x-axis position of the sprite
 * @param y y-axis position of the sprite
 * @return A pointer to the sprite object created
 */
animated_sprite_t * create_animated_sprite(xpm_map_t xpm_map[], int nsets, int nframes, int delay, int x, int y);

/**
 * @brief Destroys a sprite object
 * 
 * @param sp sprite object to be destroyed
 */
void destroy_sprite(sprite_t * sp);

/**
 * @brief Destroys an animated sprite object
 * 
 * @param asprite animated sprite object to be destroyed
 */
void destroy_animated_sprite(animated_sprite_t * asprite);

/**
 * @brief Displays a sprite object in it's inherent position
 * 
 * @param sp sprite object to be displayed on screen
 * @return Return 0 upon success and non-zero otherwise
 */
int display_sprite(sprite_t * sp);

/**
 * @brief Changes the sprite position
 * 
 * @param sp sprite object to be updated
 * @param x_dev x-axis deviation of the position
 * @param y_dev y-axis deviation of the position
 * @return Keeps the sprite in it's screen bounds, returns 0 upon success and non-zero otherwise
 */
int change_sprite_pos(sprite_t * sp, int16_t x_dev, int16_t y_dev);

/**
 * @brief Updates the animation of an animated sprite 
 * 
 * @param asprite animated sprite object to be updated
 * @return Return 0 upon success and non-zero otherwise
 */
int update_sprite_animation(animated_sprite_t * asprite);

/**
 * @brief Changes the sprite's screen bounds
 * 
 * @param sp sprite object to be updated
 * @param x_low x-axis lower bound position
 * @param x_up x-axis higher bound position
 * @param y_low y-axis lower bound position
 * @param y_up y-axis higher bound position
 * @return Return 0 upon success and non-zero otherwise
 */
void set_bounds(sprite_t *sp, int16_t x_low, int16_t x_up, int16_t y_low, int16_t y_up);

/**
 * @brief Keeps the sprite position inside it's screen bounds
 * 
 * @param sp sprite object to be updated
 * @return Return 0 upon success and non-zero otherwise
 */
int keep_sprite_in_bounds(sprite_t * sp);

/**
 * @brief Displays any string on screen
 * 
 * @param string c-string to be displayed 
 * @param font font sprite object to be used
 * @param xi x-axis position to display the string
 * @param yi y-axis position to display the string
 * @return Return 0 upon success and non-zero otherwise
 */
int print_string(const char *string, sprite_t * font, int xi, int yi);
/**@}*/
