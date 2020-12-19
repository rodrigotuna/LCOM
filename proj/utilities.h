#include <lcom/lcf.h>

#include <stdint.h>

int (util_get_LSB)(uint16_t val, uint8_t *lsb);

int (util_get_MSB)(uint16_t val, uint8_t *msb);

int (util_sys_inb)(int port, uint8_t *value);

uint16_t min(uint16_t a, uint16_t b);

int16_t max(int16_t a, int16_t b);
