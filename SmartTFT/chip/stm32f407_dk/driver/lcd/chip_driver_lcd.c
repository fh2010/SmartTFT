#include "chip_driver_lcd.h"

static void chip_driver_lcd_delay_us(uint16_t us)
{
	while(us--);
}

void chip_driver_lcd_write_reg(uint16_t reg, uint16_t data)
{	
	LCD_CMD = reg;		  
	LCD_DATA = data;   		 
}

uint16_t chip_driver_lcd_read_reg(uint16_t reg)
{
	LCD_CMD = reg;
	chip_driver_lcd_delay_us(10);
	return (LCD_DATA);
}

void chip_driver_lcd_set_cmd(uint16_t cmd)
{
	LCD_CMD = cmd;
}
void chip_driver_lcd_set_data(uint16_t data)
{
	LCD_DATA = data;
}

