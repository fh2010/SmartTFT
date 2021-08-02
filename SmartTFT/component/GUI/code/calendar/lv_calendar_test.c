#include "lv_calendar_test.h"
#include "lvgl.h"
#include <stdio.h>


//周日,周一,周二,....,周六
const char * const day_names[7] = {"Su","Mo","Tu","We","Th","Fr","Sa"};
//一月,二月,三月...,十二月
const char * const month_names[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
//需要被高亮显示的日期
const lv_calendar_date_t highlihted_days[2] = {{2018,11,9},{2018,11,13}};
//样式
lv_style_t bg_style;
lv_style_t header_style;
lv_style_t header_pr_style;
lv_style_t day_names_style;
lv_style_t highlighted_style;
lv_style_t inactive_style;
lv_style_t today_style;
lv_style_t today_row_style;
//标签
lv_obj_t * label1;


//事件回调函数
static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	char buff[30];
	if(event==LV_EVENT_CLICKED)//相当于松手事件,所以也可以替换成LV_EVENT_RELEASED
	{
		lv_calendar_date_t * selected_date = lv_calendar_get_pressed_date(obj);//获取被按下的日期,或者说是用户选择的日期

		//当用户点击HEADER区域和星期信息行区域时,会出现year=0,month=0,day=0的情况,所以我们得过滤掉这种情况
		if(selected_date&&(selected_date->year!=0)) {
				sprintf(buff,"%d/%d/%d",selected_date->year,selected_date->month,selected_date->day);
				lv_label_set_text(label1,buff);//把用户选择的日期给显示出来
				lv_calendar_set_today_date(obj,selected_date);//将用户选择的日期设置为今天的日期,即TODAY日期
				lv_calendar_set_showed_date(obj,selected_date);//跳转到这个日期所在的界面
		}
	}
}


