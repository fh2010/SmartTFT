#include "SEGGER_RTT.h"
#include "device_itl9341_driver.h"
#include "device_sram_driver.h"
#include "chip_driver_lcd.h"
#include "chip_driver_systick.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lcd_config.h"
#include "lv_calendar_test.h"
int main(void)
{
	SEGGER_RTT_WriteString(0,"hello world\r\n");
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	chip_driver_systick_init();
	device_itl9341_init();
	device_sram_init();
	lv_init();
	lv_port_disp_init();
	//lv_calendar_test_start();
	//lv_arc_test_start();
	lv_ex_gauge_1();
	while(1)
	{
		lv_task_handler();
		chip_driver_systick_delay_ms(5);
	}
}


