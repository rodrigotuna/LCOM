// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>


#include "menu.h"
#include "uart.h"
#include "utilities.h"
#include "waiting1.xpm"

// Any header files included below this line should have been created by you
extern int timer_interrupts;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

/*static int print_usage() {
  printf("Usage: <mode - hex>\n");

  return 1;
}*/

int(proj_main_loop)(int argc, char *argv[]) {
  /* 
   * Substitute the code below by your own
   */
  if(init_all()) return 1;

  if(subscribe_all()) return 1;

  /*sprite_t t = *create_sprite(tenniscourt_xpm,0,0);
  sprite_t font = *create_sprite(font_xpm,156,12);

  char string[] = "24-10-20";


  //print_string(string,&font);

  bool running = true;
  while (running) {
    uint32_t interrupts = get_interrupts();
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); //handler reads bytes from the KBC's Output_buf
      if(scancode[size-1] == ESC_BREAK_CODE) running = false;
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      if(timer_interrupts % 2 == 0){
        display_sprite(&t);
        print_string(string,&font);
        page_flipping();
      }
    }
  }
  destroy_sprite(&font);*/
  main_menu();

  if(unsubscribe_all()) return 1;
  if(reset_all()) return 1;
  return 0;

  /*if(uart_init()) return 1;  
  uint8_t bit_no;
  if(uart_subscribe_int(&bit_no)) return 1;
  if(timer_subscribe_int(&bit_no)) return 1;

  //if(uart_send_char('d')) return 1;

  while(v != 'e'){
    uint32_t interrupts = get_interrupts();
    if(interrupts & TIMER_IRQ_SET){
      timer_int_handler();
    } 
    if(interrupts & UART_IRQ_SET){
      uart_ih();
      printf("%c", v);
    }
  }
  //uart_send_char('d');

  uart_reset();
  if(timer_unsubscribe_int()) return 1;
  if(uart_unsubscribe_int()) return 1;
  return 0;*/
  /*//
  // if you're interested, try to extend the command line options so that the usage becomes:
  // <mode - hex> <minix3 logo  - true|false> <grayscale - true|false> <delay (secs)>
  //
  bool const minix3_logo = true;
  bool const grayscale = false;
  uint8_t const delay = 5;
  uint16_t mode;

  if (argc != 1)
    return print_usage();

  // parse mode info (it has some limitations for the sake of simplicity)
  if (sscanf(argv[0], "%hx", &mode) != 1) {
    printf("%s: invalid mode (%s)\n", __func__, argv[0]);

    return print_usage();
  }*/
}

