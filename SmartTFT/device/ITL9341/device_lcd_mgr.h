#ifndef  __DEVICE_LCD_MGR_H_
#define  __DEVICE_LCD_MGR_H_

#include <stdint.h>

typedef struct
{
	uint32_t (*init)(void);
	uint32_t (*uninit)(void);

}dev_lcd_ops_t;


void dev_lcd_mgr_reg(dev_lcd_ops_t *ops);

uint32_t dev_lcd_mgr_init(void);








#endif


