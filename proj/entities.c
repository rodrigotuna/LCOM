#include "entities.h"

//Ball Functions

int go_to_selected_point(ball_t * ball, uint16_t x, uint16_t y){
  if(ball == NULL) return 1;

  double y_dev = y - ball->real_y_pos;
  double x_dev = x - ball->real_x_pos;
  double norm = sqrt(y_dev*y_dev + x_dev*x_dev);
  ball->x_velocity = ball->velocity_norm*x_dev/norm;
  ball->y_velocity = ball->velocity_norm*y_dev/norm;
  return 0;
}

int change_ball_position(ball_t * ball){
  if(ball == NULL) return 1;

  ball->real_x_pos += ball->x_velocity;
  ball->real_y_pos += ball->y_velocity;
  ball->sp->x_pos = ball->real_x_pos;
  ball->sp->y_pos = ball->real_y_pos;
  return (keep_sprite_in_bounds(ball->sp));
}

//Player Functions

int change_player_velocity(player_t * player, uint8_t scancode){
  static bool w_pressed = false;
  static bool s_pressed = false;
  static bool a_pressed = false;
  static bool d_pressed = false;

  if(player == NULL) return 1;

  //Reset values
  if(scancode == 0){
    w_pressed = false;
    s_pressed = false;
    a_pressed = false;
    d_pressed = false;
  } 

  switch(scancode){
    case W_MAKE_CODE:  if(w_pressed) break;
                       player->y_velocity-=5; 
                       w_pressed = true;
                       break;
    case W_BREAK_CODE: player->y_velocity+=5; 
                       w_pressed = false;
                       break;
    case A_MAKE_CODE:  if(a_pressed) break;
                       player->x_velocity-=5; 
                       a_pressed = true;
                       break;
    case A_BREAK_CODE: player->x_velocity+=5; 
                       a_pressed = false;
                       break;
    case S_MAKE_CODE:  if(s_pressed) break;
                       player->y_velocity+=5; 
                       s_pressed = true;
                       break;
    case S_BREAK_CODE: player->y_velocity-=5; 
                       s_pressed = false;
                       break;
    case D_MAKE_CODE:  if(d_pressed) break;
                       player->x_velocity+=5; 
                       d_pressed = true;
                       break;
    case D_BREAK_CODE: player->x_velocity-=5; 
                       d_pressed = false;
                       break;
    default: return 1;
  }
  return 0;
}

int change_remote_player_velocity(player_t * player, uint8_t scancode){
  static bool w_pressed = false;
  static bool s_pressed = false;
  static bool a_pressed = false;
  static bool d_pressed = false;

  if(player == NULL) return 1;

  //Reset values
  if(scancode == 0){
    w_pressed = false;
    s_pressed = false;
    a_pressed = false;
    d_pressed = false;
  } 

  switch(scancode){
    case W_MAKE_CODE:  if(w_pressed) break;
                       player->y_velocity-=5; 
                       w_pressed = true;
                       break;
    case W_BREAK_CODE: player->y_velocity+=5; 
                       w_pressed = false;
                       break;
    case A_MAKE_CODE:  if(a_pressed) break;
                       player->x_velocity-=5; 
                       a_pressed = true;
                       break;
    case A_BREAK_CODE: player->x_velocity+=5; 
                       a_pressed = false;
                       break;
    case S_MAKE_CODE:  if(s_pressed) break;
                       player->y_velocity+=5; 
                       s_pressed = true;
                       break;
    case S_BREAK_CODE: player->y_velocity-=5; 
                       s_pressed = false;
                       break;
    case D_MAKE_CODE:  if(d_pressed) break;
                       player->x_velocity+=5; 
                       d_pressed = true;
                       break;
    case D_BREAK_CODE: player->x_velocity-=5; 
                       d_pressed = false;
                       break;
    default: return 1;
  }
  return 0;
}

int change_player_position(player_t * player){
  if(player == NULL) return 1;

  player->asprite->sp->x_pos += player->x_velocity;
  player->asprite->sp->y_pos += player->y_velocity;

  return (keep_sprite_in_bounds(player->asprite->sp));
}

void change_racket_side(ball_t * ball, player_t * player){
  int last_set = player->asprite->set_index;

  if(ball->sp->x_pos >= (player->asprite->sp->x_pos + 45)) player->asprite->set_index = 0;
  else player->asprite->set_index = 1;

  player->asprite->frame_count = (player->asprite->set_index != last_set) ?                  
                                  player->asprite->frame_delay : player->asprite->frame_count;
}
