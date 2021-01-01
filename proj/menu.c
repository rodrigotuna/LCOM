#include "menu.h"

#include "cursor.xpm"
#include "font.xpm"
#include "mainmenu.xpm"
#include "mainmenu_sp.xpm"
#include "mainmenu_mp.xpm"
#include "mainmenu_scores.xpm"
#include "mainmenu_quit.xpm"
#include "entername.xpm"
#include "entername_done.xpm"
#include "gameover.xpm"
#include "gameover_playagain.xpm"
#include "gameover_home.xpm"
#include "waiting1.xpm"
#include "waiting2.xpm"
#include "chooseplayer.xpm"
#include "chooseplayer_create.xpm"
#include "chooseplayer_join.xpm"
#include "scoreboard.xpm"
#include "scoreboard_home.xpm"

extern uint32_t timer_interrupts;

int main_menu(){

  sprite_t *cursor = create_sprite(cursor_xpm,400,300);
  set_bounds(cursor, 0, 776, 0, 576);

  xpm_map_t main_menu_xpm[] = {mainmenu_xpm, mainmenu_sp_xpm, mainmenu_mp_xpm, mainmenu_scores_xpm, mainmenu_quit_xpm};
  animated_sprite_t *mainmenu = create_animated_sprite(main_menu_xpm,5,1,0,0,0);

  button_state_t mode = NO_MODE;
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
            while(mode != QUIT){
              int points = single_player();
              int place = check_highscore(points);
              if(place != 0) entername_menu(place, points);
              if(gameover_menu(points)) mode = QUIT;
            }
              break;
            case MULTIPLAYER: 
            choose_player_menu();
              break;
            case SCORES: 
            scoreboard_menu();
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
        kbc_ih(); 
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

int entername_menu(int place, int points){
  sprite_t * font = create_sprite(font_xpm,290,345);

  sprite_t *cursor = create_sprite(cursor_xpm,400,300);
  set_bounds(cursor, 0, 776, 0, 576);

  xpm_map_t enter_name_xpm[] = {entername_xpm, entername_done_xpm};
  animated_sprite_t *namemenu = create_animated_sprite(enter_name_xpm,2,1,0,0,0);

  char name[11] = {""};
  button_state_t mode = NO_MODE;
  bool running = true;

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(cursor, pp.delta_x, -pp.delta_y);
        mode = name_menu_mode(cursor,namemenu, mode);
        if(process_event(&pp) == PRESSED_LB && mode != NO_MODE) running = false;
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih();
        if(code_completed){
          if(strlen(name) < 10 || scancode[size-1] == BACKSPACE_MAKECODE){
            strcpy(name,write_name(name,scancode[size-1]));
          }
        }
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(namemenu);
      if(timer_interrupts % 2 == 0){
        display_sprite(namemenu->sp);
        print_string(name,font,font->x_pos,font->y_pos);
        display_sprite(cursor);
        page_flipping();
      }
    }
  }
  add_new_score(name,points,place);
  destroy_animated_sprite(namemenu);
  destroy_sprite(font);
  destroy_sprite(cursor);
  return 0;
}

int gameover_menu(int points){
  sprite_t * font = create_sprite(font_xpm,409,312);
 
  sprite_t *cursor = create_sprite(cursor_xpm,400,300);
  set_bounds(cursor, 0, 776, 0, 576);

  xpm_map_t gameover_menu_xpm[] = {gameover_xpm, gameover_playagain_xpm, gameover_home_xpm};
  animated_sprite_t *gameover = create_animated_sprite(gameover_menu_xpm,3,1,0,0,0);

  button_state_t mode = NO_MODE;
  bool running = true;
  char points_str[10];

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(cursor, pp.delta_x, -pp.delta_y);
        mode = gameover_menu_mode(cursor,gameover, mode);
        if(process_event(&pp) == PRESSED_LB && mode != NO_MODE) running = false;
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); 
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(gameover);
      if(timer_interrupts % 2 == 0){
        display_sprite(gameover->sp);
        int_to_char(points,points_str);
        print_string(points_str,font,416,313);
        display_sprite(cursor);
        page_flipping();
      }
    }
  }
  destroy_animated_sprite(gameover);
  destroy_sprite(font);
  destroy_sprite(cursor);
  if(mode == PLAYAGAIN) return 0;
  return 1;
}

