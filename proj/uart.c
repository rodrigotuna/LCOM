#include "uart.h"
#include "utilities.h"

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

queue_t *reciever;

int uart_init(){

  uint8_t lcr = BIT_NO_8 | BIT_STOP_2 | EVEN_PAR;
  if(uart_write_to_port(LCR, lcr)) return 1;

  uint8_t ier = REC_DATA_AVAIL_INT | RLS_INT;
  if(uart_write_to_port(IER, ier)) return 1;

  uint8_t fcr = EN_FIFO| EMPTY_RX | EMPTY_TX | TRIG_LEVEL_8;
  if(uart_write_to_port(FCR,fcr)) return 1;

  reciever = create_queue();

  return 0;
}

void uart_reset(){
  destroy_queue(reciever);
}

int uart_clean(){
  uint8_t fcr = EN_FIFO| EMPTY_RX | EMPTY_TX | TRIG_LEVEL_8;
  if(uart_write_to_port(FCR,fcr)) return 1;

  reciever->sz = 0;
  return 0;
}

int uart_subscribe_int(uint8_t * bit_no){
  uart_hook_id = COM1_IRQ;
  *bit_no = uart_hook_id;
  if(sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &uart_hook_id) != OK) return 1;
  return 0;
}

int uart_unsubscribe_int(){
  if(sys_irqrmpolicy(&uart_hook_id) != OK) return 1;
  return 0;
}

int uart_read_from_port(uint8_t port, uint8_t * arg){
  if(util_sys_inb(COM1_BASE_ADDR + port, arg) != OK) return 1;
  return 0;
}

int uart_write_to_port(uint8_t port, uint8_t arg){
  if(sys_outb(COM1_BASE_ADDR + port, arg) != OK) return 1;
  return 0;
}

int uart_send_char(uint8_t c){
  int tries = 100;
  while(tries--){
    uint8_t lsr;
    if(uart_read_from_port(LSR, &lsr)) return 1;
    if(lsr & TRANS_HOLD_EMPTY){
      if(uart_write_to_port(THR, c)) return 1;
      return 0;
    }
    tickdelay(micros_to_ticks(2000));
  }
    return 1;
}

int uart_send_string(uint8_t *s, int sz){
  for(int i = 0; i < sz; i++){
    if(uart_send_char(s[i])) return 1;
  }
  return 0;
}

int uart_read_fifo(){
  uint8_t lsr;
  if(uart_read_from_port(LSR, &lsr)) return 1;
  while(lsr & R_READY){
    uint8_t c;
    if(uart_read_from_port(RBR, &c)) return 1;
    push(reciever,c);
    if(uart_read_from_port(LSR, &lsr)) return 1;
  }
  return 0;
}

void uart_ih(){
  uint8_t iir;
  uint8_t lsr;
  if(uart_read_from_port(IIR, &iir)) return;
  if(iir & SER_NO_INT_PEND) return;
  switch(iir & INT_ID){
    case SER_RX_INT: if(uart_read_fifo()) return; break;
    case SER_RLS_INT: if(uart_read_from_port(LSR, &lsr)) return; break;
    case SER_CHAR_TO_INT: if(uart_read_fifo()) return; break;
    default: break;
  }
}
