#include "sprite.h"

sprite_t * create_sprite(xpm_map_t xpm_map, int x, int y, int xv, int yv){
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

  sp->x_velocity = xv;
  sp->y_velocity = yv;

  return sp;
}

animated_sprite_t * create_animated_sprite(xpm_map_t xpm_map[], int npics, int nframes, int delay, int x, int y, int xv, int yv ){
  animated_sprite_t *asprite = (animated_sprite_t*) malloc (sizeof(animated_sprite_t));
  
  if(asprite == NULL) return NULL;

  asprite->sp = *create_sprite(xpm_map[0],x,y,xv,yv);
  
  asprite->map = malloc((npics)*sizeof(map));

  asprite->map[0] = asprite->sp.current_pic;

  for(int i = 1; i < npics; i++){
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
  asprite->no_frames = nframes;
  asprite->no_pics = npics;

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
    for(int i = 0; i< asprite->no_pics;i++){
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

int check_collisions(sprite_t * sp){
  return 0;
}

int erase_sprite(sprite_t  * background, sprite_t * sp){
  for(int i = 0; i < sp->height; i++){
    for(int j = 0; j < sp->width; j++){
      uint32_t color = background->current_pic[(sp->y_pos + i) * background->width + j + sp->x_pos];
      if(set_pixel(sp->x_pos+j,sp->y_pos+i,color)) return 1;
      }     
    }
  return 0;
}

int update_sprite_animation(animated_sprite_t * asprite){
  asprite->frame_count ++;
  if(asprite->frame_count >= asprite->frame_delay){
    asprite->frame_count = 0;
    asprite->frame_index = (asprite->frame_index + 1) % asprite->no_frames;
    asprite->sp.current_pic = asprite->map[asprite->frame_index];
  }
  return 0;
}
