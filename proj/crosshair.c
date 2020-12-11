#include "crosshair.h"

int change_crosshair_position(crosshair_t * cross, struct packet *pp){
  cross->sp.x_pos += pp->delta_x;
  cross->sp.y_pos -= pp->delta_y;
  return keep_sprite_in_bounds(&cross->sp);
}
