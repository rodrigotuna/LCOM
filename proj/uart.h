#pragma once

#include "uart_macros.h"
#include "utilities.h"

#include <stdint.h>

int uart_hook_id;
queue_t *reciever;

int uart_init();

void uart_reset();

int uart_subscribe_int(uint8_t * bit_no);

int uart_unsubscribe_int();

int uart_read_from_port(uint8_t port, uint8_t * arg);

int uart_write_to_port(uint8_t port, uint8_t arg);

int uart_send_char(uint8_t c);

int uart_send_string(uint8_t *s, int sz);

int uart_read_fifo();

void uart_ih();
