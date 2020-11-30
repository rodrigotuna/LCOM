#include "player.h"

int change_player_velocity(player_t * player, uint8_t scancode){
  if(player == NULL) return 1;

  switch(scancode){
    case W_MAKE_CODE:  player->sp.y_velocity++; break;
    case W_BREAK_CODE: player->sp.y_velocity--; break;
    case A_MAKE_CODE:  player->sp.x_velocity--; break;
    case A_BREAK_CODE: player->sp.x_velocity++; break;
    case S_MAKE_CODE:  player->sp.y_velocity--; break;
    case S_BREAK_CODE: player->sp.y_velocity++; break;
    case D_MAKE_CODE:  player->sp.x_velocity++; break;
    case D_BREAK_CODE: player->sp.x_velocity--; break;
    default: return 1;
  }
  return 0;
}

int change_player_position(player_t * player){
  if(player == NULL) return 1;

  player->sp.x_pos += player->sp.x_velocity;
  player->sp.y_pos += player->sp.y_velocity;

  return (keep_player_in_bounds(player));
}

int keep_player_in_bounds(player_t * player){
  return 0;
}
