#include "lcd.h"

//控制串行输出SID
void SID(unsigned char x)
{
	if (x) HAL_GPIO_WritePin(SID_GPIO_Port,SID_Pin,GPIO_PIN_SET);//如果x大于等于1,那么I/O输出高;
	else HAL_GPIO_WritePin(SID_GPIO_Port,SID_Pin,GPIO_PIN_RESET);//否则输出低
}

//写指令
void LCD_writeOneByte(unsigned char data,unsigned char cmd)//写三个字节(data(数据),cmd(控制字))
{	//SPI通信的控制字:写指令0xf8；//写数据0xfa；//读状态0xfc；//读数据0xfe
	//使用SPI数据通信模式,初始化跟8线并口一样,CS对应12864的RS，SID对应R/W，CLK对应E；
	CLK_1;//CLK上拉
	CS_1;//CS拉高，串行通信开始
	for(unsigned char i=0;i<8;i++)//先告诉12864我需要干什么（把控制字串入）
	{
		SID(cmd & (1 << (7-i)));//从数据高位开始逐位写入
		CLK_0;//下降沿把数据发出去
		CLK_1;
	}
	for(unsigned char i=0;i<8;i++)//然后串入数据的高位，低四位补零
	{
		SID((data & 0xf0) & (1 << (7-i)));//把数据的低四位强制变成0,然后在逐位写入
		CLK_0;
		CLK_1;
	}
	for(unsigned char i=0;i<8;i++)//然后把数据的低位移到高位再串入，低四位补零
	{
		SID((((data&0x0f)<<4) & 0xf0) & (1 << (7-i)));//把数据低位移到高位然后在把移位后的数据的低
		CLK_0;
		CLK_1;									
	}
	CS_0;//CS拉低，串行通信结束
}

//LCD初始化
void LCD_Init()
{
	//文字显示模式初始化代码
	//LCD_writeOneByte(0x30,0xf8);HAL_Delay(10);
	LCD_writeOneByte(0x30,0xf8);HAL_Delay(10);//设置8位数据总线，执行基本指令集
	LCD_writeOneByte(0x0c,0xf8);HAL_Delay(10);//开显示，关光标，关光标闪烁	
	LCD_writeOneByte(0x02,0xf8);HAL_Delay(10);//游标移动到起始位置
	LCD_writeOneByte(0x01,0xf8);HAL_Delay(10);//清屏
	/*
	//绘图模式
	LCD_writeOneByte(0x34,0xf8);HAL_Delay(20);//打开扩充指令集
	LCD_writeOneByte(0x30,0xf8);HAL_Delay(20);//设置8位数据总线，执行基本指令集
	LCD_writeOneByte(0x01,0xf8);HAL_Delay(10);//清屏
	LCD_writeOneByte(0x0c,0xf8);HAL_Delay(10);//开显示，关光标，关光标闪烁
	LCD_writeOneByte(0x01,0xf8);HAL_Delay(10);//清屏
	LCD_writeOneByte(0x26,0xf8);HAL_Delay(20);//开绘图
	*/
};
uint16_t x_y_addr[][8]={
	{0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87},
	{0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97},
	{0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F},
	{0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F}
};

void LCD_writehanzi(unsigned char x,unsigned char y,unsigned char *data)//写汉字、字符（列，行，数据）
{
	LCD_writeOneByte(x_y_addr[y-1][x],0xf8);
	//定位第几行第几列开始写汉字
	while(*data!='\0'){
		LCD_writeOneByte(*data,0xfa);//写入汉字
		data++;
	}
}
//这里用到了取Flash的一个字节的函数
#define pgm_read_byte(addr) pgm_read_byte_near(addr)

unsigned char pgm_read_byte_near(const unsigned char *addr)
{
    unsigned char result;
    // 硬件相关的读取操作
    result = *addr;
    return result;
}

//绘图
void LCD_Drawing(const unsigned char *data)
{
	LCD_writeOneByte(0x34,0xf8);//打开扩充指令集
	for(unsigned char i=0;i<32;i++)//先写入上半屏
	{
		LCD_writeOneByte(0x80+i,0xf8);//上板屏有32行
		LCD_writeOneByte(0x80,0xf8);//第几列开始
		for (unsigned char q=0;q<16;q++)
		{
			LCD_writeOneByte(pgm_read_byte(&*data++),0xfa);//这里用到了取Flash的一个字节的函数
		}
	}	
	for(unsigned char i=0;i<32;i++)//然后写下半屏
	{
		LCD_writeOneByte(0x80+i,0xf8);//下半屏有32行
		LCD_writeOneByte(0x88,0xf8);//从第几列开始
		for (unsigned char q=0;q<16;q++)
		{
			LCD_writeOneByte(pgm_read_byte(&*data++),0xfa);//这里用到了取Flash的一个字节的函数
		}
	}
	LCD_writeOneByte(0x36,0xf8);//打开绘图指令
  LCD_writeOneByte(0x30,0xf8);//打开绘图指令
}






