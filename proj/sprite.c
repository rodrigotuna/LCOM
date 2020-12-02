#include "sprite.h"

sprite_t * create_sprite(xpm_map_t xpm_map[], int nframes, int aspeed, int x, int y, int xv, int yv){
  sprite_t *sp = (sprite_t*) malloc ( sizeof(sprite_t));

  if(sp == NULL) return NULL;

  sp->no_frames = nframes;
  sp->frame_count = 0;
  sp->frame_delay = aspeed;

  sp->map = malloc((nframes)*sizeof(map));

  xpm_image_t img;

  for(int i = 0; i < sp->no_frames; i++){
    xpm_image_t img_aux;
    sp->map[i] = (uint32_t *) xpm_load(xpm_map[i], XPM_8_8_8_8, &img_aux);
    if( sp->map[i] == NULL ){
      destroy_sprite(sp);
      return NULL;
    }
    img = img_aux;
  }

  sp->transparency_color = xpm_transparency_color(img.type);

  sp->width = img.width; 
  sp->height = img.height;

  sp->x_pos = x;
  sp->y_pos = y;

  sp->x_velocity = xv;
  sp->y_velocity = yv;

  return sp;
}

void destroy_sprite(sprite_t * sp){
  if( sp == NULL )return;
  if( sp->map ){
    for(int i = 1; i< sp->no_frames;i++){
      free(sp->map[i]);
    }
    free(sp->map); 
    free(sp);
    sp = NULL;
  }
}

int display_sprite(sprite_t * sp){
  for(int i = 0; i < sp->height; i++){
    for(int j = 0; j < sp->width; j++){
      uint32_t color = sp->map[(sp->frame_index)][i*sp->width + j];
      if(color != sp->transparency_color){
        if(set_pixel(sp->x_pos+j,sp->y_pos+i,color)) return 1;
      }     
    }
  }
  return 0;
}

int check_collisions(sprite_t * sp){
  return 0;
}

int erase_sprite(sprite_t  * background, sprite_t * sp){
  for(int i = 0; i < sp->height; i++){
    for(int j = 0; j < sp->width; j++){
      uint32_t color = background->map[(sp->frame_index)][(sp->y_pos + i) * background->width + j + sp->x_pos];
      if(set_pixel(sp->x_pos+j,sp->y_pos+i,color)) return 1;
      }     
    }
  return 0;
}

int update_sprite_animation(sprite_t * sp){
  sp->frame_count ++;
  if(sp->frame_count >= sp->frame_delay){
    sp->frame_count = 0;
    sp->frame_index ++;
    sp->frame_index %= sp->no_frames; 
  }
  return 0;
}
