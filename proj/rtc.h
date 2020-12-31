#pragma once

#include <lcom/lcf.h>

#include "rtc_macros.h"

int rtc_subscribe_int(uint8_t *bit_no);

int rtc_unsubscribe_int();

int rtc_enable_int(uint8_t flag);

int rtc_disable_int(uint8_t flag);

int rtc_write(uint8_t cmd, uint8_t stat);

int rtc_read_status(uint8_t cmd, uint8_t * stat);

int rtc_read_date(uint8_t cmd, uint8_t * data);

int rtc_get_date(uint8_t * date);

int rtc_set_alarm(uint8_t tseconds);

uint8_t bcd_to_int(uint8_t value);

uint8_t int_to_bcd(uint8_t value);
