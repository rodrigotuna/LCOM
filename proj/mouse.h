#pragma once

#include <stdint.h>
#include <lcom/lcf.h>

#include "mouse_macros.h"

int mouse_hook_id;
uint8_t mouse_packet[3];
uint8_t mouse_count;

/** @defgroup mouse mouse
 * @{
 *
 * Functions for programming the mouse
 */
/**
 * @brief Represents the events of the mouse
 */
typedef enum{PRESSED_LB, MOVEMENT} click_ev;

/**
 * @brief Subscribes the interrupts of the mouse
 * 
 * @param bit_no variable that will store the mouse's irq line
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubsribes the interrupts of the keyboard
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_unsubscribe_int();

/**
 * @brief Constructs a packet with the mouse information
 * 
 * @return Packet with mouse information
 */
struct packet make_packet();

/**
 * @brief Mouse's interrupt handler
 */
void (mouse_ih)(void);

/**
 * @brief Reads one byte from the mouse
 * 
 * @param data variable where the byte will be stored
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_read(uint8_t *data);

/**
 * @brief Sets an argument to the mouse
 * 
 * @param arg argument to be set
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_set_arg(uint8_t arg);

/**
 * @brief Processes an event of hte mouse
 * 
 * @param packet struct with the mouse information
 * @return Return 0 upon success and non-zero otherwise
 */
click_ev process_event(struct packet * packet);
 /**@}*/
