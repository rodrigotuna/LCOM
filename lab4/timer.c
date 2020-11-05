#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

uint32_t interrupts = 0;
int timer_hook_id;

int (timer_set_frequency)(uint8_t timer, uint32_t freq){
  if(freq > TIMER_FREQ || freq < TIMER_MIN_FREQ) return 1;

  uint8_t st;
  if(timer_get_conf(timer,&st)) return 1;

  st &= (TIMER_MODE_MASK | TIMER_BASE_MASK);
  uint8_t ctrl_word = TIMER_SEL(timer) | TIMER_LSB_MSB | st;
  if(sys_outb(TIMER_CTRL,ctrl_word) != OK) return 1;

  uint16_t div = TIMER_FREQ / freq;

  uint8_t lsb,msb;
  if(util_get_LSB(div,&lsb)) return 1;
  if(util_get_MSB(div,&msb)) return 1;

  if(sys_outb(TIMER_(timer),lsb) != OK) return 1;
  if(sys_outb(TIMER_(timer),msb) != OK) return 1;
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
   timer_hook_id = TIMER0_IRQ;
   *bit_no = timer_hook_id;
   if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != OK) return 1; 
   return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer_hook_id) != OK) return 1;
  return 0;
}

void (timer_int_handler)() {
  interrupts++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL) return 1;

  uint8_t cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if (sys_outb(TIMER_CTRL, cmd) != OK) return 1;

  if (util_sys_inb(TIMER_(timer),st)) return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val val;
  uint8_t initial = (st & TIMER_LSB_MSB) >> TIMER_INIT_MODE_POS;

  switch(field){
    case tsf_all:
      val.byte = st;
      break;
    case tsf_initial:
     switch(initial){
       case 0: val.in_mode = INVAL_val; break;
       case 1: val.in_mode = LSB_only; break;
       case 2: val.in_mode = MSB_only; break;
       case 3: val.in_mode = MSB_after_LSB; break;
       default : return 1;
     }
     break;
    case tsf_mode:
      val.count_mode = (st & TIMER_MODE_MASK) >> TIMER_MODE_POS;
      break;
    case tsf_base: 
     val.bcd = st;
     break;
    default : return 1;
  }
  if(timer_print_config(timer,field,val)) return 1;
  return 0;
}
