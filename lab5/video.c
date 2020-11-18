#include "video.h"

int video_init_mode(uint16_t mode){
  reg86_t r;

  memset(&r, 0, sizeof(reg86_t));
  
  r.ax = VBE_MODE; // VBE call, function 02 -- set VBE mode
  r.bx = LIN_FRAME_BUFF|mode; // set bit 14: linear framebuffer
  r.intno = BIOS_VIDEO_SERV;

  if( sys_int86(&r) != OK ) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }

  return 0;
}
