#include "communication.h"

int len = 0;

int send_player_message(uint8_t scancode){
  uint8_t mess[2];
  mess[0] = 'P';
  mess[1] = scancode;
  return uart_send_string(mess,2);
}

int send_ball_message(uint16_t x_pos, uint16_t y_pos){
  uint8_t mess[3];
  uint8_t x_msb;
  uint8_t y_msb;
  util_get_MSB(x_pos, &x_msb);
  util_get_LSB(x_pos, &mess[1]);
  util_get_MSB(y_pos, &y_msb);
  util_get_LSB(y_pos, &mess[2]);
  mess[0] = x_msb << 3 | y_msb;
  return uart_send_string(mess,3);
}

int handle_message(uint8_t c){
  if( len == 0){
    if(c == 'P') from_player = true;
    else from_player = false;
  }

  mess[len] = c;
  len++;

  if(from_player && len == 2){
    len = 0;
    return 1;
  }

  if(len == 3){
    len = 0;
    return 1;
  }

  return 0;
}
