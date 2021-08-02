#include "device_lcd_mgr.h"
#include "device_itl9341_driver.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "error_code_config.h"
static dev_lcd_ops_t dev_lcd_ops;

static bool dev_lcd_init_flag = false;



static uint32_t dev_lcd_init(void)
{
	if(dev_lcd_init_flag)
	{
		return ERROR_CODE_SUCCESS;
	}
	device_itl9341_init();
	dev_lcd_init_flag = true;
	return ERROR_CODE_SUCCESS;
}

static uint32_t dev_lcd_uninit(void)
{
	dev_lcd_init_flag = false;
	return ERROR_CODE_SUCCESS;
}

void dev_lcd_mgr_reg(dev_lcd_ops_t *ops)
{
	memcpy(&dev_lcd_ops,ops,sizeof(dev_lcd_ops_t));
}


uint32_t dev_lcd_mgr_init(void)
{
	if(dev_lcd_ops.init != NULL)
	{
		return dev_lcd_ops.init();
	}
	else
	{
		return ERROR_CODE_INVALID_ADDR;
	}
}
