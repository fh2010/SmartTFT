#ifndef __DEVICE_ITL9341_DRIVER_H_
#define __DEVICE_ITL9341_DRIVER_H_

#include "chip_driver_lcd.h"
#include "lcd_config.h"

typedef enum 
{
	L2R_U2D = 0,
	L2R_D2U = 1,
	R2L_U2D = 2,
	R2L_D2U = 3,
	U2D_L2R = 4,
	U2D_R2L = 5,
	D2U_L2R = 6,
	D2U_R2L = 7,
}DEVICE_ITL9341_SCAN_DIR;

typedef enum 
{
	VERTICAL_SCREEN = 0,
	HORIZONTAL_SCREEN = 1,
}DEVICE_ITL9341_DISPLAY_DIR;

typedef struct
{
	uint16_t lcd_id;
	DEVICE_ITL9341_DISPLAY_DIR dis_dir;
	uint16_t lcd_width;
	uint16_t lcd_height;
	uint16_t lcd_brush_color;
	uint16_t lcd_back_color;
	
}device_itl9341_msg_t;



#define   DEVICE_ITL9341_DISPLAY_ON     0x29
#define   DEVICE_ITL9341_DISPLAY_OFF    0x28
#define   DEVICE_ITL9341_SET_X          0x2A
#define   DEVICE_ITL9341_SET_Y          0x2B
#define   DEVICE_ITL9341_WRITE_GRAM     0x2C
#define   DEVICE_ITL9341_SCAN_DIR_REG   0x36

#define   DEVICE_ITL9341_ID             0x9341



extern void device_itl9341_init(void);

#endif

