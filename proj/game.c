#include "game.h"

#include "font.xpm"
#include "tenniscourt.xpm"
#include "sp_score.xpm"
#include "mp_score.xpm"
#include "net.xpm"
#include "playerdownright_0.xpm"
#include "playerdownright_1.xpm"
#include "playerdownleft_0.xpm"
#include "playerdownleft_1.xpm"
#include "playerupright_0.xpm"
#include "playerupright_1.xpm"
#include "playerupleft_0.xpm"
#include "playerupleft_1.xpm"
#include "aim.xpm"
#include "ball.xpm"
#include "tennismachine.xpm"

#include "drivers.h"
#include "entities.h"
#include "gameLogic.h"
#include "communication.h"

extern uint32_t timer_interrupts;

int single_player(){

  sprite_t *score = create_sprite(sp_score_xpm,12,7);

  sprite_t *font = create_sprite(font_xpm,165,12);

  sprite_t *court = create_sprite(tenniscourt_xpm,0,0);

  sprite_t *net = create_sprite(net_xpm,0,0);

  sprite_t *machine = create_sprite(tennismachine_xpm,360,54);

  sprite_t *crosshair = create_sprite(aim_xpm,400,300);
  set_bounds(crosshair, 0, 768, 0, 568);

  player_t player;
  xpm_map_t player_xpm[] = {playerdownright_0_xpm, playerdownright_1_xpm, playerdownleft_0_xpm,     
                                                                             playerdownleft_1_xpm};
  player.asprite = create_animated_sprite(player_xpm,2,2,30,300,500);
  player.x_velocity = 0; player.y_velocity = 0; player.points = 0;
  set_bounds(player.asprite->sp,0,700,250,500);

  ball_t ball;
  ball.sp = create_sprite(ball_xpm,390,100);
  set_bounds(ball.sp, 0, 768, 0, 568);
  ball.real_x_pos = 400; ball.real_y_pos = 100;
  ball.velocity_norm = 4;
  shoot_ball(&ball);

  bool running = true;
  char points[10];

  while (running) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(crosshair, pp.delta_x, -pp.delta_y);
        if(process_event(&pp) == PRESSED_LB && can_shoot(&ball, &player)){
          go_to_selected_point(&ball, crosshair->x_pos, crosshair->y_pos, 1);
        }
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); //handler reads bytes from the KBC's Output_buf
        if(code_completed){
          change_player_velocity(&player,scancode[size-1]);
        }
      if(scancode[size-1] == ESC_BREAK_CODE) running = false;
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(player.asprite);
      change_racket_side(&ball, &player);
      change_player_position(&player);
      change_ball_position(&ball);
      if(get_ball_state(&ball) == OUT_OF_BOUNDS){
        switch(get_winner_of_set(&ball)){
          case PLAYER1: shoot_ball(&ball); 
                        player.points++; 
                        break;
          case PLAYER2: running = false;
                        break;
        }
      }
      if(timer_interrupts % 2 == 0){
        display_sprite(court);
        display_sprite(score);
        int_to_char(player.points,points);
        print_string(points,font,165,12);
        display_sprite(net);
        display_sprite(machine);
        display_sprite(ball.sp);
        display_sprite(player.asprite->sp);
        display_sprite(crosshair);
        page_flipping();
      }
    }
  }
  change_player_velocity(&player, 0);
  destroy_animated_sprite(player.asprite);
  destroy_sprite(court);
  destroy_sprite(score);
  destroy_sprite(machine);
  destroy_sprite(net);
  destroy_sprite(crosshair);
  destroy_sprite(ball.sp);
  return player.points;
}

