/*! \copyright Copyright 2018 Intrinsic ID B.V. All rights reserved.\n
    This text contains proprietary, confidential information of Intrinsic ID B.V.,
    and may be used, copied, distributed and/or published only pursuant to the
    terms of a valid license agreement with Intrinsic ID B.V.\n
    This copyright notice must be retained as part of this text at all times.
*/

#include "gw1ns2c.h"

#include "iid_usart.h"
#include "iid_platform.h"

#define PLATFORM_UART          UART0	//change uart0 to uart1 by noke 2020/11/16

void iid_usart_setup(uint32_t baudrate)
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

    UART_Init(PLATFORM_UART, &UART_InitStruct);
}

void iid_usart_write(const uint8_t * const data, uint32_t num_bytes)
{
    char * pu8 = (char *)data;

    while (num_bytes--)
    {
        UART_SendChar(PLATFORM_UART, *pu8++);
    }

    /* Wait till the last character has been sent. */
    while(PLATFORM_UART->STATE & UART_STATE_TXBF);
}

void iid_usart_read(uint8_t * const data, uint32_t num_bytes)
{
    char * pu8 = (char *)data;

    while (num_bytes--)
    {
        *pu8++ = UART_ReceiveChar(PLATFORM_UART);
    }
}
