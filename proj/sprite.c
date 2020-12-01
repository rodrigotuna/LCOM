#include "sprite.h"

sprite_t * create_sprite(xpm_map_t xpm_map, int x, int y, int xv, int yv){
  sprite_t *sp = (sprite_t*) malloc ( sizeof(sprite_t));

  xpm_image_t img;
  if(sp == NULL) return NULL;

  sp->map = (uint32_t *) xpm_load(xpm_map, XPM_8_8_8_8, &img);

  if( sp->map == NULL ){
    free(sp);
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

void destroy_sprite(sprite_t * sp){
  if( sp == NULL )return;
  if( sp->map ){
    //free(sp->map);
    free(sp);
    sp = NULL;
  }
}

int display_sprite(sprite_t * sp){
  for(int i = 0; i < sp->height; i++){
    for(int j = 0; j < sp->width; j++){
      uint32_t color = sp->map[i*sp->width + j];
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
      uint32_t color = background->map[(sp->y_pos + i)*background->width + j + sp->x_pos];
      if(set_pixel(sp->x_pos+j,sp->y_pos+i,color)) return 1;
      }     
    }
  return 0;
}
