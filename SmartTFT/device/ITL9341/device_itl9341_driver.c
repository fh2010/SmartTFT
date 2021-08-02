#include "device_itl9341_driver.h"
#include "chip_driver_lcd.h"
#include "chip_driver_systick.h"
#include <stdbool.h>

static device_itl9341_msg_t device_itl9341_msg;
static device_itl9341_color_msg_t device_itl9341_color_msg;

static uint8_t device_itl9341_get_display_dir(void)
{
	return device_itl9341_msg.dis_dir;
}

static uint16_t device_itl9341_get_lcd_id(void)
{
	return device_itl9341_msg.lcd_id;
}

static uint16_t device_itl9341_get_lcd_backcolor(void)
{
	return device_itl9341_color_msg.lcd_back_color;
}

void device_itl9341_set_lcd_backcolor(uint16_t backcolor)
{
	device_itl9341_color_msg.lcd_back_color = backcolor;
}

static uint16_t device_itl9341_get_lcd_textcolor(void)
{
	return device_itl9341_color_msg.lcd_text_color;
}

void device_itl9341_set_lcd_textcolor(uint16_t textcolor)
{
	device_itl9341_color_msg.lcd_text_color = textcolor;
}

void device_itl9341_display_onff(bool onoroff)
{
	if(onoroff)
	{
		chip_driver_lcd_set_cmd(DEVICE_ITL9341_DISPLAY_ON);	
	}
	else
	{
		chip_driver_lcd_set_cmd(DEVICE_ITL9341_DISPLAY_OFF);	
	}
}

void device_itl9341_set_show_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	if(x1<1 || y1<1)
	{
		return;
	}
	chip_driver_lcd_set_cmd(device_itl9341_msg.setx_cmd);	
	chip_driver_lcd_set_data(x0>>8);
	chip_driver_lcd_set_data(x0&0XFF);
	chip_driver_lcd_set_data((x1-1)>>8);
	chip_driver_lcd_set_data((x1-1)&0XFF);
	chip_driver_lcd_set_cmd(device_itl9341_msg.sety_cmd);
	chip_driver_lcd_set_data(y0>>8);
	chip_driver_lcd_set_data(y0&0XFF);
	chip_driver_lcd_set_data((y1-1)>>8);
	chip_driver_lcd_set_data((y1-1)&0XFF);	
	
}
void device_itl9341_set_scan_dir(DEVICE_ITL9341_SCAN_DIR dir)
{
	uint16_t scan_data = 0;	
	uint16_t scan_reg = 0;	
	if((device_itl9341_get_display_dir() == HORIZONTAL_SCREEN) && \
		(device_itl9341_get_lcd_id() == DEVICE_ITL9341_ID))
	{
		switch(dir)
		{
			case L2R_U2D:dir = D2U_L2R;break;
			case R2L_U2D:dir = D2U_R2L;break;
			case L2R_D2U:dir = U2D_L2R;break;
			case R2L_D2U:dir = U2D_R2L;break;
			case U2D_L2R:dir = R2L_U2D;break;
			case U2D_R2L:dir = L2R_U2D;break;
			case D2U_L2R:dir = R2L_D2U;break;
			case D2U_R2L:dir = L2R_D2U;break;
		}
	}
	switch(dir)
	{
		case L2R_U2D:scan_data|=(0<<7)|(0<<6)|(0<<5);break;
		case R2L_U2D:scan_data|=(1<<7)|(0<<6)|(0<<5);break;
		case L2R_D2U:scan_data|=(0<<7)|(1<<6)|(0<<5);break;
		case R2L_D2U:scan_data|=(1<<7)|(1<<6)|(0<<5);break;
		case U2D_L2R:scan_data|=(0<<7)|(0<<6)|(1<<5);break;
		case U2D_R2L:scan_data|=(0<<7)|(1<<6)|(1<<5);break;
		case D2U_L2R:scan_data|=(1<<7)|(0<<6)|(1<<5);break;
		case D2U_R2L:scan_data|=(1<<7)|(1<<6)|(1<<5);break;
	}
	scan_reg=DEVICE_ITL9341_SCAN_DIR_REG;
	if(device_itl9341_get_lcd_id() == DEVICE_ITL9341_ID)
	{
		scan_data|=0X08;
	}		
	chip_driver_lcd_write_reg(scan_reg,scan_data);
	device_itl9341_set_show_window(0,0,device_itl9341_msg.lcd_hor,device_itl9341_msg.lcd_ver);
}

