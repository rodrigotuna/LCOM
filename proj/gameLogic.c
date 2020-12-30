#include "gameLogic.h"


ball_state_t get_ball_state(ball_t * ball){
  if(ball->real_y_pos <= 0) return OUT_OF_BOUNDS_TOP;
  if(ball->real_y_pos >= 600) return OUT_OF_BOUNDS_BOT;
  if(ball->real_x_pos <= 0 || ball->real_x_pos >= 800){
    if(ball->real_y_pos <= 334) return OUT_OF_BOUNDS_TOP;
    else return OUT_OF_BOUNDS_BOT;
  }
  return INSIDE;
}

int shoot_ball(ball_t *ball){
  ball->real_x_pos = 390; ball->real_y_pos = 100;
  ball->velocity_norm += 0.25;
  go_to_selected_point(ball, rand()%461 + 171, rand()%256 + 334);
  return 0;
}

bool can_shoot(ball_t * ball, player_t *player){
   int16_t y_dist = ball->real_y_pos - player->asprite->sp->y_pos;
   int16_t x_dist = ball->real_x_pos - player->asprite->sp->x_pos;

   return (y_dist >= 19 && y_dist <= 69 && x_dist >= -15 && x_dist <= 96);
}

bool update_score(player_t* winner, player_t * loser){
  winner->points++;
  if(winner->points == 4 && loser->points == 4){
    winner->points--;
    loser->points--;
  }
  return (winner->points - loser->points) > 1 && winner->points >= 4;
}

char * multiplayer_score(player_t *player){
  switch(player->points){
    case 0: return "00";
    case 1: return "15";
    case 2: return "30";
    case 3: return "40";
    case 4: return "45";
  }
  return "";
}
