#pragma once

#include "uart_macros.h"
#include "utilities.h"

#include <stdint.h>

int uart_hook_id;
queue_t *reciever;

/** @defgroup uart uart
 * @{
 * Functions for programming the uart
 */
/**
 * @brief Initializes the uart
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_init();

/**
 * @brief Resets the uart
 */
void uart_reset();

/**
 * @brief Cleans the the fifo's
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_clean();

/**
 * @brief Subscribes the interrupts of the uart
 * 
 * @param bit_no variable that will store the uart's irq line
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_subscribe_int(uint8_t * bit_no);

/**
 * @brief Unsubscribes uart interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_unsubscribe_int();

/**
 * @brief Reads from a uart port
 * 
 * @param port port to read from
 * @param arg variable that will store what is read
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_read_from_port(uint8_t port, uint8_t * arg);

/**
 * @brief Writes to a uart port
 * 
 * @param port port to write to
 * @param arg what to write in the port
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_write_to_port(uint8_t port, uint8_t arg);

/**
 * @brief Sends a char to the other computer
 * 
 * @param c char to send
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_send_char(uint8_t c);

/**
 * @brief Sends a string to the other computer
 * 
 * @param s string to send
 * @param sz size of the string
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_send_string(uint8_t *s, int sz);

/**
 * @brief Reads a fifo
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int uart_read_fifo();

/**
 * @brief Uart's interrupt handler
 */
void uart_ih();
/**@}*/
