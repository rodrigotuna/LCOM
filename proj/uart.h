#pragma once

#include "uart_macros.h"
#include "utilities.h"

#include <stdint.h>

int uart_hook_id;
queue_t *transmiter;
queue_t *reciever;
uint8_t v;

int uart_init();

void uart_reset();

int uart_subscribe_int(uint8_t * bit_no);

int uart_unsubscribe_int();

int uart_read_from_port(uint8_t port, uint8_t * arg);

int uart_write_to_port(uint8_t port, uint8_t arg);

int uart_send_char(uint8_t c);

int uart_read_char(uint8_t *c);

void uart_ih();
