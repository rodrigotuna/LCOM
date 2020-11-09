#include "state_machine.h"

struct mouse_ev* mouse_detect_event( struct packet * pp){
  static struct mouse_ev event;
  static buttons_pressed = 0;

  uint8_t new_button = pp->bytes[0] & (L_BUTTON | R_BUTTON | M_BUTTON);

  if((pp->delta_x || pp->delta_y) && (buttons_pressed == new_button)){
    event.type = MOUSE_MOV;
  } else if((buttons_pressed ^ new_button) & L_BUTTON && (buttons_pressed == L_BUTTON)){
    event.type = LB_RELEASED;
  } else if ((buttons_pressed ^ new_button) & L_BUTTON && (new_button == L_BUTTON)){
    event.type = LB_PRESSED;
  } else if ((buttons_pressed ^ new_button) & R_BUTTON && (buttons_pressed == R_BUTTON)){
    event.type = RB_RELEASED;
  } else if ((buttons_pressed ^ new_button) & R_BUTTON && (new_button == R_BUTTON)){
    event.type = RB_RELEASED;
  }
  else {
    event.type = BUTTON_EV;
  }
  event.delta_x = pp->delta_x;
  event.delta_y = pp->delta_y;
  buttons_pressed = new_button;

  return &event;
}	

States state_machine(struct mouse_ev *ev, uint8_t x_len, uint8_t tolerance){
  static States state = INITIAL;
  int d_x = 0;
  int d_y = 0;

  switch(state){
    INITIAL:


  }
}