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

/** @defgroup video video
 * @{
 *
 * Functions for programming the video card
 */

/**
 * @brief Gets the information about a graphic mode
 * 
 * @param mode indicates the specific mode
 * @return Return 0 upon success and non-zero otherwise
 */
int video_get_inf(uint16_t mode);

/**
 * @brief Initializes a specific mode
 * 
 * @param mode indicates specific mode
 *@return Return 0 upon success and non-zero otherwise
 */
int video_init_mode(uint16_t mode);

/**
 * @brief Alternates between buffers calling the vbe
 */
void page_flipping();

/**
 * @brief Maps the memory of the video card region
 */
void map_memory();

/**
 * @brief Indicates the number of bytes per Pixel
 * 
 * @return The number of bytes per pixel
 */
int bytesPerPixel();

/**
 * @brief Changes the color of a pixel to a specified one
 * 
 * @param x x-axis position of the pixel to be changed
 * @param y y-axis position of the pixel to be changed
 * @param color color to be changed to
 * @return Return 0 upon success and non-zero otherwise
 */
int set_pixel(uint16_t x, uint16_t y, uint32_t color);
/**@}*/
