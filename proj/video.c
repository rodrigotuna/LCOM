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
  struct minix_mem_range front_mr, back_mr;

  memset(&front_mr,0,sizeof(struct minix_mem_range));
  memset(&back_mr,0,sizeof(struct minix_mem_range));

  unsigned int front_vram_base = inf.PhysBasePtr;
  unsigned int vram_size = inf.XResolution * inf.YResolution * bytesPerPixel();

  unsigned int back_vram_base = inf.PhysBasePtr + vram_size;

  int r1, r2;
  front_mr.mr_base = (phys_bytes) front_vram_base;
  front_mr.mr_limit = front_mr.mr_base + vram_size;  

  back_mr.mr_base = (phys_bytes) back_vram_base;
  back_mr.mr_limit = back_mr.mr_base + vram_size;

  if( OK != (r1 = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &front_mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r1);

  if( OK != (r2 = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &back_mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r2);

/* Map memory */

  front_video_mem = vm_map_phys(SELF, (void *)front_mr.mr_base, vram_size);

  back_video_mem = vm_map_phys(SELF, (void *)back_mr.mr_base, vram_size);

  if(front_video_mem == MAP_FAILED || back_video_mem == MAP_FAILED)
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

  /*void * temp = front_video_mem;
  front_video_mem = back_video_mem;
  back_video_mem = temp;*/

  video_mem = (video_mem == front_video_mem) ? back_video_mem : front_video_mem;

}

uint32_t getRed(uint32_t color){
  return (color >> inf.RedFieldPosition) & (BIT(inf.RedMaskSize) - 1);
}

uint32_t getBlue(uint32_t color){
  return (color >> inf.BlueFieldPosition) & (BIT(inf.BlueMaskSize) - 1);
}

uint32_t getGreen(uint32_t color){
  return (color >> inf.GreenFieldPosition) & (BIT(inf.GreenMaskSize) - 1);
}

uint32_t setColor(uint32_t red, uint32_t green, uint32_t blue){
  return (red << inf.RedFieldPosition) | (green << inf.GreenFieldPosition) | (blue
                                                                        << inf.BlueFieldPosition);
}

uint32_t new_color(uint16_t x, uint16_t y, uint8_t no_rectangles, uint32_t first, uint8_t step){
  if(bytesPerPixel() == 1){
      return (first + (y* no_rectangles + x) * step) % (1 << inf.BitsPerPixel);
  }else {
      uint32_t red = (getRed(first) + x * step) % (1 << inf.RedMaskSize);
      uint32_t green = (getGreen(first) + y * step) % (1 << inf.GreenMaskSize);
      uint32_t blue = (getBlue(first) + (x + y)* step) % (1 << inf.BlueMaskSize);
      return setColor(red,green,blue);
  }
}

int set_pixel(uint16_t x, uint16_t y, uint32_t color){
  if(x >= inf.XResolution || y >= inf.YResolution) return 1;

  unsigned int pos = (x + inf.XResolution * y)*bytesPerPixel();

  //unsigned int video_mem_pos = (flip) ? ((unsigned int)front_video_mem + pos) : ((unsigned int)back_video_mem + pos);

  //memcpy((void*) ((unsigned int)front_video_mem + pos), &color, bytesPerPixel());
  
  memcpy((void*) ((unsigned int)video_mem + pos)/*(video_mem_pos)*/, &color, bytesPerPixel());
  
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(int i = 0; i < len; i++){
    if(set_pixel(x+i,y,color)) return 1;
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for(int i = 0; i < height; i++){
    if(vg_draw_hline(x,y+i,width,color)) return 1;
  }
  return 0;
}

uint16_t min(uint16_t a, uint16_t b){
  if(a < b) return a;
  return b;
}

int16_t max(int16_t a, int16_t b){
  if(a > b) return a;
  return b;
}
