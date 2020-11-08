#include "keyboard.h"

int kb_hook_id;
uint8_t scancode[2];
uint8_t size;
bool code_completed = true;

int(kb_subscribe_int)(uint8_t *bit_no){
  *bit_no = KB_IRQ;  
  kb_hook_id = *bit_no;
  return sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kb_hook_id);
}

int(kb_unsubscribe_int)(){
  if(sys_irqdisable(&kb_hook_id) != OK) return 1;
  if(sys_irqrmpolicy(&kb_hook_id) != OK) return 1;
  return 0;
}

void (kbc_ih)(void) {
  if (code_completed) size = 0;
  uint8_t code;
  if(kbc_read(&code)) return;
  
  scancode[size] = code;
  size++;

  if(code == TWO_BYTE_CODE) code_completed = false;
  else code_completed = true;
} 

int kb_poll(){
  size = 0;
  while(true){
  uint8_t stat,data;
  if(util_sys_inb(KBC_ST_REG, &stat)) return 1; 
  if((stat &(KBC_PAR_ERR | KBC_TO_ERR))) return 1;
  if(stat & KBC_OBF) {
      util_sys_inb(KBC_OUT_BUF, &data);
      scancode[size] = data;
      size++;
      if(data != TWO_BYTE_CODE) return 0;
  }
  }
  return 1;
}