int choose_player_menu(){
  sprite_t *cursor = create_sprite(cursor_xpm,400,300);
  set_bounds(cursor, 0, 776, 0, 576);

  xpm_map_t choose_menu_xpm[] = {chooseplayer_xpm,chooseplayer_create_xpm,chooseplayer_join_xpm};
  animated_sprite_t *chooseplayermenu = create_animated_sprite(choose_menu_xpm,3,1,0,0,0);

  button_state_t mode = NO_MODE;
  bool running = true;

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(cursor, pp.delta_x, -pp.delta_y);
        mode = chooseplayer_menu_mode(cursor,chooseplayermenu, mode);
        if(process_event(&pp) == PRESSED_LB && mode != NO_MODE){
          switch(mode){
            case CREATE:
            if(connect_player1_menu()){ 
               multi_player_1();
            }
              break;
            case JOIN: 
            if(connect_player2_menu()){ 
               multi_player_2();
            }
              break;
            default:
            break;
          }
        }
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih();
      if(scancode[size-1] == ESC_BREAK_CODE) running = false;
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(chooseplayermenu);
      if(timer_interrupts % 2 == 0){
        display_sprite(chooseplayermenu->sp);
        display_sprite(cursor);
        page_flipping();
      }
    }
    if(interrupts & UART_IRQ_SET){
      uart_ih();
    }
  }
  destroy_animated_sprite(chooseplayermenu);
  destroy_sprite(cursor);
  return 0;
}

int connect_player1_menu(){
  bool running = true;
  int found = 0;
  rtc_set_alarm(30);
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
    if(interrupts & RTC_IRQ_SET){
      rtc_ih();
      if(alarm_int) running = false;
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

int scoreboard_menu(){
  sprite_t *font = create_sprite(font_xpm,70,191);

  sprite_t *cursor = create_sprite(cursor_xpm,400,300);
  set_bounds(cursor, 0, 776, 0, 576);

  xpm_map_t scoreboard_menu_xpm[] = {scoreboard_xpm, scoreboard_home_xpm};
  animated_sprite_t *scoreboardmenu = create_animated_sprite(scoreboard_menu_xpm,2,1,0,0,0);

  button_state_t mode = NO_MODE;
  bool running = true;

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(cursor, pp.delta_x, -pp.delta_y);
        mode = scoreboard_menu_mode(cursor,scoreboardmenu, mode);
        if(process_event(&pp) == PRESSED_LB && mode != NO_MODE) running = false;
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih();
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(scoreboardmenu);
      if(timer_interrupts % 2 == 0){
        display_sprite(scoreboardmenu->sp);
        display_scores(font);
        display_sprite(cursor);
        font->x_pos = 70; 
        font->y_pos = 191;
        page_flipping();
      }
    }
  }
  destroy_animated_sprite(scoreboardmenu);
  destroy_sprite(font);
  destroy_sprite(cursor);
  return 0;
}

button_state_t main_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode){
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

button_state_t name_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode){
  if(check_button_bounds(cursor->x_pos,cursor->y_pos,331,455, SMALL)){
    menu->set_index = 1;
    mode = DONE;
  }
  else{
    menu->set_index = 0;
    mode = NO_MODE;
  }
  return mode;
}

button_state_t gameover_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode){

  if(check_button_bounds(cursor->x_pos,cursor->y_pos,227,404, SMALL)){
    menu->set_index = 1;
    mode = PLAYAGAIN;
  }
  else if(check_button_bounds(cursor->x_pos,cursor->y_pos,428,404, SMALL)){
    menu->set_index = 2;
    mode = HOME;
  }
  else{
    menu->set_index = 0;
    mode = NO_MODE;
  }
  return mode;
}

button_state_t chooseplayer_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode){
  if(check_button_bounds(cursor->x_pos,cursor->y_pos,204,479, SMALL)){
    menu->set_index = 1;
    mode = CREATE;
  }
  else if(check_button_bounds(cursor->x_pos,cursor->y_pos,461,479, SMALL)){
    menu->set_index = 2;
    mode = JOIN;
  }
  else{
    menu->set_index = 0;
    mode = NO_MODE;
  }
  return mode;
}

button_state_t scoreboard_menu_mode(sprite_t * cursor, animated_sprite_t * menu, button_state_t mode){
  if(check_button_bounds(cursor->x_pos,cursor->y_pos,159,493, BIG)){
    menu->set_index = 1;
    mode = HOME;
  }
  else{
    menu->set_index = 0;
    mode = NO_MODE;
  }
  return mode;
}

bool check_button_bounds(int16_t cursor_x, int16_t cursor_y, int xi,int yi, button_sizes_t size){
  if(cursor_y >= yi && cursor_y <= (yi + 55)){
    if(cursor_x >= xi && cursor_x <= (xi + 135) && size == SMALL) return 1;
    else if(cursor_x >= xi && cursor_x <= (xi + 486) && size == BIG)return 1;
  }
  return 0;
}
