#include "gameLogic.h"


ball_state_t get_ball_state(ball_t * ball){
  if(ball->real_y_pos <= 0 || ball-> real_y_pos >= 600) return OUT_OF_BOUNDS;
  if(ball->real_x_pos <= 0 || ball->real_x_pos >= 800) return OUT_OF_BOUNDS;
  return INSIDE;
}

won_service_t get_winner_of_set(ball_t *ball){
  switch(ball->last_player){
    case 1: if(ball->valid_shot){
              return PLAYER1;
            } else{
              return PLAYER2;
            }
            break;
    case 2: if(ball->valid_shot){
              return PLAYER2;
            } else{
              return PLAYER1;
            }
  }
  return PLAYER1;
}

int shoot_ball(ball_t *ball){
  ball->real_x_pos = 390; ball->real_y_pos = 100;
  ball->velocity_norm += 0.25;
  go_to_selected_point(ball, rand()%461 + 171, rand()%256 + 334, 2);
  return 0;
}

bool valid_shot(uint16_t x_pos, uint16_t y_pos, int player){
  if(player == 1){
    return x_pos >= 171 && x_pos <= 632 && y_pos >= 76 && y_pos <= 334;
  } else{
    return x_pos >= 171 && x_pos <= 632 && y_pos >= 334 && y_pos <= 590;
  }
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
