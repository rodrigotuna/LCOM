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

int bytesPerPixel(){
  return (inf.BitsPerPixel + 7) >> 3;
}

void map_memory(){
  struct minix_mem_range mr;

  memset(&mr,0,sizeof(struct minix_mem_range));

  unsigned int vram_base = inf.PhysBasePtr;  /* VRAM's physical addresss */
  unsigned int vram_size = inf.XResolution * inf.YResolution * bytesPerPixel();

  int r;
  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

/* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");

}

uint32_t getRed(uint32_t color){
  return (color >> inf.RedFieldPosition) & (BIT(inf.RedMaskSize + 1) - 1);
}

uint32_t getBlue(uint32_t color){
  return (color >> inf.BlueFieldPosition) & (BIT(inf.BlueMaskSize + 1) - 1);
}

uint32_t getGreen(uint32_t color){
  return (color >> inf.GreenFieldPosition) & (BIT(inf.GreenMaskSize + 1) - 1);
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

  memcpy((void*)((unsigned int)video_mem + pos), &color, bytesPerPixel());
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

int free_mem_map(){
  return lm_free(&map);
}
