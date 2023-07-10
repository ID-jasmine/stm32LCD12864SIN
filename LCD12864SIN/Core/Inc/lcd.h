#ifndef __LCD_H
#define __LCD_H

#include "main.h"

#define CLK_0 HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET);//CLK下拉
#define CLK_1 HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET);//CLK上拉
#define CS_0 HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET);//CS下拉
#define CS_1 HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET);//CS上拉

void SID(unsigned char x);
void LCD_writeOneByte(unsigned char data,unsigned char cmd);
void LCD_Init();
void LCD_writehanzi(unsigned char x,unsigned char y,unsigned char *data);
void LCD_Send_byte(uint8_t a);
void LCD_Drawing(const unsigned char *data);



#endif

