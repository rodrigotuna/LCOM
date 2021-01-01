#include "rtc.h"

bool alarm_int = false;

int rtc_subscribe_int(uint8_t *bit_no){
  *bit_no = RTC_IRQ;  
  rtc_hook_id = *bit_no;
  if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &rtc_hook_id) != OK) return 1;
  return 0;
}

int rtc_unsubscribe_int(){
  if(sys_irqdisable(&rtc_hook_id)) return 1;
  if(sys_irqrmpolicy(&rtc_hook_id) != OK) return 1;
  return 0;
}

int rtc_write(uint8_t cmd, uint8_t stat){
  if(sys_outb(RTC_ADDR_REG, cmd)) return 1;
  if(sys_outb(RTC_DATA_REG,stat)) return 1;
  return 0;
}

int rtc_enable_int(uint8_t flag){
  uint8_t stat;
  if(rtc_read_status(REG_B,&stat)) return 1;
  stat |= flag;
  if(rtc_write(REG_B,stat)) return 1;
  return 0;
}

int rtc_disable_int(uint8_t flag){
  uint8_t stat;
  if(rtc_read_status(REG_B,&stat)) return 1;
  stat &= ~flag;
  if(rtc_write(REG_B,stat)) return 1;
  return 0;
}

int rtc_read_status(uint8_t cmd, uint8_t * stat){
  if(sys_outb(RTC_ADDR_REG,cmd)) return 1;
  if(util_sys_inb(RTC_DATA_REG,stat)) return 1;
  return 0;
}

int rtc_read_date(uint8_t cmd, uint8_t * data){
  uint8_t stat;
  if(rtc_read_status(REG_A, &stat)) return 1;
  if((stat & UIP) == 0){
    if(sys_outb(RTC_ADDR_REG,cmd)) return 1;
    if(util_sys_inb(RTC_DATA_REG, data)) return 1;
  }
  return 0;
}

int rtc_get_date(uint8_t * date){
  uint8_t seconds, minutes, hour, day, month, year;

  if(rtc_read_date(SECONDS,&seconds)) return 1;
  if(rtc_read_date(MINUTES,&minutes)) return 1;
  if(rtc_read_date(HOUR,&hour)) return 1;
  if(rtc_read_date(DAY,&day)) return 1;
  if(rtc_read_date(MONTH,&month)) return 1;
  if(rtc_read_date(YEAR,&year)) return 1;

  date[2] = bcd_to_int(seconds);
  date[1] = bcd_to_int(minutes);
  date[0] = bcd_to_int(hour);
  date[3] = bcd_to_int(day);
  date[4] = bcd_to_int(month);
  date[5] = bcd_to_int(year);

  return 0;
}

int rtc_set_alarm(uint8_t tseconds){
  uint8_t date[6];
  if(rtc_get_date(date)) return 1;

  int hours, minutes, seconds;
  seconds = date[0] * 3600 + date[1] * 60 + date[2] + tseconds;
  
  hours = (seconds / 3600) % 24;
  minutes = ((seconds % 3600) / 60) % 60;
  seconds %= 60;

  seconds = int_to_bcd(seconds);
  minutes = int_to_bcd(minutes);
  hours = int_to_bcd(hours);

  if(rtc_write(SECONDS_ALARM,seconds)) return 1;
  if(rtc_write(MINUTES_ALARM,minutes)) return 1;
  if(rtc_write(HOUR_ALARM,hours)) return 1;

  return 0;

}

void rtc_ih(){
  uint8_t stat;
  if(rtc_read_status(REG_C,&stat)) return;

  if(stat & UF) return;
  if(stat & AF) alarm_int = true;
  if(stat & PF) return;
}


uint8_t bcd_to_int(uint8_t value){
  return (value >> 4 )*10 + (value & 0x0F);
} 

uint8_t int_to_bcd(uint8_t value){
  return ((value / 10) << 4) | (value % 10);
}

