#pragma once
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "video_macros.h"

vbe_mode_info_t inf;
static mmap_t map;
static void *front_video_mem, *back_video_mem, *video_mem;

int video_get_inf(uint16_t mode);

int video_init_mode(uint16_t mode);

void page_flipping();

void map_memory();

int bytesPerPixel();

int set_pixel(uint16_t x, uint16_t y, uint32_t color);
