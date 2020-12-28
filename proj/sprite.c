#include "sprite.h"
#include "utilities.h"

sprite_t * create_sprite(xpm_map_t xpm_map, int x, int y){
  sprite_t *sp = (sprite_t*) malloc ( sizeof(sprite_t));

  if(sp == NULL) return NULL;

  xpm_image_t img;

  sp->current_pic = (uint32_t *) xpm_load(xpm_map, XPM_8_8_8_8, &img);

  if( sp->current_pic == NULL ){
      destroy_sprite(sp);
      return NULL;
  }

  sp->transparency_color = xpm_transparency_color(img.type);

  sp->width = img.width; 
  sp->height = img.height;

  sp->x_pos = x;
  sp->y_pos = y;

  return sp;
}

animated_sprite_t * create_animated_sprite(xpm_map_t xpm_map[], int nsets, int nframes, int delay, int x, int y){
  animated_sprite_t *asprite = (animated_sprite_t*) malloc (sizeof(animated_sprite_t));
  
  if(asprite == NULL) return NULL;

  asprite->sp = *create_sprite(xpm_map[0],x,y);
  
  asprite->map = malloc((nsets * nframes)*sizeof(map));

  asprite->map[0] = asprite->sp.current_pic;

  for(int i = 1; i < (nsets * nframes); i++){
    xpm_image_t img;
    asprite->map[i] = (uint32_t *) xpm_load(xpm_map[i],XPM_8_8_8_8, &img);
    if( asprite->map[i] == NULL ){
      destroy_animated_sprite(asprite);
      return NULL;
    }
  }

  asprite->frame_count = 0;
  asprite->frame_delay = delay;
  asprite->frame_index = 0; 
  asprite->set_index = 0;
  asprite->no_frames = nframes;
  asprite->no_sets = nsets;

  return asprite;
}

void destroy_sprite(sprite_t * sp){
  if( sp == NULL )return;
  if( sp->current_pic ) free(sp->current_pic); 
  free(sp);
  sp = NULL;
}

void destroy_animated_sprite(animated_sprite_t * asprite){
  if(asprite == NULL) return;
  if(asprite->map){
    for(int i = 0; i< (asprite->no_sets * asprite->no_frames);i++){
      free(asprite->map[i]);
    }
    free(asprite->map); 
  }
  destroy_sprite(&asprite->sp);
  free(asprite);
  asprite = NULL;
}

int display_sprite(sprite_t * sp){
  for(int i = 0; i < sp->height; i++){
    for(int j = 0; j < sp->width; j++){
      uint32_t color = sp->current_pic[i* sp->width + j];
      if(color != sp->transparency_color){
        if(set_pixel(sp->x_pos+j,sp->y_pos+i,color)) return 1;
      }     
    }
  }
  return 0;
}

int change_sprite_pos(sprite_t * sp, int16_t x_dev, int16_t y_dev){
  sp->x_pos += x_dev;
  sp->y_pos += y_dev;
  return 0;
}

int check_collisions(sprite_t * sp){
  return 0;
}

int update_sprite_animation(animated_sprite_t * asprite){
  asprite->frame_count ++;
  if(asprite->frame_count >= asprite->frame_delay){
    asprite->frame_count = 0;
    asprite->frame_index = ((asprite->frame_index + 1) % asprite->no_frames) + (asprite->no_frames * asprite->set_index);
    asprite->sp.current_pic = asprite->map[asprite->frame_index];
  }
  return 0;
}

void set_bounds(sprite_t *sp, int16_t x_low, int16_t x_up, int16_t y_low, int16_t y_up){
  sp->x_lower_lim = x_low;
  sp->x_upper_lim = x_up;
  sp->y_lower_lim = y_low;
  sp->y_upper_lim = y_up;
}

int keep_sprite_in_bounds(sprite_t * sp){
  sp->x_pos = max(sp->x_pos, sp->x_lower_lim);
  sp->x_pos = min(sp->x_pos, sp->x_upper_lim);
  sp->y_pos = max(sp->y_pos, sp->y_lower_lim);
  sp->y_pos = min(sp->y_pos, sp->y_upper_lim);
  return 0;
}

int print_string(const char *string, sprite_t * font){
  int width = 16, height = 20;
  int x, y, pos_x, pos_y, font_aux = font->x_pos;

  for (int i = 0; string[i] != '\0'; i++){
    int code = string[i];
    if(code >= 48 && code <= 57){
      x = code % 48;
      y = 0;
    }
    else if(code >= 65 && code <= 74){
      x = code % 65;
      y = 1;
    }
    else if(code >= 75 && code <= 84){
      x = code % 75;
      y = 2;
    }
    else if(code >= 85 && code <= 90){
      x = code % 85;
      y = 3;
    }
    else{
      y = 4;
      if(code == 45) x = 0;
      if(code == 58) x = 1;
      if(code == 32) x = 2;
    }
    
    pos_y = 0;
    for(int i = y * height; i < (y + 1) * height; i++){
      pos_x = 0;
      for(int j = x * width; j < (x + 1) * width; j++){
        uint32_t color = font->current_pic[i * font->width + j];
        if(color != font->transparency_color){
          if(set_pixel(font->x_pos+pos_x,font->y_pos+pos_y,color)) return 1;
        }
        pos_x++;     
      }
      pos_y++;
    }
    font->x_pos += width;
  }
  font->x_pos = font_aux;
  return 0;
}
