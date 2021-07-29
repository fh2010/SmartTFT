#include "chip_driver_systick.h"

static uint32_t chip_driver_systick_us = 0;
static uint32_t chip_driver_systick_ms = 0;



void chip_driver_systick_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	chip_driver_systick_us=168/8;	 
	chip_driver_systick_ms=(uint16_t)chip_driver_systick_us*1000; //ÿ��ms��Ҫ��systickʱ����   
}

void chip_driver_systick_delay_us(uint32_t us)
{
	uint32_t midtime;	    	 
	SysTick->LOAD=us*chip_driver_systick_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //��ʼ���� 
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));  //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	//ÿ��ms��Ҫ��systickʱ����   
}

void chip_driver_systick_delay_ms(uint32_t ms)
{
	uint32_t midtime;	    	 
	SysTick->LOAD=ms*chip_driver_systick_ms; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;    //��ʼ���� 
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));  //�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	//ÿ��ms��Ҫ��systickʱ����   
}


