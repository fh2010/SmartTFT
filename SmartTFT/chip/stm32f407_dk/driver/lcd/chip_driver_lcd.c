#include "chip_driver_lcd.h"
#include "chip_driver_systick.h"
static void chip_driver_lcd_delay_us(uint16_t us)
{
	while(us--);
}



void chip_driver_lcd_write_cmd(uint16_t cmd)
{	
	cmd = cmd;
	LCD_REG = cmd;		    		 
}

void chip_driver_lcd_write_data(uint16_t data)
{	
	data = data;
	LCD_DATA = data;		    		 
}

uint16_t chip_driver_lcd_read_data(void)
{
    return LCD_DATA;
}

void chip_driver_lcd_write_reg(uint16_t reg, uint16_t data)
{	
	chip_driver_lcd_write_cmd(reg);  
	chip_driver_lcd_write_data(data);	 
}

uint16_t chip_driver_lcd_read_reg(uint16_t reg)
{
	chip_driver_lcd_write_cmd(reg);
	chip_driver_systick_delay_us(5);
	return (LCD_DATA);
}

void chip_driver_lcd_set_cmd(uint16_t reg)
{
	LCD_REG = reg;
}
void chip_driver_lcd_set_data(uint16_t data)
{
	LCD_DATA = data;
}

