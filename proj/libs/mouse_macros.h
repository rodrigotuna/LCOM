#pragma once

#include <lcom/lcf.h>

/** @defgroup mouse_macros mouse_macros
 * @{
 *
 * Constants for programming the mouse
 */

#define MOUSE_IRQ 12

/*Package first byte macros*/
#define L_BUTTON BIT(0)
#define R_BUTTON BIT(1)
#define M_BUTTON BIT(2)
#define MSB_X_DELTA BIT(4)
#define MSB_Y_DELTA BIT(5)
#define X_OVFL BIT(6)
#define Y_OVFL BIT(7)

/*mouse commands*/
#define DIS_MOUSE 0xA7
#define EN_MOUSE 0xA8
#define CHECK_MOUSE_INT 0xA9
#define WRITE_B_MOUSE 0xD4


/*mouse args*/
#define DIS_DATA_REP 0xF5
#define EN_DATA_REP 0xF4
#define READ_DATA 0xEB
#define SET_STREAM_MODE 0xEA

#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC
/**@}*/
