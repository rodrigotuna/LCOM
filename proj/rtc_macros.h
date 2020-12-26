#pragma once

/* IRQ LINES*/
#define RTC_IRQ 8

/*ADDRESSES*/
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define SECONDS 0
#define SECONDS_ALARM 1
#define MINUTES 2
#define MINUTES_ALARM 3
#define HOUR 4
#define HOUR_ALARM 5
#define DAY 7
#define MONTH 8
#define YEAR 9

#define REG_A 10
#define REG_B 11
#define REG_C 12

/*REGISTER A*/
#define UIP BIT(7)

/*REGISTER B*/
#define SET BIT(7)
#define PIE BIT(6)
#define AIE BIT(5)
#define UIE BIT(4)
#define SQWE BIT(5)

/*REGISTER C*/
#define IRQF BIT(7)
#define PF BIT(6)
#define AF BIT(5)
#define UF BIT(4)

