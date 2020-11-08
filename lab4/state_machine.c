#include "state_machine.h"

struct mouse_ev* mouse_detect_event( struct packet * pp){
  static struct mouse_ev event;
  static buttons_pressed = 0;

  uint8_t new_button = pp->bytes[0] & (L_BUTTON | R_BUTTON | M_BUTTON);

  if((pp->delta_x || pp->delta_y) && buttons_pressed = new_button){
    event.type = MOUSE_MOV;
  } else if((new_button == L_BUTTON && buttons_pressed = 0){

  }

  else if

}	

States state_machine(struct packet *pp){
  static States state = INITIAL;

  switch(state){
    INITIAL:


  }
}