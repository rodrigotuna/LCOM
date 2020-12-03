#include "crosshair.h"

int read_deviation(crosshair_t * cross, struct packet *pp){
  cross->acum_delta_x+= pp->delta_x;
  cross->acum_delta_y -= pp->delta_y;
  return 0;
}

int change_crosshair_position(crosshair_t * cross){
  cross->sp.x_pos += cross->acum_delta_x;
  cross->sp.y_pos += cross->acum_delta_y;
  cross->acum_delta_x = 0;
  cross->acum_delta_y = 0;
  return 0;
}
