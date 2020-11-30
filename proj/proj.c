// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "sprite.h"
#include "tenniscourt.xpm"
#include "playerdown1.xpm"
#include "keyboard.h"
#include "player.h"

extern uint32_t interrupts;

// Any header files included below this line should have been created by you

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
  if(video_get_inf(MODE)) return 1;

  map_memory();

  if(video_init_mode(MODE)) return 1;
  
  
  uint8_t bit_no_timer;  
  uint8_t bit_no_kb;
  if(timer_subscribe_int(&bit_no_timer)) return 1;
  if(kb_subscribe_int(&bit_no_kb)) return 1; //subscribe KBC 
  int ipc_status;
  message msg;
  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_kb = BIT(bit_no_kb);

  sprite_t court = *create_sprite(tenniscourt_xpm,0,0,0,0);
  display_sprite(&court);

  player_t player;
  player.sp = *create_sprite(playerdown1_xpm,300,500,0,0);
  display_sprite(&player.sp);

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
          if (msg.m_notify.interrupts & irq_set_timer){
            display_sprite(&court);
            change_player_position(&player);
            display_sprite(&player.sp);
             
        }if (msg.m_notify.interrupts & irq_set_kb){
             kbc_ih(); //handler reads bytes from the KBC's Output_buf
             if(code_completed){
               change_player_velocity(&player,scancode[size-1]);
             }
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }
  if(timer_unsubscribe_int()) return 1;
  if(kb_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;

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
