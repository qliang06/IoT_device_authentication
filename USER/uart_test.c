/****************************************Copyright (c)****************************************************
**
**                                 http://www.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               uart_test.c
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

#include "printf.h"
#include "led.h"


#define SW_STR_NAME							"uart_test"
#define SW_STR_EDITION						"V1.0.0.190508a"
#define SW_STR_AUTHOR						"GW"


#define LOGO_PRINT_ON

#ifdef LOGO_PRINT_ON
#include "logo.h"
#endif	//LOGO_PRINT_ON


#define UART_CONSOLE						UART0
#define UART_CONSOLE_BAUDRATE				115200

#define PRINTF_USE

#ifdef	PRINTF_USE
#define printf_d(args...)					printf(args)
#endif	//PRINTF_USE


void _putchar(char character)
{
	UART_SendChar(UART_CONSOLE, character);
}

static void printf_str(const char *str)
{
#ifdef PRINTF_USE
	printf_d(str);
	//printf_d("%s", str);
#else
	UART_SendString(UART_CONSOLE, (char *)str);
#endif	//PRINTF_USE
}

static void sw_edition_print(void)
{
	printf_str("\r\n");
	printf_str(starts_str);
	printf_str("Name:     "SW_STR_NAME"\r\n"
           "Edition:  "SW_STR_EDITION"\r\n"
		   "Compiled: "__DATE__", "__TIME__"\r\n"
			"Author:   "SW_STR_AUTHOR"\r\n");
	printf_str(starts_str);
	printf_str("\r\n");
}

static void start_info_print(void)
{
	sw_edition_print();

#ifdef LOGO_PRINT_ON
	printf_str("\r\n");
	printf_str(starts_str);
	printf_str(logo_str);
	printf_str(starts_str);
	printf_str("\r\n");
#endif	//LOGO_PRINT_ON
}

void uart0_init(uint32_t baudrate)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
	UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
	UART_InitStruct.UART_Hstm = DISABLE;
	UART_InitStruct.UART_BaudRate = baudrate;

	UART_Init(UART0, &UART_InitStruct);
}

void uart1_init(uint32_t baudrate)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
	UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
	UART_InitStruct.UART_Hstm = DISABLE;
	UART_InitStruct.UART_BaudRate = baudrate;

	UART_Init(UART1, &UART_InitStruct);
}

void uart2_init(uint32_t baudrate)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
	UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
	UART_InitStruct.UART_Hstm = DISABLE;
	UART_InitStruct.UART_BaudRate = baudrate;

	UART_Init(UART2, &UART_InitStruct);
}

void uart3_init(uint32_t baudrate)
{
	UART_InitTypeDef UART_InitStruct;

	UART_InitStruct.UART_Mode.UARTMode_Tx = ENABLE;
	UART_InitStruct.UART_Mode.UARTMode_Rx = ENABLE;
	UART_InitStruct.UART_Int.UARTInt_Tx = DISABLE;
	UART_InitStruct.UART_Int.UARTInt_Rx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Tx = DISABLE;
	UART_InitStruct.UART_Ovr.UARTOvr_Rx = DISABLE;
	UART_InitStruct.UART_Hstm = DISABLE;
	UART_InitStruct.UART_BaudRate = baudrate;

	UART_Init(UART3, &UART_InitStruct);
}

void uart0_read(uint8_t *out, uint32_t bytes)
{
    while (bytes--)
    {
        *out++ = UART_ReceiveChar(UART0);
    }
}

void uart1_read(uint8_t *out, uint32_t bytes)
{
    while (bytes--)
    {
        *out++ = UART_ReceiveChar(UART1);
    }
}

void uart2_read(uint8_t *out, uint32_t bytes)
{
    while (bytes--)
    {
        *out++ = UART_ReceiveChar(UART2);
    }
}

void uart3_read(uint8_t *out, uint32_t bytes)
{
    while (bytes--)
    {
        *out++ = UART_ReceiveChar(UART3);
    }
}

static void delay(volatile uint32_t n)
{
	while (n--)
	{
		;
	}
}

static void init_misc(void)
{
	uart0_init(UART_CONSOLE_BAUDRATE);
	uart1_init(115200);
	uart2_init(115200);
	uart3_init(115200);

	led_init();
}

void printf_test(void)
{
#ifdef PRINTF_USE
	printf_d("\r\nprintf_test\r\n");
	printf_d("123 = %u\r\n", 123);
	printf_d("-456 = %d\r\n\r\n", -456);
#endif	//PRINTF_USE
}

int uart_test(void)
{
	uint8_t n = 10;

	uint8_t buf0[2] = {0};
	uint8_t buf1[2] = {0};
	uint8_t buf2[2] = {0};
	uint8_t buf3[2] = {0};

	init_misc();
	start_info_print();
	printf_test();

	while (n--)
	{
		UART_SendString(UART0, (char *)"0.uart_test\r\n");
		UART_SendString(UART1, (char *)"1.uart_test\r\n");
		UART_SendString(UART2, (char *)"2.uart_test\r\n");
		UART_SendString(UART3, (char *)"3.uart_test\r\n");

		led_toggle(0);
		led_toggle(1);
		led_toggle(2);
		led_toggle(3);

		delay(0x000FFFFF);
	}

	while (1)
	{
		uart0_read(buf0, 1);
		UART_SendString(UART0, (char *)buf0);

		uart1_read(buf1, 1);
		UART_SendString(UART1, (char *)buf1);

		uart2_read(buf2, 1);
		UART_SendString(UART2, (char *)buf2);

		uart3_read(buf3, 1);
		UART_SendString(UART3, (char *)buf3);

		led_toggle(0);
		led_toggle(1);
		led_toggle(2);
		led_toggle(3);

		delay(0x000FFFFF);
	}

	return 0;
}

/*********************************************************************************************************
END FILE
*********************************************************************************************************/