void device_itl9341_set_show_dir(uint8_t sacn_dir)
{
	uint8_t tmp = sacn_dir%2;
    if(sacn_dir>7)
    {
        return;
    }
	device_itl9341_msg.setx_cmd = DEVICE_ITL9341_SET_X;
	device_itl9341_msg.sety_cmd = DEVICE_ITL9341_SET_Y;
	device_itl9341_msg.gram_cmd = DEVICE_ITL9341_WRITE_GRAM;
	device_itl9341_msg.scan_mode = sacn_dir;
	device_itl9341_msg.dis_dir = (DEVICE_ITL9341_DISPLAY_DIR)tmp;
	if(tmp == 0)
	{
		device_itl9341_msg.lcd_hor = LCD_HEIGHT;
		device_itl9341_msg.lcd_ver = LCD_WIDHT;
		
	}
	else if(tmp == 1)
	{
		device_itl9341_msg.lcd_hor = LCD_WIDHT;
		device_itl9341_msg.lcd_ver = LCD_HEIGHT;
	}
	device_itl9341_set_scan_dir((DEVICE_ITL9341_SCAN_DIR)sacn_dir);
}

void device_itl9341_setcursor(uint16_t x_addr, uint16_t y_addr)
{
	if(device_itl9341_get_lcd_id() == DEVICE_ITL9341_ID)
	{
		chip_driver_lcd_set_cmd(device_itl9341_msg.setx_cmd);	
		chip_driver_lcd_write_data(x_addr>>8);
		chip_driver_lcd_write_data(x_addr&0XFF);
		chip_driver_lcd_write_data((device_itl9341_msg.lcd_hor-1)>>8);
		chip_driver_lcd_write_data((device_itl9341_msg.lcd_hor-1)&0XFF);
		chip_driver_lcd_set_cmd(device_itl9341_msg.sety_cmd);
		chip_driver_lcd_write_data(y_addr>>8);
		chip_driver_lcd_write_data(y_addr&0XFF);
		chip_driver_lcd_write_data((device_itl9341_msg.lcd_ver-1)>>8);
		chip_driver_lcd_write_data((device_itl9341_msg.lcd_ver-1)&0XFF);
	}
}

void device_itl9341_drawpoint(uint16_t x_addr, uint16_t y_addr)
{
	device_itl9341_setcursor(x_addr,y_addr);
	chip_driver_lcd_write_cmd(device_itl9341_msg.gram_cmd);
	chip_driver_lcd_write_data(device_itl9341_color_msg.lcd_text_color);
}

void device_itl9341_set_back_light(uint8_t back_light)
{
	chip_driver_lcd_set_cmd(0xBE);	
	chip_driver_lcd_set_data(0x05);
	chip_driver_lcd_set_data(back_light);
	chip_driver_lcd_set_data(0x01);
	chip_driver_lcd_set_data(0xFF);
	chip_driver_lcd_set_data(0x00);
	chip_driver_lcd_set_data(0x00);
}

void device_itl9341_show_clear(uint16_t color)
{
    uint32_t totalpoint = device_itl9341_msg.lcd_hor * device_itl9341_msg.lcd_ver;
	device_itl9341_color_msg.lcd_back_color = color;
	device_itl9341_setcursor(0,0);
	chip_driver_lcd_write_cmd(device_itl9341_msg.gram_cmd);
	for(uint32_t i=0;i<totalpoint;i++)
	{
		chip_driver_lcd_write_data(device_itl9341_color_msg.lcd_back_color);
	}
}

