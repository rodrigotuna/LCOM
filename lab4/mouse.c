#include "mouse.h"

int mouse_subscribe_int(uint8_t* bit_no){
  mouse_hook_id = MOUSE_IRQ;
  *bit_no = mouse_hook_id;
  if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK) return 1;
  return 0;
}

int mouse_unsubscribe_int(){
  if(sys_irqrmpolicy(&mouse_hook_id) != OK) return 1;
  return 0;
}

int mouse_data_report(bool mode){
  if(kbc_issue_cmd(WRITE_B_MOUSE)) return 1;

  if(mode){
    if(kbc_issue_arg(EN_DATA_REP)) return 1;
  }else{
    if(kbc_issue_arg(DIS_DATA_REP)) return 1;
  }
  return 0;
}

struct packet make_packet(){
  struct packet p;
  p.bytes[0] = mouse_packet[0];
  p.bytes[1] = mouse_packet[1];
  p.bytes[2] = mouse_packet[2];
  p.lb = mouse_packet[0] & L_BUTTON;
  p.rb = mouse_packet[0] & R_BUTTON;
  p.mb = mouse_packet[0] & M_BUTTON;
  p.delta_x = sign_extend(mouse_packet[0] & MSB_X_DELTA, mouse_packet[1]);
  p.delta_y = sign_extend(mouse_packet[0] & MSB_Y_DELTA, mouse_packet[2]);
  p.x_ov = mouse_packet[0] & X_OVFL;
  p.y_ov = mouse_packet[0] & Y_OVFL;
  return p;

}

uint16_t sign_extend(bool sign, uint8_t byte){
  uint16_t res = 0;
  res = (sign)?  (0xFF << 8)|byte : byte;
  return res;
}

void (mouse_ih)(void){
  if (mouse_count ==3) mouse_count = 0;

  uint8_t code;
  kbc_read(&code);

  mouse_packet[mouse_count] = code;
  mouse_count++;
}


