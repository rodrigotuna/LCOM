#pragma once
#include <lcom/lcf.h>

#include <stdint.h>

/** @defgroup utilities utilities
 * @{
 *
 * Functions with utility functions
 */

/**
 * @brief Gets the LSB of a 16-bit number
 * 
 * @param val 16-bit number
 * @param lsb variable where the LSB will be stored
 * @return Return 0 upon success and non-zero otherwise
 */
int (util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Gets the MSB of a 16-bit number
 * 
 * @param val 16-bit number
 * @param msb variable where the MSB will be stored
 * @return Return 0 upon success and non-zero otherwise
 */
int (util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 * @brief Wrapper of function sys_inb()
 * 
 * @param port port to read from
 * @param value variable where the value will be stored
 * @return Return 0 upon success and non-zero otherwise
 */
int (util_sys_inb)(int port, uint8_t *value);

/**
 * @brief Gets the smallest of 2 numbers
 * 
 * @param a number to be compared
 * @param b number to be compared
 * @return The smallest number
 */
uint16_t min(uint16_t a, uint16_t b);

/**
 * @brief Gets the biggest of 2 numbers
 * 
 * @param a number to be compared
 * @param b number to be compared
 * @return The biggest number
 */
int16_t max(int16_t a, int16_t b);

/**
 * @brief struct that represents a queue
 */
struct queue{
  uint8_t * arr;
  uint8_t sz;
};

typedef struct queue queue_t;

/**
 * @brief Constructor
 * 
 * @return Pointer to the queue created
 */
queue_t * create_queue();

/**
 * @brief Destructor
 * 
 * @param queue object to be destroyed
 */
void destroy_queue(queue_t * queue);

/**
 * @brief Adds a variable to the queue
 * 
 * @param q queue object
 * @param c variable to add
 */
void push(queue_t *q, uint8_t c);

/**
 * @brief Gets the element on top of the queue
 * 
 * @param q queue object
 * @return Element on top of the queue
 */
uint8_t top(queue_t *q);

/**
 * @brief Pops the first element of the queue
 * 
 * @param q queue object
 */
void pop(queue_t *q);

/**
 * @brief Checks if a queue is empty
 * 
 * @param q queue object
 * @return True if queue is empty, false otherwise
 */
bool empty(queue_t *q);

/**
 * @brief Gets a string of an integer
 * 
 * @param value integer to be converted
 * @param str where the string will be placed
 */
void int_to_char(int value, char * str);
/**@}*/