void device_itl9341_fill_color(uint16_t sx_addr, uint16_t sy_addr,uint16_t ex_addr, uint16_t ey_addr,uint16_t *color)
{
    uint16_t i,j; 
    uint16_t height,width;     
    width = ex_addr - sx_addr + 1;          
    height = ey_addr - sy_addr + 1; 
    for(i=0; i<height; i++)   
    {   
        device_itl9341_setcursor(sx_addr, sy_addr+i);     
        chip_driver_lcd_write_cmd(device_itl9341_msg.gram_cmd);    
        for(j=0; j<width; j++)
        {
            chip_driver_lcd_write_data(color[i*width+j]);
        }
    } 
}

void device_itl9341_read_lcd_id(void)
{
	uint16_t tmp = 0;
	chip_driver_lcd_write_cmd(0xD3);
	tmp = chip_driver_lcd_read_data();
	tmp = chip_driver_lcd_read_data();
	tmp = chip_driver_lcd_read_data();
	tmp <<= 8;
	tmp |= chip_driver_lcd_read_data();
	device_itl9341_msg.lcd_id = tmp;	
}

void device_itl9341_back_light_on(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_10);
}

void device_itl9341_back_light_off(void)
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_10);
}


void device_itl9341_fsmc_config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;        //PF10 推挽输出,控制背光
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;     //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);            //初始化PF10 

	GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14); 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);            //初始化  

	GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);         //PE7~15,AF OUT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);            //初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;         //PG2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);            //初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;        //PG12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      //复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;      //上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);            //初始化 

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC); 

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);  
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC); 

	GPIO_PinAFConfig(GPIOG,GPIO_PinSource2,GPIO_AF_FSMC); 
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);   

	readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //地址建立时间（ADDSET） 16个HCLK 1/168M=6ns*16=96ns	
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）
	readWriteTiming.FSMC_DataSetupTime = 60;			 //数据保存时间 60个HCLK	= 6*60=360ns
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	readWriteTiming.FSMC_CLKDivision = 0x00;
	readWriteTiming.FSMC_DataLatency = 0x00;
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 

	writeTiming.FSMC_AddressSetupTime =8;	     //地址建立时间（ADDSET）9个HCLK =54ns 
	writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间 
	writeTiming.FSMC_DataSetupTime = 7;		     //数据保存时间 6ns*9个HCLK=54ns
	writeTiming.FSMC_BusTurnAroundDuration = 0x00;
	writeTiming.FSMC_CLKDivision = 0x00;
	writeTiming.FSMC_DataLatency = 0x00;
	writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;  
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;   //数据宽度为16bit   
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	 //写使能
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;      //读写使用不同的时序
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;     //读写时序
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;             //写时序
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  //使能Bank1
}

