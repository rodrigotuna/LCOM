#pragma once

#include <lcom/lcf.h>

#include <stdint.h>

#include "video_macros.h"

vbe_mode_info_t inf;
static mmap_t map;
static void *video_mem;
xpm_image_t img;
uint8_t *img_map;

int video_get_inf(uint16_t mode);

int video_init_mode(uint16_t mode);

void map_memory();

int bytesPerPixel();

uint32_t getRed(uint32_t color);

uint32_t getBlue(uint32_t color);

uint32_t getGreen(uint32_t color);

uint32_t setColor(uint32_t red, uint32_t green, uint32_t blue);

uint32_t new_color(uint16_t x, uint16_t y, uint8_t no_rectangles, uint32_t first, uint8_t step);

int set_pixel(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

void free_mem_map();

void load_xpm(xpm_map_t xpm);

int display_xpm(uint16_t x, uint16_t y);

int move(xpm_map_t xpm, uint16_t *xi, uint16_t *yi, uint16_t xf, uint16_t yf, int16_t speed);

uint16_t min(uint16_t a, uint16_t b);

int16_t max(int16_t a, int16_t b);
