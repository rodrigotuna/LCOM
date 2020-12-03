#include "player.h"

int change_player_velocity(player_t * player, uint8_t scancode){
  static bool w_pressed = false;
  static bool s_pressed = false;
  static bool a_pressed = false;
  static bool d_pressed = false;

  if(player == NULL) return 1;

  switch(scancode){
    case W_MAKE_CODE:  if(w_pressed) break;
                       player->asprite->sp.y_velocity-=5; 
                       w_pressed = true;
                       break;
    case W_BREAK_CODE: player->asprite->sp.y_velocity+=5; 
                       w_pressed = false;
                       break;
    case A_MAKE_CODE:  if(a_pressed) break;
                       player->asprite->sp.x_velocity-=5; 
                       a_pressed = true;
                       //player->sp.frame_index = 2;
                       break;
    case A_BREAK_CODE: player->asprite->sp.x_velocity+=5; 
                       a_pressed = false;
                       break;
    case S_MAKE_CODE:  if(s_pressed) break;
                       player->asprite->sp.y_velocity+=5; 
                       s_pressed = true;
                       break;
    case S_BREAK_CODE: player->asprite->sp.y_velocity-=5; 
                       s_pressed = false;
                       break;
    case D_MAKE_CODE:  if(d_pressed) break;
                       player->asprite->sp.x_velocity+=5; 
                       d_pressed = true;
                       //player->sp.frame_index = 0;
                       break;
    case D_BREAK_CODE: player->asprite->sp.x_velocity-=5; 
                       d_pressed = false;
                       break;
    default: return 1;
  }
  return 0;
}

int change_player_position(player_t * player){
  if(player == NULL) return 1;

  player->asprite->sp.x_pos += player->asprite->sp.x_velocity;
  player->asprite->sp.y_pos += player->asprite->sp.y_velocity;

  return (keep_player_in_bounds(player));
}

void set_bounds(player_t* player, int16_t x_low, int16_t x_up, int16_t y_low, int16_t y_up){
  player->x_lower_lim = x_low;
  player->x_upper_lim = x_up;
  player->y_lower_lim = y_low;
  player->y_upper_lim = y_up;
}

int keep_player_in_bounds(player_t * player){
  player->asprite->sp.x_pos = max(player->asprite->sp.x_pos, player->x_lower_lim);
  player->asprite->sp.x_pos = min(player->asprite->sp.x_pos, player->x_upper_lim);
  player->asprite->sp.y_pos = max(player->asprite->sp.y_pos, player->y_lower_lim);
  player->asprite->sp.y_pos = min(player->asprite->sp.y_pos, player->y_upper_lim);
  return 0;
}
