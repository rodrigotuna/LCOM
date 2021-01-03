#pragma once

#include <lcom/lcf.h>

/** @defgroup video_macros video_macros
 * @{
 *
 * Constants for programming the video card
 */
#define VBE_MODE_INFO 0x4F01              /**< @brief VBE mode info */
#define VBE_MODE 0x4F02                   /**< @brief Set VBE mode */
#define VBE_SET_GET_DISPLAY_START 0x4F07  /**< @brief  VBE set/get display start*/
#define SET_DISPLAY_VERTICAL_RETRACE 0x80 /**< @brief VBE set display vertical retrace */
#define PIXEL_POS 0                       /**< @brief  Pixel position*/
#define LIN_FRAME_BUFF BIT(14)            /**< @brief  Linear frame buffer*/

#define BIOS_VIDEO_SERV 0x10  /**< @brief BIOS video service */
#define VBE_CALL 0x4F         /**< @brief VBE call */

#define MODE 0x115 /**< @brief Mode used in the project */
/**@}*/
