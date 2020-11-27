// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "video.h"
#include "keyboard.h"

extern int interrupts;
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(video_init_mode(mode)) return 1;

  tickdelay(micros_to_ticks(delay*1000000));

  if(vg_exit()) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  if(video_get_inf(mode)) return 1;

  map_memory();

  if(video_init_mode(mode)) return 1;
  
  if(vg_draw_rectangle(x,y,width,height,color)) return 1;

  uint8_t bit_no;
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
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }
  free_mem_map();
  if(kb_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  if(video_get_inf(mode)) return 1;

  map_memory();

  if(video_init_mode(mode)) return 1;

  uint16_t xPos = 0;
  uint16_t yPos = 0;

  uint16_t width = inf.XResolution /no_rectangles;
  uint16_t height = inf.YResolution /no_rectangles;

  for(uint8_t i = 0; i < no_rectangles; i++){
    xPos = 0;
    for(uint8_t j = 0; j < no_rectangles; j++){
      uint32_t color = new_color(j, i, no_rectangles, first, step);
      if(vg_draw_rectangle(xPos, yPos, width, height, color)) return 1;
      xPos+= width;
    }
    yPos+= height;
  }
  

  uint8_t bit_no;
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
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }

  free_mem_map();
  if(kb_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {  
  if(video_get_inf(INDEXED_MODE)) return 1;

  map_memory();

  if(video_init_mode(INDEXED_MODE)) return 1;

  if(display_xpm(xpm,x,y)) return 1;

  uint8_t bit_no;
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
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }

  free_mem_map();
  if(kb_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {

  if(video_get_inf(INDEXED_MODE)) return 1;

  map_memory();

  if(video_init_mode(INDEXED_MODE)) return 1;
  
  uint8_t bit_no_timer;  
  uint8_t bit_no_kb;
  if(timer_subscribe_int(&bit_no_timer)) return 1;
  if(kb_subscribe_int(&bit_no_kb)) return 1; //subscribe KBC 
  int ipc_status;

  message msg;
  uint32_t irq_set_timer = BIT(bit_no_timer);
  uint32_t irq_set_kb = BIT(bit_no_kb);

  uint32_t FREQ = fr_rate;
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
             timer_int_handler();
            if(interrupts % FREQ == 0){
              if(move(xpm,xi,yi,xf,yf,speed)) return 1;
            }
          }
          if (msg.m_notify.interrupts & irq_set_kb){
             kbc_ih(); //handler reads bytes from the KBC's Output_buf
            if(scancode[size-1] == ESC_BREAK_CODE) running = false;
          }
          break;
        default: break;
      }
    }
  }

  free_mem_map();
  if(timer_unsubscribe_int()) return 1;
  if(kb_unsubscribe_int()) return 1;
  if(vg_exit()) return 1;

  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
