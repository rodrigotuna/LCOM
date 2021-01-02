#pragma once

/** @defgroup uart_macros uart_macros
 * @{
 *
 * Constants for programming the UART
 */
/* IRQ LINES*/
#define COM1_IRQ 4
#define COM2_IRQ 3

/*ADDRESSES*/
#define COM1_BASE_ADDR 0x3F8
#define COM2_BASE_ADDR 0x2F8

#define UART_DELAY 1000

#define RBR 0
#define THR 0
#define IER 1
#define IIR 2
#define FCR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6
#define SR  7

#define DDL 0
#define DLM 1

/*LSR*/
#define R_READY BIT(0)
#define OR_ERR BIT(1)
#define PAR_ERR BIT(2)
#define FRAM_ERR BIT(3)
#define BREAK_INT BIT(4)
#define TRANS_HOLD_EMPTY BIT(5)
#define TRANS_EMPTY BIT(6)

/*IIR*/
#define SER_NO_INT_PEND BIT(0)
#define INT_ID (BIT(1) | BIT(2) | BIT(3))
#define SER_RX_INT BIT(2)
#define SER_TX_INT BIT(1)
#define SER_RLS_INT (BIT(1) | BIT(2))
#define SER_CHAR_TO_INT (BIT(2) | BIT(3))

/*LCR*/
#define BIT_NO_8 BIT(1) | BIT(0)
#define BIT_STOP_2 BIT(2)
#define EVEN_PAR BIT(3) | BIT(4)

/*IER*/
#define REC_DATA_AVAIL_INT BIT(0)
#define TRANS_EMPTY_INT BIT(1)
#define RLS_INT BIT(2)

/*FCR*/
#define EN_FIFO BIT(0)
#define EMPTY_RX BIT(1)
#define EMPTY_TX BIT(2)
#define TRIG_LEVEL_8 BIT(7)
/**@}*/
