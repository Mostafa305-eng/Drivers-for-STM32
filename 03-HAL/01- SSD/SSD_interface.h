
/* 
 * File:  SSD.h 
 * Author: Metwaly
 * Comments:
 * Revision history: 
 */


#ifndef SSD_H_
#define SSD_H_

/************************************************************************/
/*				 I				INCLUDES						        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

/************************************************************************/
/*								 DEFINES						        */
/************************************************************************/

#define FIRST_SSD       0
#define SECOND_SSD      1
#define THIRD_SSD       2
#define FOURTH_SSD      3

#define SSD_ON          1
#define SSD_OFF         0


/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/



/*****************************************************************************
 * Description: Initialize the x_SSD (where x First, second, third, fourth) as output
 * @param u8_SSD_ID: The SSD to be initialized and it takes
 * 				  one of defines
 *
 *****************************************************************************/
void SSD_Init(uint8 u8_SSD_ID);


/*******************************************************************************
 * Description: Update all x_SSD (where x First, second, third, fourth)  to show
 *              the required numbers
 *
 * @note : this function must be called in the system tick handler or in the 
 *          super loop handler
 *****************************************************************************/
void SSD_Update(void);



/*****************************************************************************
 * Description: Set the value that will be displayed on
 *              the x_SSD (where x First, second, third, fourth)
 * @param u8_SSD_ID: The SSD to be changed and it takes
 * 				  one of defines
 *        u8_SSD_Data : The number will be displayed on SSD
 *****************************************************************************/

void SSD_SetValue(uint8 u8_SSD_ID,uint8 u8_SSD_Data);




/*****************************************************************************
 * Description: Set the state of displaying on
 *  the x_SSD (where x First, second, third, fourth)
 * @param u8_SSD_ID: The SSD to be changed and it takes
 * 				  one of defines
 *        u8_SSD_State : The State of SSD ( ON or OFF )
 *****************************************************************************/

void SSD_SetState(uint8 u8_SSD_ID,uint8 u8_SSD_State);

/*****************************************************************************
 * Description: Get the state of required SSD  
 *  the x_SSD (where x First, second, third, fourth)
 * @param u8_SSD_ID: The SSD to be changed and it takes
 * 				  one of defines
 * OUTPUT :       u8_SSD_State : The State of SSD ( ON or OFF )
 *****************************************************************************/

void SSD_GetState(uint8 u8_SSD_ID,uint8 * u8_SSD_State);




/*****************************************************************************
 * Description: Turn off the required SSD  
 *  the x_SSD (where x First, second, third, fourth) immediately
 * @param u8_SSD_ID: The SSD to be turned off and it takes
 * 				  one of defines
 * OUTPUT :       
 *****************************************************************************/

void SSD_TurnOff(uint8 u8_SSD_ID);



#endif