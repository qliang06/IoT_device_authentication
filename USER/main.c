/****************************************Copyright (c)****************************************************
**
**                                 http://www.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Last modified Date:      2019-05-08
** Last Version:            1.0.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:              feiyun.wu
** Created date:            2019-05-08
** Version:                 1.0.0
** Descriptions:            Ô´ÎÄ¼þ
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#include "gw1ns2c.h"
#include <stdio.h>
#include <stdlib.h>

#include "broadkey_demo_app.h"
#include "led.h"	//test by Qin 0914
#include "gw1ns2c_lcd1602.h"
//#define UART_TEST_EN


#ifdef	UART_TEST_EN
#include "uart_test.h"
#endif	//UART_TEST_EN


#define SW_STR_NAME							"broadkey_no_enroll"
#define SW_STR_EDITION						"V1.0.0.190508a"
#define SW_STR_AUTHOR						"GOWIN"
#define	AU_870								"Authentication Project-870 ProjectI | NYIT VANCOUVER "
#define AU_EDITION							"V1.0.0"
#define AU_AUTHOR							"Qin Liang|Jin WU|Qiang Zhou"
#define DELAY_VALUE		3333000				//25M 1s = 8333000

#define FLASH_DETAIN1_BASE        			(FLASH_BASE + 0x1F800)
#define FLASH_DETAIN2_BASE        			(FLASH_BASE + 0x1FC00)

#define UART_CONSOLE						UART0
#define UART_CONSOLE_BAUDRATE				115200

extern int __bk_addr_puf;
extern int __bk_addr_ac;


uint8_t * const sram_puf = (uint8_t * const )&__bk_addr_puf;
uint8_t * const sram_ac = (uint8_t * const )&__bk_addr_ac;


static void printf_str(const char *str)
{
	//UART_SendString(UART0, (char *)str);
	UART_SendString(UART_CONSOLE, (char *)str);
}

static void sw_edition_print(void)
{
	printf_str("\r\n************************************************\r\n");
	printf_str("Name:     "SW_STR_NAME"\r\n"
			   "Edition:  "SW_STR_EDITION"\r\n"
		       "Compiled: "__DATE__", "__TIME__"\r\n"
			   "Author:   "SW_STR_AUTHOR"\r\n"
			   "Topic:   "AU_870"\r\n"
			   "Cur Edition:   "AU_EDITION"\r\n"
			   "Group Member:   "AU_AUTHOR"\r\n");
	printf_str("************************************************\r\n\r\n");
}

uint8_t hex2char(uint8_t va)
{
	if (va <= 9)
	{
		va += '0';
	}
	else
	{
		va += 'A' - 0x0A;
	}
	
	return va;
}

void print_byte(uint8_t va)
{
	uint8_t temp;
	
	temp = hex2char(va >> 4);
	//UART_SendChar(UART0, (char)temp);
	UART_SendChar(UART_CONSOLE, (char)temp);
	
	temp = hex2char(va & 0x0F);
	//UART_SendChar(UART0, (char)temp);
	UART_SendChar(UART_CONSOLE, (char)temp);
}

void endian_big_little_u32(uint32_t *in)
{
	uint8_t temp;
	uint8_t *p = (uint8_t *)in;
	
	temp = p[0];
	p[0] = p[3];
	p[3] = temp;
		
	temp = p[1];
	p[1] = p[2];
	p[2] = temp;
}

void endian_big_little_u32_array(uint32_t *in, uint32_t len)
{
	while (len--)
	{
		endian_big_little_u32(in++);
	}
}

void UartInit(void)
{
  UART_InitTypeDef UART_InitStruct;

  UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
  UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
  UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
  UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
  UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
  UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
  UART_InitStruct.UART_Hstm = DISABLE;
  UART_InitStruct.UART_BaudRate = 115200;//Baud Rate
  //UART_CONSOLE,UART0
  UART_Init(UART_CONSOLE,&UART_InitStruct);
}


void Delay_ms(__IO uint32_t delay_ms)
{
  for(delay_ms=delay_ms*8500; delay_ms != 0; delay_ms--);
}

void Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}

void ReadFlashDetain(uint32_t *data)
{
	uint32_t i = 0;

	for (i = 0; i < 256; i++)
	{
		*(data + i) = *(uint32_t *)(FLASH_DETAIN2_BASE + i * 4);
	}
}

int main(void)
{   
	uint32_t data[256] = {0};
	uint32_t i = 0;
	uint8_t *p = (uint8_t *)data;

#ifdef	UART_TEST_EN
	uart_test();
#else	//UART_TEST_EN
	SystemInit();
	
	//Init Uart
	UartInit();
	
	Delay_ms(10);
	
	sw_edition_print();
	
	for(i = 0; i < 2; i++)
	{
		printf_str("UART Ready!\r\n");
	}
//
	Delay_ms(10);
//
//	printf_str("\r\n00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
	printf_str("Read flash begin.\r\n");

	ReadFlashDetain(data);
	endian_big_little_u32_array(data, sizeof(data) / sizeof(data[0]));
	
	for(i = 0; i < sizeof(data); i++)
	{
		print_byte(*p++);

		if (0 == ((i + 1) % 16))
		{
			printf_str("\r\n");
		}
		else
		{
			printf_str(" ");
		}
	}

	printf_str("Read flash end.\r\n");

    broadkey_demo_app(sram_puf, sram_ac);
#endif	//UART_TEST_EN

    SystemInit();

	Lcd_Pin_Config();
	Lcd_Init();

	Lcd_Write_String("1",1);
	//Lcd_Write_Dat(20);

    GPIO0->OUTENSET = 0xffffffff;

    while (1)
    {
    	GPIO_SetBit(GPIO0, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
		Delay(DELAY_VALUE);

		GPIO_SetBit(GPIO0, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_1);
		Delay(DELAY_VALUE);

		GPIO_SetBit(GPIO0, GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_3);
		GPIO_ResetBit(GPIO0, GPIO_Pin_2);
		Delay(DELAY_VALUE);

		GPIO_SetBit(GPIO0,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_0);
		GPIO_ResetBit(GPIO0, GPIO_Pin_3);
		Delay(DELAY_VALUE);
    }
}
