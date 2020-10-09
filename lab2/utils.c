#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
    if(lsb == NULL){
      return 1;
    }

    uint16_t mask = 0x00FF;

    *lsb = val & mask;
    return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL){
    return 1;
  }

  uint16_t mask = 0xFF00;
  
  *msb = (val & mask) >> 8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
