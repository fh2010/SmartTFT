#ifndef  __CHIP_DRIVER_LCD_H_
#define  __CHIP_DRIVER_LCD_H_

#include "stm32f4xx.h"


#define  REG_BASE      ((uint32_t)(0x6C000000 | 0x00001FFE))
#define  DATA_BASE     ((uint32_t)(0x6C000000 | 0x00002000))

#define  LCD_REG       ( * (__IO uint16_t *) REG_BASE )
#define  LCD_DATA      ( * (__IO uint16_t *) DATA_BASE)

extern void chip_driver_lcd_write_cmd(uint16_t cmd);
extern void chip_driver_lcd_write_data(uint16_t data);
extern uint16_t chip_driver_lcd_read_data(void);
extern void chip_driver_lcd_write_reg(uint16_t reg, uint16_t data);
extern uint16_t chip_driver_lcd_read_reg(uint16_t reg);
void chip_driver_lcd_set_cmd(uint16_t reg);
void chip_driver_lcd_set_data(uint16_t data);

#endif


