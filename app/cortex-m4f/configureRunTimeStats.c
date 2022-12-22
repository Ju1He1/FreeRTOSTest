/****************************************************************************
 * @copyright Copyright: Testo SE & Co. KGaA, 79822 Titisee-Neustadt
 * @file configureRunTimeStats.c
 * @brief<b>Description: </b> enter description here 
 *
 * <br> <br> description:<br> 
 * ... 
 * <br> <br> variability:<br> 
 * ... 
 * <br> <br> context:<br> 
 * ... 
 * <br> <br> collaborators:<br> 
 * ... 
 * <br> <br>provided interfaces:<br> 
 * ...: 
 * @sa ref 
 * 
 * <br> <br> required interfaces:<br>  
 * ... 
  <br> <br> boundary conditions:<br> 
 *  Created on: 16.08.2021
 * <br> @author Author: 1000len-Julian
 * <br> Date: 16.08.2021 
 * <br> HeadURL: not available     
 * <br> Revision: not available

 ****************************************************************************/


/**************************************************************************** 
* INCLUDES 
****************************************************************************/ 
#include "configureRunTimeStats.h"
#include <main.h>
#include <FreeRTOS.h>
/**************************************************************************** 
* DEFINES 
****************************************************************************/ 


/**************************************************************************** 
 GLOBALS 
****************************************************************************/ 
extern TIM_HandleTypeDef htim14;
/**************************************************************************** 
 FUNCTION DECLARATIONS 
****************************************************************************/ 
 

/**************************************************************************** 
 FUNCTION IMPLEMENTATIONS 
****************************************************************************/ 

void configureTimerForRunTimeStats()
{
  configASSERT(HAL_OK == HAL_TIM_Base_Start(&htim14));
}


uint32_t getRunTimeCounterValue()
{
  const uint32_t res = __HAL_TIM_GET_COUNTER(&htim14);
  return res;
}
