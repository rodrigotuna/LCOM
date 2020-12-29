#include "drivers.h"

int subscribe_all(){
  uint8_t bit_no; 
  if(timer_subscribe_int(&bit_no)) return 1;
  if(kb_subscribe_int(&bit_no)) return 1; 
  if(mouse_subscribe_int(&bit_no)) return 1;
  if(rtc_subscribe_int(&bit_no)) return 1;
  if(uart_subscribe_int(&bit_no)) return 1;
  return 0;
}

int unsubscribe_all(){
  if(timer_unsubscribe_int()) return 1;
  if(kb_unsubscribe_int()) return 1;
  if(mouse_unsubscribe_int()) return 1;
  if(rtc_unsubscribe_int()) return 1;
  if(uart_unsubscribe_int()) return 1;
  return 0;
}

uint32_t get_interrupts(){
    int ipc_status;
    message msg;
    int r;
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      return 0;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: return msg.m_notify.interrupts;
        default: return 0;
      }
    }
    return 0;
}

int init_all(){
  if(video_get_inf(MODE)) return 1;

  map_memory();

  if(video_init_mode(MODE)) return 1;
  if(mouse_data_report(true)) return 1;
  if(rtc_enable_int(AIE)) return 1;
  if(uart_init()) return 1;
  return 0;
}

int reset_all(){
  free(front_video_mem);
  free(back_video_mem);
  if(rtc_disable_int(AIE)) return 1;
  if(mouse_data_report(false)) return 1;
  uart_reset();
  if(vg_exit()) return 1;
  return 0;
}
