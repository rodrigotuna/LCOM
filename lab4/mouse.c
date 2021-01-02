#include "mouse.h"

uint8_t mouse_count = 0;

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

struct packet make_packet(){
  struct packet p;
  p.bytes[0] = mouse_packet[0];
  p.bytes[1] = mouse_packet[1];
  p.bytes[2] = mouse_packet[2];
  p.lb = mouse_packet[0] & L_BUTTON;
  p.rb = mouse_packet[0] & R_BUTTON;
  p.mb = mouse_packet[0] & M_BUTTON;
  if(mouse_packet[0] & MSB_X_DELTA){
    p.delta_x = (0xFF << 8)|mouse_packet[1];
  } else{
    p.delta_x = mouse_packet[1];
  }
  if(mouse_packet[0] & MSB_Y_DELTA){
    p.delta_y = (0xFF << 8)|mouse_packet[2];
  } else{
    p.delta_y = mouse_packet[2];
  }
  p.x_ov = mouse_packet[0] & X_OVFL;
  p.y_ov = mouse_packet[0] & Y_OVFL;
  return p;

}

void (mouse_ih)(void){
  if (mouse_count ==3) mouse_count = 0;

  uint8_t code;
  if(mouse_read(&code)) return;

  mouse_packet[mouse_count] = code;
  mouse_count++;
}

int mouse_read(uint8_t *data){
  while(TRUE){
    uint8_t stat;
    if(util_sys_inb(KBC_ST_REG, &stat)) return 1; 
    if ((stat &(KBC_PAR_ERR | KBC_TO_ERR))) return 1;
    //if((stat & KBC_OBF) && (stat & KBC_AUX)) {
        util_sys_inb(KBC_OUT_BUF, data); /*ass. it returns OK*/
        return 0;
    //}
  }
  return 1;
}

int mouse_set_arg(uint8_t arg){
  uint8_t ack;
  while(TRUE){
  if(kbc_issue_cmd(WRITE_B_MOUSE)) return 1;
  if(kbc_issue_arg(arg)) return 1;

  if(mouse_read(&ack)) return 1;

  if(ack == ACK) return 0;
  if(ack == ERROR) return 1;

  tickdelay(micros_to_ticks(DELAY_US));
  }
}

int mouse_poll_byte(uint8_t *data){
  while (true){
  uint8_t stat;
  if(util_sys_inb(KBC_ST_REG, &stat)) return 1; 
  if ((stat &(KBC_PAR_ERR | KBC_TO_ERR))) return 1;
  if((stat & KBC_OBF) && (stat & KBC_AUX)) {
      util_sys_inb(KBC_OUT_BUF, data); /*ass. it returns OK*/
      return 0;
  }
 }
}


void mouse_poll(){
  uint8_t byte;
  for(int i = 0; i < 3; i++){
    mouse_set_arg(READ_DATA);
    mouse_poll_byte(&byte);
    mouse_packet[i] = byte;
  }
}
