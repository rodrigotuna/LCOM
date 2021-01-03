#pragma once

#include <lcom/lcf.h>

#include "keyboard.h"
#include "mouse.h"
#include "video.h"
#include "rtc.h"
#include "uart.h"

/** @defgroup drivers drivers
 * @{
 * Functions for the drivers
 */

/**
 * @brief Timer IRQ set
 */
#define TIMER_IRQ_SET BIT(0)
/**
 * @brief Keyboard IRQ set
 */
#define KB_IRQ_SET BIT(1)
/**
 * @brief Mouse IRQ set
 */
#define MOUSE_IRQ_SET BIT(12)
/**
 * @brief RTC IRQ set
 */
#define RTC_IRQ_SET BIT(8)
/**
 * @brief UART IRQ set
 */
#define UART_IRQ_SET BIT(4)

/**
 * @brief Subscribes the interrupts of all drivers
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int subscribe_all();

/**
 * @brief Unsubscribes the interrupts of all drivers
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int unsubscribe_all();

/**
 * @brief Function that calls driver-recieve gets the interrupts
 * 
 * @return 32-bit unsigned integer with all interrupts
 */
uint32_t get_interrupts();

/**
 * @brief Initializes and configures all drivers
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int init_all();

/**
 * @brief Initializes and configures all drivers
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int reset_all();
/**@}*/
