#include "utilities.h"

int (util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb == NULL) return 1;

  *lsb = val;
  return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) return 1;

  *msb = val >> 8;
  return 0;
}

#ifdef LAB3
  uint32_t sys_counter = 0;
 #endif

int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL) return 1;

  uint32_t var;
  
  if(sys_inb(port,&var) != OK) return 1;

  *value = var;
  #ifdef LAB3
    sys_counter++;
  #endif
  return 0;
}

uint16_t min(uint16_t a, uint16_t b){
  if(a < b) return a;
  return b;
}

int16_t max(int16_t a, int16_t b){
  if(a > b) return a;
  return b;
}
