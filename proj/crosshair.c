#include "crosshair.h"

int read_deviation(crosshair_t * cross, struct packet *pp){
  cross->acum_X += pp->delta_x;
  cross->acum_Y -= pp->delta_y;
  return 0;
}

int change_crosshair_position(crosshair_t *cross){
  cross->sp.x_pos += cross->acum_X;
  cross->sp.y_pos += cross->acum_Y;
  cross->acum_X = 0;
  cross->acum_Y = 0;
  return (keep_sprite_in_bounds(&cross->sp));
}

