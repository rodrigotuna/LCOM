#include "player.h"

int change_player_velocity(player_t * player, uint8_t scancode){
  if(player == NULL) return 1;

  switch(scancode){
    case W_MAKE_CODE:  player->y_velocity++; break;
    case W_BREAK_CODE: player->y_velocity--; break;
    case A_MAKE_CODE:  player->x_velocity--; break;
    case A_BREAK_CODE: player->x_velocity++; break;
    case S_MAKE_CODE:  player->y_velocity--; break;
    case S_BREAK_CODE: player->y_velocity++; break;
    case D_MAKE_CODE:  player->x_velocity++; break;
    case D_BREAK_CODE: player->x_velocity--; break;
    default: return 1;
  }
  return 0;
}

int change_player_position(player_t * player){
  if(player == NULL) return 1;

  player->x_pos += player->x_velocity;
  player->y_velocity += player->y_velocity;

  return (keep_player_in_bounds(player));
}

int keep_player_in_bounds(player_t * player){
  
}