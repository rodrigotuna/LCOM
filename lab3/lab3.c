#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

#include <minix/sysutil.h>

#include "i8042.h"
#include "kbc.h"
#include "keyboard.h"

extern uint32_t sys_counter;
extern uint32_t interrupts;

int main(int argc, char* argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  uint8_t bit_no;
  //kbc_restore();
  if(kb_subscribe_int(&bit_no)) return 1; //subscribe KBC 
  int ipc_status;
  message msg;
  uint32_t irq_set = BIT(bit_no);

  bool running = true;
 
  while (running) { 
    int r;
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) { 
             kbc_ih(); //handler reads bytes from the KBC's Output_buf
            if (code_completed){
              kbd_print_scancode(!(scancode[size-1] & BREAK_CODE), size, scancode);
            }
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }
  if(kb_unsubscribe_int()) return 1;
  if(kbd_print_no_sysinb(sys_counter)) return 1;
  return 0;
}

int(kbd_test_poll)() {
  do{
    kb_poll();
    kbd_print_scancode(!(scancode[size-1] & BREAK_CODE), size, scancode);

  }while(scancode[size-1] != ESC_BREAK_CODE);
  
  if(kbd_print_no_sysinb(sys_counter)) return 1;

  if (kbc_restore()) return 1;

  return 0;
}



int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t bit_no_kb,bit_no_timer;
  if(kb_subscribe_int(&bit_no_kb)) return 1; //subscribe KBC 
  if(timer_subscribe_int(&bit_no_timer)) return 1;
  int ipc_status;
  message msg;
  uint32_t kb_irq_set = BIT(bit_no_kb);
  uint32_t timer_irq_set = BIT(bit_no_timer);
  uint32_t FREQ = 60;
  uint8_t time = n;

  bool running = true;
 
  while (running && time) { 
    int r;
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if(msg.m_notify.interrupts &timer_irq_set){
            timer_int_handler();
            if (interrupts % FREQ == 0){
              time--;
            }
          }
          if (msg.m_notify.interrupts & kb_irq_set) { 
             kbc_ih(); //handler reads bytes from the KBC's Output_buf
            if (code_completed){
              kbd_print_scancode(!(scancode[size-1] & BREAK_CODE), size, scancode);
              time = n; interrupts = 0;
            }
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }
  if(kb_unsubscribe_int()) return 1;
  if(timer_unsubscribe_int()) return 1;
  if(kbd_print_no_sysinb(sys_counter)) return 1;
  return 0;
}
