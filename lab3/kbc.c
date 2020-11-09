#include "kbc.h"
#include <lcom/lab2.h>

int(kbc_issue_cmd)(uint8_t cmd){
  uint8_t stat;
  while(TRUE) {
    if(util_sys_inb(KBC_CMD_REG, &stat)) return 1; 
    if((stat & KBC_IBF) == 0){
      if(sys_outb(KBC_CMD_REG, cmd)) return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
  return 1;
}

int(kbc_issue_cmd_b)(uint8_t cmd){
  uint8_t stat;
  while(TRUE) {
    if(util_sys_inb(KBC_CMD_REG, &stat)) return 1; 
    if((stat & KBC_IBF) == 0){
      if(sys_outb(KBC_CMD_B, cmd)) return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
  return 1;
}

int kbc_read(uint8_t *data){
  while (TRUE){
    uint8_t stat;
    if(util_sys_inb(KBC_ST_REG, &stat)) return 1; 
    if ((stat &(KBC_PAR_ERR | KBC_TO_ERR))) return 1;
    if(stat & KBC_OBF) {
        util_sys_inb(KBC_OUT_BUF, data); /*ass. it returns OK*/
        return 0;
    }
  }
}

int (kbc_read_cmd)(uint8_t *cmd){
  if(kbc_issue_cmd(READ_CMD_B)) return 1;
  if(kbc_read(cmd)) return 1;
  return 0;
}

int (kbc_write_cmd)(uint8_t cmd){
 if(kbc_issue_cmd(WRITE_CMD_B)) return 1;
 if(kbc_issue_cmd_b(cmd)) return 1;
 return 0;
}

int (kbc_restore)(){
  uint8_t cmd;
  if(kbc_read_cmd(&cmd)) return 1;
  cmd = (cmd & ~KB_INT_DIS) | KB_INTERR_EN;
  if(kbc_write_cmd(cmd)) return 1;
  return 0;
}
