#pragma once

#include <lcom/lcf.h>

/** @defgroup mouse_macros mouse_macros
 * @{
 *
 * Constants for programming the mouse
 */

#define MOUSE_IRQ 12 /**< @brief  Mouse IRQ line */

/*Package first byte macros*/
#define L_BUTTON BIT(0) /**< @brief  Left button pressed */
#define R_BUTTON BIT(1) /**< @brief  Right button pressed */
#define M_BUTTON BIT(2) /**< @brief  Middle button pressed */
#define MSB_X_DELTA BIT(4) /**< @brief  MSB of x-delta */
#define MSB_Y_DELTA BIT(5) /**< @brief  MSB of y-delta */
#define X_OVFL BIT(6) /**< @brief Overflow in x_delta*/
#define Y_OVFL BIT(7) /**< @brief Overflow in y_delta*/

/*mouse commands*/
#define DIS_MOUSE 0xA7 /**< @brief Diable mouse*/
#define EN_MOUSE 0xA8 /**< @brief Enable mouse*/
#define CHECK_MOUSE_INT 0xA9 /**< @brief Check mouse interrupts*/
#define WRITE_B_MOUSE 0xD4 /**< @brief Write byte to mouse*/


/*mouse args*/
#define DIS_DATA_REP 0xF5 /**< @brief Disable data report*/
#define EN_DATA_REP 0xF4 /**< @brief Enable data report*/
#define READ_DATA 0xEB /**< @brief Read data*/
#define SET_STREAM_MODE 0xEA /**< @brief Set stream mode*/

#define ACK 0xFA /**< @brief Acknowledge*/
#define NACK 0xFE /**< @brief Not acknowledge (resend)*/
#define ERROR 0xFC /**< @brief Error*/
/**@}*/