//例程入口
void lv_calendar_test_start()
{
	/*
	lv_obj_t * scr = lv_scr_act();//获取当前活跃的屏幕对象

	//1.创建8种样式
	//1.1 创建背景样式
	lv_style_copy(&bg_style,&lv_style_plain_color);
	bg_style.map.main_color = LV_COLOR_WHITE;//背景颜色
	bg_style.body.grad_color = LV_COLOR_WHITE;
	bg_style.body.border.color = LV_COLOR_MAKE(57,61,73);//边框的颜色
	bg_style.body.border.width = 2;//边框的宽度
	bg_style.body.shadow.color = LV_COLOR_GRAY;//阴影的颜色
	bg_style.body.shadow.width = 6;//阴影的宽度
	bg_style.body.padding.left = 0;//设置日期与左边框的距离
	bg_style.text.color = LV_COLOR_BLACK;//未被高亮显示的日期文本颜色
	//1.2 创建HEADER样式
	lv_style_copy(&header_style,&lv_style_plain_color);
	header_style.body.main_color = LV_COLOR_MAKE(57,61,73);//背景颜色
	header_style.body.grad_color = LV_COLOR_MAKE(57,61,73);
	header_style.body.padding.left = 15;//设置左箭头按钮与左边框的距离
	header_style.body.padding.right = 15;//设置右箭头按钮与右边框的距离
	header_style.body.padding.top = 8;//设置文本内容与上边框的距离
	//1.3 创建HEADER按下时的样式
	lv_style_copy(&header_pr_style,&lv_style_plain_color);
	header_pr_style.text.color = LV_COLOR_GRAY;//箭头按钮按下时的文本颜色
	//1.4 创建星期信息行的样式
	lv_style_copy(&day_names_style,&lv_style_plain_color);
	day_names_style.text.color = LV_COLOR_MAKE(0,150,136);
	//1.5 创建高亮日期的样式
	lv_style_copy(&highlighted_style,&lv_style_plain_color);
	highlighted_style.text.color = LV_COLOR_RED;//用红色进行高亮
	//1.6 创建上个月的月末日期和下个月的月初日期样式
	lv_style_copy(&inactive_style,&lv_style_plain_color);
	inactive_style.text.color = LV_COLOR_MAKE(0xAA,0xAA,0xAA);//灰色
	//1.7 创建TODAY日期的样式
	lv_style_copy(&today_style,&lv_style_plain_color);
	today_style.body.main_color = LV_COLOR_MAKE(85,150,216);
	today_style.body.grad_color = LV_COLOR_MAKE(85,150,216);
	today_style.body.radius = LV_RADIUS_CIRCLE;//圆角
	today_style.text.color = LV_COLOR_WHITE;
	 //1.8 创建TODAY日期所在行的日期
	lv_style_copy(&today_row_style,&lv_style_transp);
	today_row_style.text.color = LV_COLOR_MAKE(85,150,216);

	//2.创建日历对象
	lv_obj_t * calendar1 = lv_calendar_create(scr,NULL);//创建日历对象
	lv_obj_set_size(calendar1,220,220);//设置大小
	lv_obj_align(calendar1,NULL,LV_ALIGN_CENTER,0,0);//设置与屏幕居中对齐
	lv_obj_set_event_cb(calendar1,event_handler);//设置事件回调函数
	lv_calendar_date_t today = {2018,11,23};//可以定义为局部的
	lv_calendar_set_today_date(calendar1,&today);//设置TODAY日期
	lv_calendar_set_showed_date(calendar1,&today);//跳转到TODAY日期所在的界面
	lv_calendar_set_day_names(calendar1,(const char **)day_names);//设置星期信息行的标题,也可以不设置,那么lv_calendar会有一个默认的值
	lv_calendar_set_month_names(calendar1,(const char **)month_names);//设置月份的标题,也可以不设置,那么lv_calendar会有一个默认的值
	lv_calendar_set_highlighted_dates(calendar1,(lv_calendar_date_t *)highlihted_days,sizeof(highlihted_days)/sizeof(highlihted_days[0]));//设置需要被高亮显示的日期
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_BG,&bg_style);//设置日历控件主体部分的背景样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_HEADER,&header_style);//设置HEADER样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_HEADER_PR,&header_pr_style);//设置HEADER按下时的样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_DAY_NAMES,&day_names_style);//设置星期信息行的样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_HIGHLIGHTED_DAYS,&highlighted_style);//设置高亮日期的样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_INACTIVE_DAYS,&inactive_style);//设置高亮日期的样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_TODAY_BOX,&today_style);//设置TODAY日期的样式
	lv_calendar_set_style(calendar1,LV_CALENDAR_STYLE_WEEK_BOX,&today_row_style);//设置TODAY日期所在行的样式

	//3.创建标签,用来显示用户选择的日期
	label1 = lv_label_create(scr,NULL);
	lv_label_set_text(label1,"year/month/day");
	lv_obj_align(label1,calendar1,LV_ALIGN_OUT_BOTTOM_MID,0,15);
	lv_obj_set_auto_realign(label1,true);//使能自动重新对齐功能
	
	*/
	
	lv_obj_t  * calendar = lv_calendar_create(lv_scr_act(),NULL);
	lv_obj_set_size(calendar,235,235);
	lv_obj_align(calendar,NULL,LV_ALIGN_CENTER,0,0);
	lv_obj_set_event_cb(calendar,event_handler);
	
	lv_obj_set_style_local_text_font(calendar,LV_CALENDAR_PART_DATE,\
	LV_STATE_DEFAULT,lv_theme_get_font_small());
	lv_calendar_date_t today ;
	today.year = 2021;
	today.month = 8;
	today.day = 1;
	
	lv_calendar_set_today_date(calendar,&today);
	lv_calendar_set_showed_date(calendar,&today);
	
	static lv_calendar_date_t highlighted_days[3];
	highlighted_days[0].year = 2021;
	highlighted_days[0].month = 7;
	highlighted_days[0].day = 10;
	
		highlighted_days[1].year = 2021;
	highlighted_days[1].month = 7;
	highlighted_days[1].day = 11;
	
		highlighted_days[2].year = 2021;
	highlighted_days[2].month = 7;
	highlighted_days[2].day = 12;
	
	lv_calendar_set_highlighted_dates(calendar,highlighted_days,3);
}


