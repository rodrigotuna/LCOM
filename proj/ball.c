#include "ball.h"

int go_to_slected_point(ball_t * ball, uint16_t x, uint16_t y){
  double y_dev = y - ball->real_y_pos;
  double x_dev = x - ball->real_x_pos;
  double norm = sqrt(y_dev*y_dev + x_dev*x_dev);
  ball->x_velocity = 10*x_dev/norm;
  ball->y_velocity = 10*y_dev/norm;
  return 0;
}

int change_ball_position(ball_t * ball){
  ball->real_x_pos += ball->x_velocity;
  ball->real_y_pos += ball->y_velocity;
  ball->sp.x_pos = ball->real_x_pos;
  ball->sp.y_pos = ball->real_y_pos;
  return (keep_sprite_in_bounds(&ball->sp));
}
