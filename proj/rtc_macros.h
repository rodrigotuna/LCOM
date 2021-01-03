#pragma once

/** @defgroup RTC Macros
 * @{
 *
 * Constants for programming the RTC
 */

/* IRQ LINES*/
#define RTC_IRQ 8 /**< @brief RTC IRQ line */

/*ADDRESSES*/
#define RTC_ADDR_REG 0x70 /**< @brief RTC Adress Register */
#define RTC_DATA_REG 0x71 /**< @brief RTC Data Register */

#define SECONDS 0 /**< @brief RTC Seconds Register */
#define SECONDS_ALARM 1 /**< @brief RTC Seconds Alarm Register */
#define MINUTES 2 /**< @brief RTC Minutes Register */
#define MINUTES_ALARM 3 /**< @brief RTC Minutes Alarm Register */
#define HOUR 4 /**< @brief RTC Hour Register */
#define HOUR_ALARM 5 /**< @brief RTC Hour Alarm Register */
#define DAY 7 /**< @brief RTC Day Register */
#define MONTH 8 /**< @brief RTC Month Register */
#define YEAR 9 /**< @brief RTC Year Register */

#define REG_A 10 /**< @brief RTC Control Register A */
#define REG_B 11 /**< @brief RTC Control Register B */
#define REG_C 12 /**< @brief RTC Control Register C */

/*REGISTER A*/
#define UIP BIT(7) /**< @brief Update in progress */

/*REGISTER B*/
#define SET BIT(7) /**< @brief Inhibits updates */
#define PIE BIT(6) /**< @brief Periodic interrupts enabled */
#define AIE BIT(5) /**< @brief Alarm interrupts enabled */
#define UIE BIT(4) /**< @brief Update interrupts enabled */
#define SQWE BIT(5) /**< @brief Square-wave generation */

/*REGISTER C*/
#define IRQF BIT(7) /**< @brief IRQ line active*/
#define PF BIT(6) /**< @brief Periodic interrupt pending */
#define AF BIT(5) /**< @brief Alarm interrupt pending */
#define UF BIT(4) /**< @brief Update interrupt pending */

/**@}*/
