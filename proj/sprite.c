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
    free(sp->map);
    free(sp);
    sp = NULL;
  }
}

int display_sprite(sprite_t * sp, uint16_t x, uint16_t y){
  for(int i = 0; i < sp->height; i++){
    for(int j = 0; j < sp->width; j++){
        if(set_pixel(x+j,y+i,sp->map[i*sp->width + j])) return 1;     
    }
  }
  return 0;
}

int check_collisions(sprite_t * sp){
  return 0;
}
