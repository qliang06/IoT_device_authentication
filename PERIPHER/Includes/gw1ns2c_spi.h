/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2018 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			gw1ns2c_spi.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2018-5-1 09:00:00
 * @brief			This file contains all the functions prototypes for the SPI firmware library.
 ******************************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW1NS2C_SPI_H
#define __GW1NS2C_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gw1ns2c.h"

/** @addtogroup GW1NS2C_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/** @defgroup SPI_Exported_Types
  * @{
  */

/* SPI InitTypeDef */
typedef struct
{
  FunctionalState DIRECTION;  /* @arg: ENABLE MSB first transmission;
                                 @arg: DISABLE LSB first transmission;
                               */
  FunctionalState PHASE;      /* @arg: ENABLE Posedge transmit data;
                                 @arg: DISABLE Negedge transmit data;
                               */
  FunctionalState POLARITY;   /* @arg: ENABLE Initial polarity to 1
                                 @arg: DISABLE Initial polarity to 0;
                               */
  uint32_t CLKSEL;            /* Clock Selection */
  
}SPI_InitTypeDef;

/**
  * @}
  */

/** @defgroup SPI_Exported_Macros
  * @{
  */

/* Clock Selection */
#define CLKSEL_CLK_DIV_2   ((uint32_t) 0x00000000)  //CLK/2
#define CLKSEL_CLK_DIV_4   ((uint32_t) 0x00000001)  //CLK/4
#define CLKSEL_CLK_DIV_6   ((uint32_t) 0x00000003)  //CLK/6
#define CLKSEL_CLK_DIV_8   ((uint32_t) 0x00000004)  //CLK/8

/* Register Bit Position */
#define SPI_CR_DIRECTION_Pos   0   /* CTRL register DIRECTION bit position */
#define SPI_CR_PHASE_Pos       1   /* CTRL register PHASE bit position     */
#define SPI_CR_POLARITY_Pos    2   /* CTRL register POLARITY bit position  */
#define SPI_STATUS_ROE_Pos     2   /* STATUS register ROE bit position     */
#define SPI_STATUS_TOE_Pos     3   /* STATUS register TOE bit position     */
#define SPI_STATUS_TMT_Pos     4   /* STATUS register TMT bit position     */
#define SPI_STATUS_TRDY_Pos    5   /* STATUS register TRDY bit position    */
#define SPI_STATUS_RRDY_Pos    6   /* STATUS register RRDY bit position    */
#define SPI_STATUS_ERR_Pos     7   /* STATUS register ERR bit position     */

#define SPI_CR_CLKSEL_Pos     ((uint32_t) 0x00000003)    /* CTRL register CLKSEL Position */
#define SPI_CR_CLKSEL_Mask    ((uint32_t) 0x00000003)    /* CTRL register CLKSEL mask     */

/**
  * @}
  */

/** @defgroup SPI_Exported_Functions
  * @{
  */

/**
  * @brief Initializes SPI
  */
extern void SPI_Init(SPI_InitTypeDef* SPI_InitStruct);

/**
  * @brief Sets Direction
  */
extern void SPI_SetDirection(void);

/**
  * @brief Clears Direction
  */
extern void SPI_ClrDirection(void);

/**
  * @brief Returns Direction
  */
extern uint32_t SPI_GetDirection(void);

/**
  * @brief Sets Phase
  */
extern void SPI_SetPhase(void);

/**
  * @brief Clears Phase
  */
extern void SPI_ClrPhase(void);

/**
  * @brief Returns Phase
  */
extern uint32_t SPI_GetPhase(void);

/**
  * @brief Returns Polarity
  */
extern uint32_t SPI_GetPolarity(void);

/**
  * @brief Clears Polarity
  */
extern void SPI_ClrPolarity(void);

/**
  * @brief Sets Polarity
  */
extern void SPI_SetPolarity(void);

/**
  * @brief Sets ClkSel
  */
extern void SPI_SetClkSel(uint32_t clksel);

/**
  * @brief Returns ClkSel
  */
extern uint32_t SPI_GetClkSel(void);

/**
  * @brief Reads transmit overrun error status
  */
extern FlagStatus SPI_GetToeStatus(void);

/**
  * @brief Reads receive overrun error status
  */
extern FlagStatus SPI_GetRoeStatus(void);

/**
  * @brief Reads transmitting status
  */
extern FlagStatus SPI_GetTmtStatus(void);

/**
  * @brief Reads transmit ready status
  */
extern FlagStatus SPI_GetTrdyStatus(void);

/**
  * @brief Reads receive ready status
  */
extern FlagStatus SPI_GetRrdyStatus(void);

/**
  * @brief Reads error status
  */
extern FlagStatus SPI_GetErrStatus(void);

/**
  * @brief Clears transmit overrun error status
  */
extern void SPI_ClrToeStatus(void);

/**
  * @brief Clear receive overrun error status
  */
extern void SPI_ClrRoeStatus(void);

/**
  * @brief Clears error status
  */
extern void SPI_ClrErrStatus(void);

/**
  * @brief Writes Data
  */
extern void SPI_WriteData(uint8_t data);

/**
  * @brief Reads Data
  */
extern uint8_t SPI_ReadData(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __GW1NS2C_SPI_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************GowinSemiconductor******END OF FILE*******************/

