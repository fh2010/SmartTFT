#include "SEGGER_RTT.h"
#include "device_itl9341_driver.h"
#include "chip_driver_lcd.h"
#include "chip_driver_systick.h"
int main(void)
{
	SEGGER_RTT_WriteString(0,"hello world\r\n");
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	chip_driver_systick_init();
	device_itl9341_init();
	while(1)
	{
		
	}
}


