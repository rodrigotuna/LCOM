#pragma once

#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <minix/sysutil.h>

#include <stdint.h>
#include <stdbool.h>

#include "i8042.h"

/** @defgroup kbc kbc
 * @{
 *
 * Functions for programming the kbc
 */
/**
 * @brief Issues a command to the kbc
 * 
 * @param cmd command to be issued
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbc_issue_cmd)(uint8_t cmd);

/**
 * @brief Issues an argument to the kbc
 * 
 * @param cmd command to be issued
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbc_issue_arg)(uint8_t cmd);

/**
 * @brief Reads a byte from the kbv
 * 
 * @param data byte to be read
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbc_read)(uint8_t *data);

/**
 * @brief Restores the interrupts of the kbc
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int (kbc_restore)();

/**
 * @brief Reads a command from the kbc
 * 
 * @param cmd command to be read
 * @return Return 0 upon success and non-zero otherwise
 */
int (kbc_read_cmd)(uint8_t *cmd);

/**
 * @brief Writes a command to the kbc
 * 
 * @param cmd command to be written
 * @return Return 0 upon success and non-zero otherwise
 */
int (kbc_write_cmd)(uint8_t cmd);
/**@}*/
