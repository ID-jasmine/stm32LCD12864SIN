#include "lcd.h"

//���ƴ������SID
void SID(unsigned char x)
{
	if (x) HAL_GPIO_WritePin(SID_GPIO_Port,SID_Pin,GPIO_PIN_SET);//���x���ڵ���1,��ôI/O�����;
	else HAL_GPIO_WritePin(SID_GPIO_Port,SID_Pin,GPIO_PIN_RESET);//���������
}

//дָ��
void LCD_writeOneByte(unsigned char data,unsigned char cmd)//д�����ֽ�(data(����),cmd(������))
{	//SPIͨ�ŵĿ�����:дָ��0xf8��//д����0xfa��//��״̬0xfc��//������0xfe
	//ʹ��SPI����ͨ��ģʽ,��ʼ����8�߲���һ��,CS��Ӧ12864��RS��SID��ӦR/W��CLK��ӦE��
	CLK_1;//CLK����
	CS_1;//CS���ߣ�����ͨ�ſ�ʼ
	for(unsigned char i=0;i<8;i++)//�ȸ���12864����Ҫ��ʲô���ѿ����ִ��룩
	{
		SID(cmd & (1 << (7-i)));//�����ݸ�λ��ʼ��λд��
		CLK_0;//�½��ذ����ݷ���ȥ
		CLK_1;
	}
	for(unsigned char i=0;i<8;i++)//Ȼ�������ݵĸ�λ������λ����
	{
		SID((data & 0xf0) & (1 << (7-i)));//�����ݵĵ���λǿ�Ʊ��0,Ȼ������λд��
		CLK_0;
		CLK_1;
	}
	for(unsigned char i=0;i<8;i++)//Ȼ������ݵĵ�λ�Ƶ���λ�ٴ��룬����λ����
	{
		SID((((data&0x0f)<<4) & 0xf0) & (1 << (7-i)));//�����ݵ�λ�Ƶ���λȻ���ڰ���λ������ݵĵ�
		CLK_0;
		CLK_1;									
	}
	CS_0;//CS���ͣ�����ͨ�Ž���
}

//LCD��ʼ��
void LCD_Init()
{
	//������ʾģʽ��ʼ������
	//LCD_writeOneByte(0x30,0xf8);HAL_Delay(10);
	LCD_writeOneByte(0x30,0xf8);HAL_Delay(10);//����8λ�������ߣ�ִ�л���ָ�
	LCD_writeOneByte(0x0c,0xf8);HAL_Delay(10);//����ʾ���ع�꣬�ع����˸	
	LCD_writeOneByte(0x02,0xf8);HAL_Delay(10);//�α��ƶ�����ʼλ��
	LCD_writeOneByte(0x01,0xf8);HAL_Delay(10);//����
	/*
	//��ͼģʽ
	LCD_writeOneByte(0x34,0xf8);HAL_Delay(20);//������ָ�
	LCD_writeOneByte(0x30,0xf8);HAL_Delay(20);//����8λ�������ߣ�ִ�л���ָ�
	LCD_writeOneByte(0x01,0xf8);HAL_Delay(10);//����
	LCD_writeOneByte(0x0c,0xf8);HAL_Delay(10);//����ʾ���ع�꣬�ع����˸
	LCD_writeOneByte(0x01,0xf8);HAL_Delay(10);//����
	LCD_writeOneByte(0x26,0xf8);HAL_Delay(20);//����ͼ
	*/
};
uint16_t x_y_addr[][8]={
	{0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87},
	{0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97},
	{0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F},
	{0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F}
};

void LCD_writehanzi(unsigned char x,unsigned char y,unsigned char *data)//д���֡��ַ����У��У����ݣ�
{
	LCD_writeOneByte(x_y_addr[y-1][x],0xf8);
	//��λ�ڼ��еڼ��п�ʼд����
	while(*data!='\0'){
		LCD_writeOneByte(*data,0xfa);//д�뺺��
		data++;
	}
}
//�����õ���ȡFlash��һ���ֽڵĺ���
#define pgm_read_byte(addr) pgm_read_byte_near(addr)

unsigned char pgm_read_byte_near(const unsigned char *addr)
{
    unsigned char result;
    // Ӳ����صĶ�ȡ����
    result = *addr;
    return result;
}

//��ͼ
void LCD_Drawing(const unsigned char *data)
{
	LCD_writeOneByte(0x34,0xf8);//������ָ�
	for(unsigned char i=0;i<32;i++)//��д���ϰ���
	{
		LCD_writeOneByte(0x80+i,0xf8);//�ϰ�����32��
		LCD_writeOneByte(0x80,0xf8);//�ڼ��п�ʼ
		for (unsigned char q=0;q<16;q++)
		{
			LCD_writeOneByte(pgm_read_byte(&*data++),0xfa);//�����õ���ȡFlash��һ���ֽڵĺ���
		}
	}	
	for(unsigned char i=0;i<32;i++)//Ȼ��д�°���
	{
		LCD_writeOneByte(0x80+i,0xf8);//�°�����32��
		LCD_writeOneByte(0x88,0xf8);//�ӵڼ��п�ʼ
		for (unsigned char q=0;q<16;q++)
		{
			LCD_writeOneByte(pgm_read_byte(&*data++),0xfa);//�����õ���ȡFlash��һ���ֽڵĺ���
		}
	}
	LCD_writeOneByte(0x36,0xf8);//�򿪻�ͼָ��
  LCD_writeOneByte(0x30,0xf8);//�򿪻�ͼָ��
}






