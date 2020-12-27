#pragma once
#include <lcom/lcf.h>

#include <stdint.h>

int (util_get_LSB)(uint16_t val, uint8_t *lsb);

int (util_get_MSB)(uint16_t val, uint8_t *msb);

int (util_sys_inb)(int port, uint8_t *value);

uint16_t min(uint16_t a, uint16_t b);

int16_t max(int16_t a, int16_t b);

struct queue{
  uint8_t * arr;
  uint8_t sz;
};

typedef struct queue queue_t;

queue_t * create_queue();

void destroy_queue(queue_t * queue);

void push(queue_t *q, uint8_t c);

uint8_t top(queue_t *q);

void pop(queue_t *q);

bool empty(queue_t *q);

void int_to_char(int value, char * str);
