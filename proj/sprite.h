#pragma once

#include <stdint.h>

#include "video.h"
#include "i8042.h"


struct sprite{
  int16_t x_pos, y_pos; //x and y positions

  int x_velocity, y_velocity; //x and y velocities

  uint16_t width, height;// dimensions
  uint32_t transparency_color; 

  int16_t x_upper_lim, x_lower_lim;
  int16_t y_upper_lim, y_lower_lim;

  uint32_t * current_pic;     // the pixmap
};

typedef struct sprite sprite_t;

struct animated_sprite{

  sprite_t sp;

  int frame_count; 
  int frame_delay;
  int frame_index; //index of the frame to be shown in the image
  int no_pics;
  int no_frames;

  uint32_t * *map;     // the pixmap
  
};

typedef struct animated_sprite animated_sprite_t;

sprite_t * create_sprite(xpm_map_t xpm_map, int x, int y, int xv, int yv);

animated_sprite_t * create_animated_sprite(xpm_map_t xpm_map[], int npics, int nframes, int delay, int x, int y, int xv, int yv );

void destroy_sprite(sprite_t * sp);

void destroy_animated_sprite(animated_sprite_t * asprite);

int display_sprite(sprite_t * sp);

int check_collisions(sprite_t * sp);

int erase_sprite(sprite_t  * background, sprite_t * sp);

int update_sprite_animation(animated_sprite_t * asprite);

void set_bounds(sprite_t *sp, int16_t x_low, int16_t x_up, int16_t y_low, int16_t y_up);

int keep_sprite_in_bounds(sprite_t * sp);
