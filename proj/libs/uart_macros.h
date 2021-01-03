#pragma once

/** @defgroup uart_macros uart_macros
 * @{
 *
 * Constants for programming the UART
 */
/* IRQ LINES*/
#define COM1_IRQ 4 /**< @brief COM1 IRQ line */
#define COM2_IRQ 3 /**< @brief COM2 IRQ line */

/*ADDRESSES*/
#define COM1_BASE_ADDR 0x3F8 /**< @brief COM1 base address*/
#define COM2_BASE_ADDR 0x2F8 /**< @brief COM2 base address*/

#define UART_DELAY 1000 /**< @brief Uart delay*/

#define RBR 0 /**< @brief Reciever buffer register*/
#define THR 0 /**< @brief Transmiter Holding register*/
#define IER 1 /**< @brief Interrupt enable register*/
#define IIR 2 /**< @brief Interrupt identification register*/
#define FCR 2 /**< @brief FIFO control register*/
#define LCR 3 /**< @brief Line control register*/
#define MCR 4 /**< @brief Modem control register*/
#define LSR 5 /**< @brief Line Status register*/
#define MSR 6 /**< @brief Modem status register*/
#define SR  7

#define DDL 0 /**< @brief Divisor latch lsb*/
#define DLM 1 /**< @brief Divisor latch msb*/

/*LSR*/
#define R_READY BIT(0)          /**< @brief Reciever ready*/
#define OR_ERR BIT(1)           /**< @brief Overrun error*/
#define PAR_ERR BIT(2)          /**< @brief Parity error*/
#define FRAM_ERR BIT(3)         /**< @brief Framing error*/
#define BREAK_INT BIT(4)        /**< @brief Break interrupt*/
#define TRANS_HOLD_EMPTY BIT(5) /**< @brief Transmiter holding register empty */
#define TRANS_EMPTY BIT(6)      /**< @brief Transmiter empty*/

/*IIR*/
#define SER_NO_INT_PEND BIT(0)            /**< @brief No interrupt pending*/
#define INT_ID (BIT(1) | BIT(2) | BIT(3)) /**< @brief Interrupt ID*/
#define SER_RX_INT BIT(2)                 /**< @brief RX interrupt*/
#define SER_TX_INT BIT(1)                 /**< @brief TX interrupt*/
#define SER_RLS_INT (BIT(1) | BIT(2))     /**< @brief RLS interrupt*/
#define SER_CHAR_TO_INT (BIT(2) | BIT(3)) /**< @brief Character timeout interrupt*/

/*LCR*/
#define BIT_NO_8 BIT(1) | BIT(0) /**< @brief 8 bits per char */
#define BIT_STOP_2 BIT(2)        /**< @brief 2 stop bits*/
#define EVEN_PAR BIT(3) | BIT(4) /**< @brief Even parity*/

/*IER*/
#define REC_DATA_AVAIL_INT BIT(0) /**< @brief Enable Data vailable interrupt */
#define TRANS_EMPTY_INT BIT(1)    /**< @brief Enable Transmiter empty interrupt */
#define RLS_INT BIT(2)            /**< @brief Enable RLS change interrupt */

/*FCR*/
#define EN_FIFO BIT(0) /**< @brief Enable fifo */
#define EMPTY_RX BIT(1) /**< @brief Empty rx_fifo */
#define EMPTY_TX BIT(2) /**< @brief Empty tx_fifo */
#define TRIG_LEVEL_8 BIT(7) /**< @brief Trigger level of 8 bits */
/**@}*/
