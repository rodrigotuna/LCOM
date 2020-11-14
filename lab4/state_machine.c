#include "state_machine.h"

struct mouse_ev* mouse_detect_ev( struct packet * pp){
  static struct mouse_ev event;
  static uint8_t buttons_pressed = 0;

  uint8_t new_button = pp->bytes[0] & (L_BUTTON | R_BUTTON | M_BUTTON);

  if(buttons_pressed == new_button){
    event.type = MOUSE_MOV;
  } else if((buttons_pressed ^ new_button) & L_BUTTON && (buttons_pressed == L_BUTTON)){
    event.type = LB_RELEASED;
  } else if ((buttons_pressed ^ new_button) & L_BUTTON && (new_button == L_BUTTON)){
    event.type = LB_PRESSED;
  } else if ((buttons_pressed ^ new_button) & R_BUTTON && (buttons_pressed == R_BUTTON)){
    event.type = RB_RELEASED;
  } else if ((buttons_pressed ^ new_button) & R_BUTTON && (new_button == R_BUTTON)){
    event.type = RB_PRESSED;
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
  static int d_x = 0;
  static int d_y = 0;

  switch(state){
    case INITIAL: 
      if(ev->type == LB_PRESSED){
        state = UP;
      }
      break;

    case UP: 
      if(ev->type == MOUSE_MOV){
        if(ev->delta_y < -tolerance || ev->delta_x < -tolerance){
          state = INITIAL;
          d_x = 0;
          d_y = 0;
          break;
        }
          d_x += ev->delta_x;
          d_y += ev->delta_y;
      }
      else if(ev->type == LB_RELEASED){
        if(abs(d_y) >= abs(d_x) && abs(d_x) >= x_len){
            state = VERTIX;
            d_x = 0;
            d_y = 0;
            break;
        }
        state = INITIAL;
        d_x = 0;
        d_y = 0;
      } else {
        state = INITIAL;
        d_x = 0;
        d_y = 0;
      }
      break;

    case VERTIX:
      if(ev->type == MOUSE_MOV){
        if(abs(ev->delta_x) <= tolerance && abs(ev->delta_y) <= tolerance){
        state = VERTIX;
        d_x += ev->delta_x;
        d_y += ev->delta_y;
        break;
        }
        state = INITIAL;
        d_x = 0;
        d_y = 0;
      }
      else if(ev->type == LB_PRESSED){
        state = UP;
        d_x = 0;
        d_y = 0;
      }
      else if (ev->type == RB_PRESSED){
        state = DOWN;
        d_x = 0;
        d_y = 0;
      }else{
        state = INITIAL;
        d_x = 0;
        d_y = 0;
      }
      break;

    case DOWN:
      if(ev->type == MOUSE_MOV){
        if(ev->delta_y > tolerance || ev->delta_x > tolerance){
          state = INITIAL;
          d_x = 0;
          d_y = 0;
          break;
        }
        d_x += ev->delta_x;
        d_y += ev->delta_y;
      }
      else if(ev->type == RB_RELEASED){
          if(abs(d_y) >= abs(d_x) && abs(d_x) >= x_len){
            state = END;
            break;
          }
          state = INITIAL;
          d_x = 0;
          d_y = 0;
      } else {
        state = INITIAL;
        d_x = 0;
        d_y = 0;
      }
      break;
      default: state = INITIAL;
  }
  return state;
}
