#include "menu.h"

#include "cursor.xpm"
#include "mainmenu.xpm"
#include "mainmenu_sp.xpm"
#include "mainmenu_mp.xpm"
#include "mainmenu_scores.xpm"
#include "mainmenu_quit.xpm"
#include "waiting1.xpm"
#include "waiting2.xpm"

extern uint32_t timer_interrupts;

int main_menu(){

  sprite_t *cursor = create_sprite(cursor_xpm,400,300);
  set_bounds(cursor, 0, 776, 0, 576);

  xpm_map_t main_menu_xpm[] = {mainmenu_xpm, mainmenu_sp_xpm, mainmenu_mp_xpm, mainmenu_scores_xpm, mainmenu_quit_xpm};
  animated_sprite_t *mainmenu = create_animated_sprite(main_menu_xpm,5,1,0,0,0);

  menu_state_t mode = NO_MODE;
  bool running = true;

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(cursor, pp.delta_x, -pp.delta_y);
        mode = main_menu_mode(cursor,mainmenu, mode);
        if(process_event(&pp) == PRESSED_LB && mode != NO_MODE){
          switch(mode){
            case SINGLEPLAYER:
              if(single_player() == 0) mode = QUIT;
              break;
            case MULTIPLAYER: 
            //ISTO DEPOIS NAO FICA AQUI
            if(connect_player1_menu()){ 
                multi_player_1();
            }
              break;
            case SCORES: 
            //ISTO DEPOIS NAO FICA AQUI
            if(connect_player2_menu()){ 
               multi_player_2();
            }
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
      update_sprite_animation(mainmenu);
      if(timer_interrupts % 2 == 0){
        display_sprite(mainmenu->sp);
        display_sprite(cursor);
        page_flipping();
      }
    }
    if(interrupts & UART_IRQ_SET){
      uart_ih();
    }
  }
  destroy_animated_sprite(mainmenu);
  destroy_sprite(cursor);
  return 0;
}

bool check_button_bounds(int16_t cursor_x, int16_t cursor_y, int xi,int yi, button_sizes_t size){
  if(cursor_y >= yi && cursor_y <= (yi + 55)){
    if(cursor_x >= xi && cursor_x <= (xi + 135) && size == SMALL) return 1;
    else if(cursor_x >= xi && cursor_x <= (xi + 486) && size == BIG)return 1;
  }
  if(cursor_y >= yi && cursor_y <= (yi + 254) && 
    cursor_x >= xi && cursor_x <= (xi + 185) && size == MEDIUM) return 1;
  return 0;
}

menu_state_t main_menu_mode(sprite_t * cursor, animated_sprite_t * menu, menu_state_t mode){
  if(check_button_bounds(cursor->x_pos,cursor->y_pos,163,420, SMALL)){
    menu->set_index = 1;
    mode = SINGLEPLAYER;
  }
  else if(check_button_bounds(cursor->x_pos,cursor->y_pos,337,420, SMALL)){
    menu->set_index = 2;
    mode = MULTIPLAYER;
  }
  else if(check_button_bounds(cursor->x_pos,cursor->y_pos,512,420, SMALL)){
    menu->set_index = 3;
    mode = SCORES;
  }
  else if(check_button_bounds(cursor->x_pos,cursor->y_pos,163,509, BIG)){
    menu->set_index = 4;
    mode = QUIT;
  }
  else{
    menu->set_index = 0;
    mode = NO_MODE;
  }
  return mode;
}

int connect_player1_menu(){
  bool running = true;
  int found = 0;
  sprite_t * wait_menu = create_sprite(waiting2_xpm, 0, 0);
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
      if(timer_interrupts % 2 == 0){
        display_sprite(wait_menu);
        page_flipping();
      }
    }

    if(interrupts & UART_IRQ_SET){
      uart_ih();
      if(top(reciever) == '2'){
        running = false;
        found = 1;
        pop(reciever);
      }
    }
  }
  if(found) uart_send_char('1');
  destroy_sprite(wait_menu);
  return found;
}

int connect_player2_menu(){
  bool running = true;
  int found = 0;
  sprite_t * wait_menu = create_sprite(waiting1_xpm, 0, 0);
  uart_send_char('2');
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
      if(timer_interrupts % 2 == 0){
        display_sprite(wait_menu);
        page_flipping();
      }
    }

    if(interrupts & UART_IRQ_SET){
      uart_ih();
      if(top(reciever)  == '1'){
        running = false;
        found = 1;
        pop(reciever);
      }
    }
  }
  destroy_sprite(wait_menu);
  return found;
}
