#include "video.h"

int video_get_inf(uint16_t mode){
  memset(&inf, 0, sizeof(vbe_mode_info_t));

  reg86_t r;
  memset(&r, 0, sizeof(reg86_t));

  vbe_mode_info_t *virtual_addr = lm_alloc(sizeof(vbe_mode_info_t), &map);

  r.intno = BIOS_VIDEO_SERV;
  r.ax = VBE_MODE_INFO;
  r.cx = mode;
  r.es = PB2BASE(map.phys);
  r.di = PB2OFF(map.phys);

  if( sys_int86(&r) != OK ) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return 1;
  }

  memcpy((void*)&inf, (void*)virtual_addr, sizeof(vbe_mode_info_t));
  lm_free(&map);
  return 0;
}

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

int bytesPerPixel(){
  return (inf.BitsPerPixel + 7) >> 3;
}

void map_memory(){
 
 struct minix_mem_range front_mr;
 memset(&front_mr,0,sizeof(struct minix_mem_range));

 unsigned int front_vram_base = inf.PhysBasePtr;
 unsigned int page_size = (1 * inf.XResolution) * inf.YResolution * bytesPerPixel();
 unsigned int vram_size = (2 * inf.XResolution) * inf.YResolution * bytesPerPixel();
 
 int r1;
 front_mr.mr_base = (phys_bytes) front_vram_base;
 front_mr.mr_limit = front_mr.mr_base + vram_size;
 
 if( OK != (r1 = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &front_mr)))
     panic("sys_privctl (ADD_MEM) failed: %d\n", r1);
 
 front_video_mem = vm_map_phys(SELF, (void *)front_mr.mr_base, vram_size);
 back_video_mem = (uint8_t *)front_video_mem + (page_size);

 memset(front_video_mem,0,sizeof(uint8_t)*vram_size);
 
 if(front_video_mem == MAP_FAILED)
     panic("couldn't map video memory");
 
 video_mem = front_video_mem;
}

void page_flipping(){
  reg86_t r;
  memset(&r, 0, sizeof(reg86_t));

  r.intno = BIOS_VIDEO_SERV;
  r.ax = VBE_SET_GET_DISPLAY_START;
  r.bl = 0x00;
  r.cx = PIXEL_POS;

  r.dx = (video_mem == front_video_mem) ? PIXEL_POS : (inf.YResolution);

  if( sys_int86(&r) != OK ) return;

  video_mem = (video_mem == front_video_mem) ? back_video_mem : front_video_mem;

}

int set_pixel(uint16_t x, uint16_t y, uint32_t color){
  if(x >= inf.XResolution || y >= inf.YResolution) return 1;

  unsigned int pos = (x + inf.XResolution * y)*bytesPerPixel();
  
  memcpy((void*) ((unsigned int)video_mem + pos), &color, bytesPerPixel());
  
  return 0;
}
