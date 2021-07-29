#include "chip_driver_systick.h"

static uint32_t chip_driver_systick_us = 0;
static uint32_t chip_driver_systick_ms = 0;



void chip_driver_systick_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	chip_driver_systick_us=168/8;	 
	chip_driver_systick_ms=(uint16_t)chip_driver_systick_us*1000; //每个ms需要的systick时钟数   
}

void chip_driver_systick_delay_us(uint32_t us)
{
	uint32_t midtime;	    	 
	SysTick->LOAD=us*chip_driver_systick_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //开始倒数 
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));  //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	//每个ms需要的systick时钟数   
}

void chip_driver_systick_delay_ms(uint32_t ms)
{
	uint32_t midtime;	    	 
	SysTick->LOAD=ms*chip_driver_systick_ms; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //开始倒数 
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));  //等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	//每个ms需要的systick时钟数   
}


