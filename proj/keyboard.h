#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <minix/sysutil.h>

#include <stdint.h>
#include <stdbool.h>

#include "i8042.h"
#include "kbc.h"

int hook_id;
uint8_t scancode[2];
uint8_t size;
bool code_completed;

/** @defgroup kbc kbc
 * @{
 *
 * Functions for programming the kbc
 */

/**
 * @brief Subscribes the interrupts of the keyboard
 * 
 * @param bit_no variable that will store the keyboard's irq line
 * @return Return 0 upon success and non-zero otherwise
 */
int(kb_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubsribes the interrupts of the keyboard
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int(kb_unsubscribe_int)();

/**
 * @brief Keyboard's interrupt handler
 */
void (kbc_ih)(void);
/**@}*/
