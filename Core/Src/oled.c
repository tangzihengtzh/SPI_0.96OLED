/*
 * oled.c
 *
 *  Created on: May 29, 2023
 *      Author: tzh15
 */
#include "oled.h"
#include "main.h"



void OLED_WriteCmd(uint8_t cmd)
{
	uint8_t i = 8;
    HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 0);
    //开始传输指令DC：0指令1数据
    HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, 0);
    //SCL连接着oled模块的采用同步线，仅当SCL上升沿时候oled模块的数据输入从SDA线上采样
    for(i = 0; i < 8; i++)
    {
        if(cmd & 0x80)
        {
            HAL_GPIO_WritePin(OLED_SDIN_GPIO_Port, OLED_SDIN_Pin, 1);
        }
        else
        {
        	HAL_GPIO_WritePin(OLED_SDIN_GPIO_Port, OLED_SDIN_Pin, 0);
        }//根据cmd信号的最高位来决定对数据线SDA进行输出
        HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, 1);
        //构建SCL的上升沿以便于读取数据线上电平高低
        HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, 0);
        //复位采样同步信号
        cmd <<= 1;
        //cmd数据位移
    }
}

void OLED_WriteData(uint8_t dat)
{
	uint8_t i = 8;
    HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 1);
    //开始传输指令DC：0指令1数据
    HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, 0);
    //SCL连接着oled模块的采用同步线，仅当SCL上升沿时候oled模块的数据输入从SDA线上采样
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x80)
        {
            HAL_GPIO_WritePin(OLED_SDIN_GPIO_Port, OLED_SDIN_Pin, 1);
        }
        else
        {
        	HAL_GPIO_WritePin(OLED_SDIN_GPIO_Port, OLED_SDIN_Pin, 0);
        }//根据cmd信号的最高位来决定对数据线SDA进行输出
        HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, 1);
        //构建SCL的上升沿以便于读取数据线上电平高低
        HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, 0);
        //复位采样同步信号
        dat <<= 1;
        //cmd数据位移
    }
}

void OLED_DisON(void)
{
    OLED_WriteCmd(0x8d);		//电荷泵设置
    OLED_WriteCmd(0x14);		//电荷泵开启
    OLED_WriteCmd(0xaf);		//开启显示
}

void OLED_DisOFF(void)
{
    OLED_WriteCmd(0x8d);		//电荷泵设置
    OLED_WriteCmd(0x10);		//电荷泵关闭
    OLED_WriteCmd(0xae);		//关闭显示
}

void OLED_Clear(void)		//È«²¿ÊÇºÚÉ«µÄ.Ã»ÓÐµãÁÁ
{
    uint8_t i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd (0xb0 + i); //页地址
        OLED_WriteCmd (0x00);     //列低地址
        OLED_WriteCmd (0x10);     //列高地址
        for(n = 0; n < 128; n++)	//128个像素
            OLED_WriteData(0);		//设置亮度0
    }
}

void OLED_SetCursor(uint8_t x, uint8_t y)
{
    OLED_WriteCmd(0xb0 + (y >> 3));
    OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0f) | 0x01);
}

void OLED_Init(void)
{
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 1);
    HAL_Delay(100);
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 0);
    HAL_Delay(100);
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 1);

    OLED_WriteCmd(0xAE);
	OLED_WriteCmd(0xD5);
	OLED_WriteCmd(0x80);
	OLED_WriteCmd(0xA8);
	OLED_WriteCmd(0X3F);
	OLED_WriteCmd(0xD3);
	OLED_WriteCmd(0X00);
	OLED_WriteCmd(0x40);
	OLED_WriteCmd(0x8D);
	OLED_WriteCmd(0x14);
	OLED_WriteCmd(0x20);
	OLED_WriteCmd(0x02);
	OLED_WriteCmd(0xA1);
	OLED_WriteCmd(0xC8);
	OLED_WriteCmd(0xDA);
	OLED_WriteCmd(0x12);
	OLED_WriteCmd(0x81);
	OLED_WriteCmd(0x7f);
	OLED_WriteCmd(0xD9);
	OLED_WriteCmd(0xf1);
	OLED_WriteCmd(0xDB);
	OLED_WriteCmd(0x30);
	OLED_WriteCmd(0xA4);
	OLED_WriteCmd(0xA6);
	OLED_WriteCmd(0xAF);

	OLED_Clear();
	OLED_SetCursor(0, 0);
}
















