#include "game.h"

#include "font.xpm"
#include "tenniscourt.xpm"
#include "net.xpm"
#include "playerdownright_0.xpm"
#include "playerdownright_1.xpm"
#include "playerdownleft_0.xpm"
#include "playerdownleft_1.xpm"
#include "aim.xpm"
#include "ball.xpm"
#include "tennismachine.xpm"

extern uint32_t timer_interrupts;

int single_player(){

  sprite_t font = *create_sprite(font_xpm,165,12);

  sprite_t court = *create_sprite(tenniscourt_xpm,0,0);

  sprite_t net = *create_sprite(net_xpm,0,0);

  sprite_t machine = *create_sprite(tennismachine_xpm,360,54);

  sprite_t crosshair;
  crosshair = *create_sprite(aim_xpm,400,300);
  set_bounds(&crosshair, 0, 768, 0, 568);

  player_t player;
  xpm_map_t player_xpm[] = {playerdownright_0_xpm, playerdownright_1_xpm, playerdownleft_0_xpm,     
                                                                             playerdownleft_1_xpm};
  player.asprite = *create_animated_sprite(player_xpm,2,2,30,300,500);
  player.x_velocity = 0; player.y_velocity = 0; player.points = 0;
  set_bounds(&player.asprite.sp,0,700,250,500);

  ball_t ball;
  ball.sp = *create_sprite(ball_xpm,390,100);
  set_bounds(&ball.sp, 0, 768, 0, 568);
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
        change_sprite_pos(&crosshair, pp.delta_x, -pp.delta_y);
        if(process_event(&pp) == PRESSED_LB && can_shoot(&ball, &player)){
          go_to_selected_point(&ball, crosshair.x_pos, crosshair.y_pos);
          player.points++;
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
      update_sprite_animation(&player.asprite);
      change_racket_side(&ball, &player);
      change_player_position(&player);
      change_ball_position(&ball);
      if(is_ball_out_of_bounds(&ball) == 1) shoot_ball(&ball);
      if(is_ball_out_of_bounds(&ball) == 2) running = false;
      if(timer_interrupts % 2 == 0){
        display_sprite(&court);
        int_to_char(player.points,points);
        print_string(points,&font);
        display_sprite(&net);
        display_sprite(&machine);
        display_sprite(&ball.sp);
        display_sprite(&player.asprite.sp);
        display_sprite(&crosshair);
        page_flipping();
      }
    }
  }
  change_player_velocity(&player, 0);
  destroy_animated_sprite(&player.asprite);
  destroy_sprite(&court);
  destroy_sprite(&net);
  destroy_sprite(&crosshair);
  destroy_sprite(&ball.sp);
  return 0;
}
