#ifndef _LCOM_I8042H
#define _LCOM_I8042H

#include <lcom/lcf.h>

#define KB_IRQ 1
#define DELAY_US    20000


#define KBC_ST_REG  0x64
#define KBC_CMD_REG 0x64
#define KBC_OUT_BUF 0x60
#define KBC_ARG_REG 0x60 

#define READ_CMD_B   0x20    // Reads command byte 
#define WRITE_CMD_B  0x60    // Writes command byte (must pass command byte as argument to port 0x60
#define CHECK_KBC    0xAA    // Self-test: returns 0x55 if OK, returns 0xFC if error 
#define CHECK_KB_IFC 0xAB    // Check Keyboard interface : returns 0 if OK 
#define DISABLE_KBD  0xAD    // Disables Keyboard interface 
#define ENABLE_KBS   0xAE    // Enables Keyboard interface 

#define KBC_OBF BIT(0)
#define KBC_IBF  BIT(1)
#define KBC_AUX BIT(5)
#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)

#define KB_INT_DIS BIT(4)
#define KB_INTERR_EN BIT(0)

#define BREAK_CODE BIT(7)

#define ESC_BREAK_CODE 0x81

#define TWO_BYTE_CODE 0xE0


#endif