int multi_player_1(){

  sprite_t *scores = create_sprite(mp_score_xpm,12,7);

  sprite_t *font = create_sprite(font_xpm,165,12);

  sprite_t *court = create_sprite(tenniscourt_xpm,0,0);

  sprite_t *net = create_sprite(net_xpm,0,0);

  sprite_t *crosshair = create_sprite(aim_xpm,400,300);
  set_bounds(crosshair, 0, 768, 0, 568);

  player_t player1;
  xpm_map_t player1_xpm[] = {playerdownright_0_xpm, playerdownright_1_xpm,
                                                        playerdownleft_0_xpm, playerdownleft_1_xpm};
  player1.asprite = create_animated_sprite(player1_xpm,2,2,30,200,500);
  set_bounds(player1.asprite->sp,0,700,250,500);
  player1.points = 0;

  player_t player2;
  xpm_map_t player2_xpm[] = {playerupright_0_xpm, playerupright_1_xpm, playerupleft_0_xpm,     
                                                                                playerupleft_1_xpm};
  player2.asprite = create_animated_sprite(player2_xpm,2,2,30,500,0); 
  set_bounds(player2.asprite->sp,0,700,0,240);
  player2.points = 0;

  ball_t ball;
  ball.sp = create_sprite(ball_xpm,270,530);
  set_bounds(ball.sp, 0, 768, 0, 568);
  ball.velocity_norm = 7;

  service_positions(&ball, &player1, &player2, true);

  game_state_t state = SERVICE;

  char score[10];

  while (!(state == WIN || state == LOSE)) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(crosshair, pp.delta_x, -pp.delta_y);
        if(process_event(&pp) == PRESSED_LB && can_shoot(&ball, &player1)){
          if(state == SERVICE) state = PLAYING;
          send_ball_message(crosshair->x_pos, crosshair->y_pos);
          go_to_selected_point(&ball, crosshair->x_pos, crosshair->y_pos, 1);
        }
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); //handler reads bytes from the KBC's Output_buf
        if(code_completed && state != SERVICE){
          change_player_velocity(&player1, scancode[size-1]);
          send_player_message(scancode[size-1]);
        }
    }
    if(interrupts & UART_IRQ_SET){
      uart_ih();
      while(!empty(reciever)){
        if(handle_message(top(reciever))){
          if(from_player) change_remote_player_velocity(&player2, mess[1]);
          else {
            uint16_t x_pos = ((mess[0] >> 3) << 8) | mess[1];
            uint16_t y_pos = ((mess[0] & 0x07) << 8) | mess[2];
            go_to_selected_point(&ball, x_pos, y_pos, 2);
          }         
        }
        pop(reciever);
      }
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(player1.asprite);
      update_sprite_animation(player2.asprite);
      change_racket_side(&ball, &player1);
      change_racket_side(&ball, &player2);
      change_player_position(&player1);
      change_player_position(&player2);
      change_ball_position(&ball);
      if(get_ball_state(&ball) == OUT_OF_BOUNDS){
        switch(get_winner_of_set(&ball)){
          case PLAYER1: service_positions(&ball, &player1, &player2, true);
                        state = SERVICE;
                        if(update_score(&player1, &player2)) state = WIN;
                        break;
          case PLAYER2: service_positions(&ball, &player1, &player2, false); 
                        state = PLAYING;
                        if(update_score(&player2, &player1)) state = LOSE;
                        break;
        }
        reset_communication();
      }
      if(timer_interrupts % 2 == 0){
        display_sprite(court);
        display_sprite(scores);
        strcpy(score,multiplayer_score(&player1));
        strcat(score, "-");
        strcat(score,multiplayer_score(&player2));
        print_string(score, font, 60, 7);
        display_sprite(player2.asprite->sp);
        display_sprite(net);
        display_sprite(ball.sp);
        display_sprite(player1.asprite->sp);
        display_sprite(crosshair);
        page_flipping();
      }
    }
    if(interrupts & RTC_IRQ_SET){
      rtc_ih();
    }
  }
  change_player_velocity(&player1, 0);
  change_player_velocity(&player2, 0);
  destroy_animated_sprite(player1.asprite);
  destroy_animated_sprite(player2.asprite);
  destroy_sprite(font);
  destroy_sprite(scores);
  destroy_sprite(court);
  destroy_sprite(net);
  destroy_sprite(crosshair);
  destroy_sprite(ball.sp);

  if(state == WIN) return 1;
  else return 2;
}

