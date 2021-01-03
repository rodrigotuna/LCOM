#pragma once

#include <lcom/lcf.h>

#include "rtc_macros.h"

int rtc_hook_id;
bool alarm_int;

/** @defgroup RTC RTC
 * @{
 * Functions for the PC's Real Time Clock
 */

/**
 * @brief Subscribes RTC's interrupts
 * 
 * @param bit_no RTC's IRQ line
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes RTC's interrupts
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_unsubscribe_int();

/**
 * @brief Enables RTC's interrupts
 * 
 * @param flag Type of interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_enable_int(uint8_t flag);

/**
 * @brief Disables RTC's interrupts
 * 
 * @param flag Type of interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_disable_int(uint8_t flag);

/**
 * @brief Writes data to a certain register of the RTC
 * 
 * @param cmd register of the RTC to write on
 * @param data data byte to write to the register
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_write(uint8_t cmd, uint8_t data);

/**
 * @brief Reads the status from a certain register of the RTC
 * 
 * @param cmd register of the RTC to read from
 * @param stat status byte to read from the register
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_read_status(uint8_t cmd, uint8_t * stat);

/**
 * @brief Checks if an update is in progress, if not reads data from a certain register of the RTC
 * 
 * @param cmd register of the RTC to read from
 * @param data data byte to read from the register
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_read_date(uint8_t cmd, uint8_t * data);

/**
 * @brief Reads the year, month, day, hours, minutes and seconds from the RTC
 * 
 * @param date array that stores the date read
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_get_date(uint8_t * date);

/**
 * @brief Sets an alarm seconds from the current time on the RTC
 * 
 * @param tseconds time in seconds to set the alarm to
 * @return Return 0 upon success and non-zero otherwise
 */
int rtc_set_alarm(uint8_t tseconds);

/**
 * @brief Handles RTC interrupts
 * 
 */
void rtc_ih();

/**
 * @brief Converts value in BCD to a decimal integer
 * 
 * @param value value to be converted
 * @return Value after converting
 */
uint8_t bcd_to_int(uint8_t value);

/**
 * @brief Converts a decimal integer to BCD
 * 
 * @param value value to be converted
 * @return Value after converting
 */
uint8_t int_to_bcd(uint8_t value);
/**@}*/
