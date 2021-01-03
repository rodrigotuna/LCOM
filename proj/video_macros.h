#pragma once

#include <lcom/lcf.h>

/** @defgroup video_macros video_macros
 * @{
 *
 * Constants for programming the video card
 */
#define VBE_MODE_INFO 0x4F01
#define VBE_MODE 0x4F02
#define VBE_SET_GET_DISPLAY_START 0x4F07
#define SET_DISPLAY_VERTICAL_RETRACE 0x80
#define PIXEL_POS 0
#define LIN_FRAME_BUFF BIT(14)

#define BIOS_VIDEO_SERV 0x10
#define VBE_CALL 0x4F

#define MODE 0x115
/**@}*/