int multi_player_2(){

  sprite_t *scores = create_sprite(mp_score_xpm,12,7);

  sprite_t *font = create_sprite(font_xpm,165,12);

  sprite_t *court = create_sprite(tenniscourt_xpm,0,0);

  sprite_t *net = create_sprite(net_xpm,0,0);

  sprite_t *crosshair = create_sprite(aim_xpm,400,300);
  set_bounds(crosshair, 0, 768, 0, 568);

  player_t player1;
  xpm_map_t player1_xpm[] = {playerdownright_0_xpm, playerdownright_1_xpm,
                                                        playerdownleft_0_xpm, playerdownleft_1_xpm};
  player1.asprite = create_animated_sprite(player1_xpm,2,2,30,200,500);
  set_bounds(player1.asprite->sp,0,700,250,500);
  player1.points = 0;

  player_t player2;
  xpm_map_t player2_xpm[] = {playerupright_0_xpm, playerupright_1_xpm, playerupleft_0_xpm,     
                                                                                playerupleft_1_xpm};
  player2.asprite = create_animated_sprite(player2_xpm,2,2,30,500,0); 
  set_bounds(player2.asprite->sp,0,700,0,240);
  player2.points = 0;

  ball_t ball;
  ball.sp = create_sprite(ball_xpm,270,530);
  set_bounds(ball.sp, 0, 768, 0, 568);
  ball.velocity_norm = 7;

  service_positions(&ball, &player1, &player2, true);

  game_state_t state = PLAYING;

  char score[10];

  while (!(state == WIN || state == LOSE)) {
    uint32_t interrupts = get_interrupts();
    if(interrupts & MOUSE_IRQ_SET){
      mouse_ih();
      if(mouse_count == 3){
        struct packet pp = make_packet();
        change_sprite_pos(crosshair, pp.delta_x, -pp.delta_y);
        if(process_event(&pp) == PRESSED_LB && can_shoot(&ball, &player2)){
          if(state == SERVICE) state = PLAYING;
          send_ball_message(crosshair->x_pos, crosshair->y_pos);
          go_to_selected_point(&ball, crosshair->x_pos, crosshair->y_pos, 2);
        }
      }
    }
    if (interrupts & KB_IRQ_SET){
        kbc_ih(); //handler reads bytes from the KBC's Output_buf
        if(code_completed && state != SERVICE){
          send_player_message(scancode[size-1]);
          change_player_velocity(&player2,scancode[size-1]);
        }
    }
    if(interrupts & UART_IRQ_SET){
      uart_ih();
      while(!empty(reciever)){
        if(handle_message(top(reciever))){
          if(from_player)change_remote_player_velocity(&player1, mess[1]);
          else {
            uint16_t x_pos = ((mess[0] >> 3) << 8) | mess[1];
            uint16_t y_pos = ((mess[0] & 0x07) << 8) | mess[2];
            go_to_selected_point(&ball, x_pos, y_pos, 1);
          }
        }
        pop(reciever);
      }
    }
    if (interrupts & TIMER_IRQ_SET){
      timer_int_handler();
      update_sprite_animation(player1.asprite);
      update_sprite_animation(player2.asprite);
      change_racket_side(&ball, &player1);
      change_racket_side(&ball, &player2);
      change_player_position(&player1);
      change_player_position(&player2);
      change_ball_position(&ball);
      if(get_ball_state(&ball) == OUT_OF_BOUNDS){
        switch(get_winner_of_set(&ball)){
          case PLAYER1: service_positions(&ball, &player1, &player2, true);
                        state = PLAYING;
                        if(update_score(&player1, &player2)) state = LOSE;
                        break;
          case PLAYER2: service_positions(&ball, &player1, &player2, false); 
                        state = SERVICE;
                        if(update_score(&player2, &player1)) state = WIN;
                        break;
        }
        reset_communication();
      }
      if(timer_interrupts % 2 == 0){
        display_sprite(court);
        display_sprite(scores);
        strcpy(score,multiplayer_score(&player1));
        strcat(score, "-");
        strcat(score,multiplayer_score(&player2));
        print_string(score, font, 60, 7);
        display_sprite(player2.asprite->sp);
        display_sprite(net);
        display_sprite(ball.sp);
        display_sprite(player1.asprite->sp);
        display_sprite(crosshair);
        page_flipping();
      }
    }
  }
  change_player_velocity(&player1, 0);
  change_player_velocity(&player2, 0);
  destroy_animated_sprite(player1.asprite);
  destroy_animated_sprite(player2.asprite);
  destroy_sprite(font);
  destroy_sprite(scores);
  destroy_sprite(court);
  destroy_sprite(net);
  destroy_sprite(crosshair);
  destroy_sprite(ball.sp);
  
  if(state == WIN) return 1;
  else return 2;
}
