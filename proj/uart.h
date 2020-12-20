#pragma once

#include "uart_macros.h"

#include <stdint.h>

int uart_hook_id;

int uart_subscribe_int(uint8_t * bit_no);

int uart_unsubscribe_int();

int uart_read_from_port(uint8_t port, uint8_t * arg);

int uart_write_to_port(uint8_t port, uint8_t arg);

void uart_ih();
