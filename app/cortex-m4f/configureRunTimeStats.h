/****************************************************************************
 * @copyright Copyright: Testo SE & Co. KGaA, 79822 Titisee-Neustadt
 * @file configureRunTimeStats.h
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

#pragma once

/*************************************************************************** 
* INCLUDES 
***************************************************************************/ 
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



/*************************************************************************** 
* DEFINES 
***************************************************************************/ 


/*************************************************************************** 
* GLOBALS 
***************************************************************************/ 

 
/*************************************************************************** 
* FUNCTION DECLARATIONS 
***************************************************************************/ 

/**
 * @fn void configureTimerForRunTimeStats()
 * @brief configures the runtime stats counter
 *
 */
void configureTimerForRunTimeStats();

/**
 * @fn uint32_t getRunTimeCounterValue()
 * @brief Returns the current runtimevalue
 *
 * @return current runtime counter value
 */
uint32_t getRunTimeCounterValue();


#ifdef __cplusplus
}
#endif //__cplusplus


