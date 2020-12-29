#pragma once

#include <stdint.h>

#include "video.h"
#include "i8042.h"


struct sprite{
  int16_t x_pos, y_pos; //x and y positions

  uint16_t width, height;// dimensions
  uint32_t transparency_color; 

  int16_t x_upper_lim, x_lower_lim;
  int16_t y_upper_lim, y_lower_lim;

  uint32_t * current_pic;     // the pixmap
};

typedef struct sprite sprite_t;

struct animated_sprite{

  sprite_t *sp;

  int frame_count; 
  int frame_delay;
  int frame_index;
  int set_index;
  int no_frames;
  int no_sets;

  uint32_t * *map;     // the pixmap
  
};

typedef struct animated_sprite animated_sprite_t;

sprite_t * create_sprite(xpm_map_t xpm_map, int x, int y);

animated_sprite_t * create_animated_sprite(xpm_map_t xpm_map[], int nsets, int nframes, int delay, int x, int y);

void destroy_sprite(sprite_t * sp);

void destroy_animated_sprite(animated_sprite_t * asprite);

int display_sprite(sprite_t * sp);

int change_sprite_pos(sprite_t * sp, int16_t x_dev, int16_t y_dev);

int check_collisions(sprite_t * sp);

int update_sprite_animation(animated_sprite_t * asprite);

void set_bounds(sprite_t *sp, int16_t x_low, int16_t x_up, int16_t y_low, int16_t y_up);

int keep_sprite_in_bounds(sprite_t * sp);

int print_string(const char *string, sprite_t * font, int xi, int yi);