void device_itl9341_init(void)
{
	device_itl9341_fsmc_config();
	chip_driver_systick_delay_ms(50);
	device_itl9341_read_lcd_id();
	if(device_itl9341_get_lcd_id() == DEVICE_ITL9341_ID)
	{
		FSMC_Bank1E->BWTR[6]&=~(0XF<<0); //地址建立时间清零 	 
		FSMC_Bank1E->BWTR[6]&=~(0XF<<8); //数据保存时间清零
		FSMC_Bank1E->BWTR[6]|=3<<0;		   //地址建立时间为3个HCLK =18ns  	 
		FSMC_Bank1E->BWTR[6]|=2<<8;    	 //数据保存时间为6ns*3个HCLK=18ns
		chip_driver_lcd_set_cmd(0xCF); 
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0xC1);
		chip_driver_lcd_set_data(0X30);
		chip_driver_lcd_set_cmd(0xED); 
		chip_driver_lcd_set_data(0x64);
		chip_driver_lcd_set_data(0x03);
		chip_driver_lcd_set_data(0X12);
		chip_driver_lcd_set_data(0X81);
		chip_driver_lcd_set_cmd(0xE8);
		chip_driver_lcd_set_data(0x85);
		chip_driver_lcd_set_data(0x10);
		chip_driver_lcd_set_data(0x7A);		
		chip_driver_lcd_set_cmd(0xCB); 
		chip_driver_lcd_set_data(0x39);
		chip_driver_lcd_set_data(0x2C);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x34);
		chip_driver_lcd_set_data(0x02);
		chip_driver_lcd_set_cmd(0xF7);
		chip_driver_lcd_set_data(0x20);
		chip_driver_lcd_set_cmd(0xEA);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x00);		
		chip_driver_lcd_set_cmd(0xC0);  
		chip_driver_lcd_set_data(0x1B);  
		chip_driver_lcd_set_cmd(0xC1);    
		chip_driver_lcd_set_data(0x01);    
		chip_driver_lcd_set_cmd(0xC5);     
		chip_driver_lcd_set_data(0x30);
		chip_driver_lcd_set_data(0x30);		
		chip_driver_lcd_set_cmd(0xC7);     
		chip_driver_lcd_set_data(0XB7); 
		chip_driver_lcd_set_cmd(0x36); 
		chip_driver_lcd_set_data(0x48);
		chip_driver_lcd_set_cmd(0x3A);  
		chip_driver_lcd_set_data(0x55);
		chip_driver_lcd_set_cmd(0xB1); 
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x1A);
		chip_driver_lcd_set_cmd(0xB6); 
		chip_driver_lcd_set_data(0x0A);
		chip_driver_lcd_set_data(0xA2);		 
		chip_driver_lcd_set_cmd(0xF2);     
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_cmd(0x26);
		chip_driver_lcd_set_data(0x01);
		chip_driver_lcd_set_cmd(0xE0);
		chip_driver_lcd_set_data(0x0F);
		chip_driver_lcd_set_data(0x2A);
		chip_driver_lcd_set_data(0x28);
		chip_driver_lcd_set_data(0x08);
		chip_driver_lcd_set_data(0x0E);
		chip_driver_lcd_set_data(0x08);
		chip_driver_lcd_set_data(0x54);
		chip_driver_lcd_set_data(0XA9);
		chip_driver_lcd_set_data(0x43);
		chip_driver_lcd_set_data(0x0A);
		chip_driver_lcd_set_data(0x0F);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x00); 
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_cmd(0XE1);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x15);
		chip_driver_lcd_set_data(0x17);
		chip_driver_lcd_set_data(0x07);
		chip_driver_lcd_set_data(0x11);
		chip_driver_lcd_set_data(0x06);
		chip_driver_lcd_set_data(0x2B);
		chip_driver_lcd_set_data(0x56);
		chip_driver_lcd_set_data(0x3C);
		chip_driver_lcd_set_data(0x05);
		chip_driver_lcd_set_data(0x10);
		chip_driver_lcd_set_data(0x0F);
		chip_driver_lcd_set_data(0x3F);
		chip_driver_lcd_set_data(0x3F);
		chip_driver_lcd_set_data(0x0F);
		chip_driver_lcd_set_cmd(0x2B);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x01);
		chip_driver_lcd_set_data(0x3f);
		chip_driver_lcd_set_cmd(0x2A); 
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0x00);
		chip_driver_lcd_set_data(0xef); 
		chip_driver_lcd_set_cmd(0x11);  
		chip_driver_systick_delay_ms(120);
		chip_driver_lcd_set_cmd(0x29);
		
		device_itl9341_back_light_on();
	
	}
	device_itl9341_set_show_dir(L2R_U2D);
	device_itl9341_show_clear(WHITE);
}
