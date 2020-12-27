#include "menu.h"

#include "cursor.xpm"
#include "mainmenu.xpm"
#include "mainmenu_sp.xpm"
#include "mainmenu_mp.xpm"
#include "mainmenu_scores.xpm"
#include "mainmenu_quit.xpm"

extern uint32_t timer_interrupts;

int main_menu(){

  sprite_t cursor = *create_sprite(cursor_xpm,400,300);
  set_bounds(&cursor, 0, 776, 0, 576);

  xpm_map_t menu_xpm[] = {mainmenu_xpm, mainmenu_sp_xpm, mainmenu_mp_xpm, mainmenu_scores_xpm, mainmenu_quit_xpm};
  animated_sprite_t menu = *create_animated_sprite(menu_xpm,5,1,0,0,0);

  menu_state_t mode = NO_MODE;
  bool running = true;

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(&cursor, pp.delta_x, -pp.delta_y);
        mode = check_button_bounds(&cursor,&menu, mode);
        if(process_event(&pp) == PRESSED_LB && mode != NO_MODE){
          switch(mode){
            case SINGLEPLAYER:
              if(single_player() == 0) mode = QUIT;
              break;
            case MULTIPLAYER:
              break;
            case SCORES:
              break;
            case QUIT:
              running = false;
              break;
            default:
            break;
          }
        }
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); //handler reads bytes from the KBC's Output_buf
      if(scancode[size-1] == ESC_BREAK_CODE) running = false;
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(&menu);
      if(timer_interrupts % 2 == 0){
        display_sprite(&menu.sp);
        display_sprite(&cursor);
        page_flipping();
      }
    }
    if(interrupts & UART_IRQ_SET){
      uart_ih();
    }
  }
  destroy_animated_sprite(&menu);
  destroy_sprite(&cursor);
  return 0;
}

menu_state_t check_button_bounds(sprite_t * cursor, animated_sprite_t * menu, menu_state_t mode){
  if(cursor->y_pos >= 420 && cursor->y_pos <= 475){
    if(cursor->x_pos >= 163 && cursor->x_pos <= 295){
      menu->set_index = 1;
      mode = SINGLEPLAYER;
    }
    if(cursor->x_pos >= 339 && cursor->x_pos <= 471){
      menu->set_index = 2;
      mode = MULTIPLAYER;
    }
    if(cursor->x_pos >= 514 && cursor->x_pos <= 646){
      menu->set_index = 3;
      mode = SCORES;
    }
  }
  else if(cursor->y_pos >= 509 && cursor->y_pos <= 563 && cursor->x_pos >= 163 && 
  cursor->x_pos <= 647){
    menu->set_index = 4;
    mode = QUIT;
  }
  else{
    menu->set_index = 0;
    mode = NO_MODE;
  }
  return mode;
}

int connect_players(uint8_t send, uint8_t recieve){
  vg_exit();
  bool running = true;
  int found = 0;
  reset_var();
  int t = 100;
  uint8_t dum = '0';
  while(t--){
    uart_read_char(&dum);
    printf("%c", dum);
    dum = '0';
  }
  uart_clean_buffer();
  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); 
      if(scancode[size-1] == ESC_BREAK_CODE) running = false;
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      uart_clean_buffer();
      uart_send_char(send);
      if(timer_interrupts % 2 == 0){
        page_flipping();
      }
    }

    if(interrupts & UART_IRQ_SET){
      uart_ih();
      printf("%c", v);
      if(v == recieve){
        running = false;
        found = 1;
      }
    }
  }
  uart_send_char(send);

  int n = 1000;
  while(n--){
    uart_clean_buffer();
  }

  return found;
}
