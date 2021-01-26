/****************************************Copyright (c)****************************************************
**
**                                 http://www.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               led.c
** Last modified Date:      2019-05-07
** Last Version:            1.0.0
** Descriptions:            
**
**--------------------------------------------------------------------------------------------------------
** Created by:              feiyun.wu
** Created date:            2019-05-07
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
#include <stdint.h>

#include "gw1ns2c.h"


void led_init(void)
{
	GPIO0->OUTENSET = 0xFFFFFFFF;
	GPIO_SetBit(GPIO0, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
}

void led_on(uint8_t led)
{
    switch (led)
    {
        case 0:
        	GPIO_ResetBit(GPIO0, GPIO_Pin_0);
        	break;

        case 1:
        	GPIO_ResetBit(GPIO0, GPIO_Pin_1);
        	break;

        case 2:
        	GPIO_ResetBit(GPIO0, GPIO_Pin_2);
        	break;

        case 3:
        	GPIO_ResetBit(GPIO0, GPIO_Pin_3);
        	break;

        default:
        	break;
    }
}

void led_off(uint8_t led)
{
	switch (led)
    {
        case 0:
        	GPIO_SetBit(GPIO0, GPIO_Pin_0);
        	break;

        case 1:
        	GPIO_SetBit(GPIO0, GPIO_Pin_1);
        	break;

        case 2:
        	GPIO_SetBit(GPIO0, GPIO_Pin_2);
        	break;

        case 3:
        	GPIO_SetBit(GPIO0, GPIO_Pin_3);
        	break;

        default:
        	break;
    }
}

void led_toggle(uint8_t led)
{
	uint32_t temp;

	temp = GPIO0->DATAOUT;

	switch (led)
    {
        case 0:
        	if (temp & GPIO_Pin_0)
        	{
        		GPIO_ResetBit(GPIO0, GPIO_Pin_0);
        	}
        	else
        	{
        		GPIO_SetBit(GPIO0, GPIO_Pin_0);
        	}

			break;

        case 1:
        	if (temp & GPIO_Pin_1)
        	{
        		GPIO_ResetBit(GPIO0, GPIO_Pin_1);
        	}
        	else
        	{
        		GPIO_SetBit(GPIO0, GPIO_Pin_1);
        	}

			break;

        case 2:
        	if (temp & GPIO_Pin_2)
        	{
        		GPIO_ResetBit(GPIO0, GPIO_Pin_2);
        	}
        	else
        	{
        		GPIO_SetBit(GPIO0, GPIO_Pin_2);
        	}

			break;

        case 3:
        	if (temp & GPIO_Pin_3)
        	{
        		GPIO_ResetBit(GPIO0, GPIO_Pin_3);
        	}
        	else
        	{
        		GPIO_SetBit(GPIO0, GPIO_Pin_3);
        	}

			break;

        default:
        	break;
    }
}

/*********************************************************************************************************
END FILE
*********************************************************************************************************/
