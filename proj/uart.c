#include "uart.h"

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

int uart_subscribe_int(uint8_t * bit_no){
  uart_hook_id = 5;
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

void uart_ih(){

}
