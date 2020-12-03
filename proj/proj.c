// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "sprite.h"
#include "tenniscourt.xpm"
#include "playerdownright_0.xpm"
#include "playerdownright_1.xpm"
#include "playerdownleft_0.xpm"
#include "playerdownleft_1.xpm"
#include "aim.xpm"
#include "keyboard.h"
#include "mouse.h"
#include "player.h"
#include "crosshair.h"

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

  if(mouse_enable_data_reporting()) return 1;
  
  xpm_map_t player_xpm[] = {playerdownright_0_xpm, playerdownright_1_xpm, playerdownleft_0_xpm,playerdownleft_1_xpm};
  
  xpm_map_t court_xpm[] = {tenniscourt_xpm};

  xpm_map_t crosshair_xpm[] = {aim_xpm};

  uint8_t bit_no_timer;  
  uint8_t bit_no_kb;
  uint8_t bit_no_mouse;
  if(timer_subscribe_int(&bit_no_timer)) return 1;
  if(kb_subscribe_int(&bit_no_kb)) return 1; //subscribe KBC 
  if(mouse_subscribe_int(&bit_no_mouse)) return 1;
  int ipc_status;
  message msg;
  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_kb = BIT(bit_no_kb);
  uint32_t irq_set_mouse = BIT(bit_no_mouse);

  sprite_t court = *create_sprite(court_xpm,1,0,0,0,0,0);
  court.frame_index = 0;
  display_sprite(&court);

  player_t player;
  player.sp = *create_sprite(player_xpm,4,30,300,500,0,0);
  set_bounds(&player,0,700,250,500);
  player.sp.frame_index = 0;
  display_sprite(&player.sp);

  crosshair_t crosshair;
  crosshair.sp = *create_sprite(crosshair_xpm,1,0,400,300,0,0);
  crosshair.sp.frame_index = 0;
  //display_sprite(&crosshair.sp);

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
            //update_sprite_animation(&player.sp);
            timer_int_handler();
            if(interrupts % 1 == 0){
              erase_sprite(&court, &player.sp);
              erase_sprite(&court, &crosshair.sp);
              change_player_position(&player);
              //change_crosshair_position(&crosshair);
              display_sprite(&player.sp);
              display_sprite(&crosshair.sp);
            }
          }
          if (msg.m_notify.interrupts & irq_set_kb){
             kbc_ih(); //handler reads bytes from the KBC's Output_buf
             if(code_completed){
               change_player_velocity(&player,scancode[size-1]);
             }
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }

          if(msg.m_notify.interrupts & irq_set_mouse){
            mouse_ih();
            if(mouse_count == 3){
              struct packet pp = make_packet();
              read_deviation(&crosshair, &pp);
            }
          }
          break;
        default: break;
      }
    }
  }
  destroy_sprite(&player.sp);
  destroy_sprite(&court);
  destroy_sprite(&crosshair.sp);
  if(timer_unsubscribe_int()) return 1;
  if(kb_unsubscribe_int()) return 1;
  if(mouse_unsubscribe_int()) return 1;
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
