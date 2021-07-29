#ifndef  __CHIP_DRIVER_SYSTICK_H_
#define  __CHIP_DRIVER_SYSTICK_H_

#include "stm32f4xx.h"

extern void chip_driver_systick_init(void);
extern void chip_driver_systick_delay_us(uint32_t us);
extern void chip_driver_systick_delay_ms(uint32_t ms);
#endif

