#include "player.h"

int change_player_velocity(player_t * player, uint8_t scancode){
  static bool w_pressed = false;
  static bool s_pressed = false;
  static bool a_pressed = false;
  static bool d_pressed = false;

  if(player == NULL) return 1;

  switch(scancode){
    case W_MAKE_CODE:  if(w_pressed) break;
                       player->asprite->sp.y_velocity-=10; 
                       w_pressed = true;
                       break;
    case W_BREAK_CODE: player->asprite->sp.y_velocity+=10; 
                       w_pressed = false;
                       break;
    case A_MAKE_CODE:  if(a_pressed) break;
                       player->asprite->sp.x_velocity-=10; 
                       a_pressed = true;
                       //player->sp.frame_index = 2;
                       break;
    case A_BREAK_CODE: player->asprite->sp.x_velocity+=10; 
                       a_pressed = false;
                       break;
    case S_MAKE_CODE:  if(s_pressed) break;
                       player->asprite->sp.y_velocity+=10; 
                       s_pressed = true;
                       break;
    case S_BREAK_CODE: player->asprite->sp.y_velocity-=10; 
                       s_pressed = false;
                       break;
    case D_MAKE_CODE:  if(d_pressed) break;
                       player->asprite->sp.x_velocity+=10; 
                       d_pressed = true;
                       //player->sp.frame_index = 0;
                       break;
    case D_BREAK_CODE: player->asprite->sp.x_velocity-=10; 
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

  return (keep_sprite_in_bounds(&player->asprite->sp));
}
