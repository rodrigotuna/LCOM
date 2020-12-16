#include "gameLogic.h"


int is_ball_out_of_bounds(ball_t * ball){
  if(ball->real_y_pos <= 0) return 1;
  if(ball->real_y_pos >= 600) return 2;
  if(ball->real_x_pos <= 0 || ball->real_x_pos >= 800){
    if(ball->real_y_pos <= 300) return 1;
    return 2;
  }
  return 0;
}

int shoot_ball(ball_t *ball){
  ball->real_x_pos = 390; ball->real_y_pos = 100;
  go_to_selected_point(ball, rand()%500 + 150, rand()%200 + 400);
  return 0;
}

bool can_shoot(ball_t * ball, player_t *player){
   int16_t y_dist = ball->real_y_pos - player->asprite.sp.y_pos;
   int16_t x_dist = ball->real_x_pos - player->asprite.sp.x_pos;

   printf("%d %d", y_dist, x_dist);
   return (y_dist >= 19 && y_dist <= 69 && x_dist >= -15 && x_dist <= 96);
}
