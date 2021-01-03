#ifndef _LCOM_I8042H
#define _LCOM_I8042H

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 Keyboard.
 */
#define KB_IRQ 1            /**< @brief  Keyboard IRQ line */
#define DELAY_US  20000     /**< @brief  KBC delay*/


#define KBC_ST_REG  0x64  /**< @brief  KBC status register */
#define KBC_CMD_REG 0x64  /**< @brief  KBC command register */
#define KBC_OUT_BUF 0x60  /**< @brief  KBC output buffer*/
#define KBC_ARG_REG 0x60  /**< @brief  KBC argument register */

#define READ_CMD_B   0x20    /**< @brief  Reads command byte */
#define WRITE_CMD_B  0x60    /**< @brief Writes command byte */
#define CHECK_KBC    0xAA    /**< @brief Self-test: returns 0x55 if OK, returns 0xFC if error */
#define CHECK_KB_IFC 0xAB    /**< @brief Check Keyboard interface : returns 0 if OK */
#define DISABLE_KBD  0xAD    /**< @brief Disables Keyboard interface */
#define ENABLE_KBS   0xAE    /**< @brief Enables Keyboard interface */

#define KBC_OBF BIT(0)     /**< @brief KBC output buffer full*/
#define KBC_IBF  BIT(1)    /**< @brief KBC input buffer full*/
#define KBC_AUX BIT(5)     /**< @brief KBC from mouse*/
#define KBC_PAR_ERR BIT(7) /**< @brief KBC parity error*/
#define KBC_TO_ERR BIT(6)  /**< @brief KBC timeout*/

#define KB_INT_DIS BIT(4)   /**< @brief Disable keyboard interrupts*/
#define KB_INTERR_EN BIT(0) /**< @brief Enable keyboard interrupts*/

#define BREAK_CODE BIT(7)  /**< @brief Break code bit */

#define ESC_BREAK_CODE 0x81 /**< @brief ESC break code*/
#define W_MAKE_CODE 0x11  /**< @brief W make code*/
#define W_BREAK_CODE 0x91 /**< @brief W break code*/
#define A_MAKE_CODE 0x1E  /**< @brief A make code*/
#define A_BREAK_CODE 0x9E /**< @brief A break code*/
#define S_MAKE_CODE 0x1F  /**< @brief S make code*/
#define S_BREAK_CODE 0x9F /**< @brief S break code*/
#define D_MAKE_CODE 0x20  /**< @brief D make code*/
#define D_BREAK_CODE 0xA0 /**< @brief D break code*/


#define TWO_BYTE_CODE 0xE0 /**< @brief First byte of a two byte code*/


#endif
/**@}*/
