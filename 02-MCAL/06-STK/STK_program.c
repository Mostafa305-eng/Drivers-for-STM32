/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 22 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/


/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"


#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"


/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/

Ptrfunc PTR_STK_CallBck;
uint8 	u8_STK_CLKSrc;


/************************************************************************/
/*				  		 FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/******************************************************************************
 * fun
 * Input: Pointer to a structure contains the information needed to initialize the systick. 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Initiates the module.
 *
 **************************************************************************/
void STK_Init(str_STK_cfg_t * str_STK_cfg)
{
	if ( (str_STK_cfg->STK_Polling_Or_Interrupt == STK_INTERRUPT_MODE) && ( str_STK_cfg->ptrf_STK_Cbk != NULL ))
	{
	 SET_BIT(STK_CTRL,1);
	 PTR_STK_CallBck = str_STK_cfg->ptrf_STK_Cbk;
	}
	else 
	{
	}


	if(str_STK_cfg->STK_CLKSource == AHB_DIV_8_SRC)
	{
		u8_STK_CLKSrc=AHB_DIV_8_SRC;
		CLR_BIT(STK_CTRL,2);		 
	}
	else if (str_STK_cfg->STK_CLKSource == AHB_SRC)
	{
		u8_STK_CLKSrc=AHB_SRC;
		SET_BIT(STK_CTRL,2);
	}
	else 
	{
		
	}
}



 /****************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function starts the systick.
 * 							
 ***************************************************************************/
void STK_Start()
{
	SET_BIT(STK_CTRL,0);
}



 /****************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function stops the systick.
 * 							
 ***************************************************************************/
void STK_Stop()
{
	CLR_BIT(STK_CTRL,0);
}



/*****************************************************************************************
 * Input: 
 * Output:
 * 	Data: A variable of type bool returns if the flag of the systick is raised or not.
 * In/Out:			
 * Return: 			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 *****************************************************************************************/
void STK_GetStatus(bool* Data)
{
	* Data = GET_BIT(STK_CTRL,16);
}

/*****************************************************************************************
 * Input: 
 * Output:
 * 	Data: This is the output variable of the function which holds the current value of the systick .
 * In/Out:			
 * Return: 			
 * Description: This function is used to return the current value of the systick .
 * 							
 *****************************************************************************************/
void STK_GetValue( uint32 * Data)
{
	* Data = STK_VAL;
}


/*****************************************************************************************
 * Input: 
 * 	Data: This is the  variable of the function which holds the current that will be set in systick  .
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to set the current value of the systick .
 * 							
 *****************************************************************************************/
void STK_SetValue( uint32  Data)
{
	STK_LOAD = Data ;
}


/******************************************************************************************
 * Input: 
 * Output:
 * 			Time : this is the time of one tick of the timer in milliseconds 
 * In/Out:			
 * Return:
 * Description: This function is used to return the value of the time of one tick.
 * 				
 *******************************************************************************************/
void STK_GetTickTime(float32 *Time)
{
		if (u8_STK_CLKSrc == AHB_DIV_8_SRC)
		{
			* Time = (1.00*8.00)/(F_CPU_MHZ);
		}
		else if (u8_STK_CLKSrc == AHB_SRC)
		{
			* Time = (1.00)/(F_CPU_MHZ);
		}
		else
		{
		}
}







void SysTick_Handler (void)
{
	if(NULL != PTR_STK_CallBck)
	{
		PTR_STK_CallBck();
	}
  // DO NOT loop, just return.
  // Useful in case someone (like STM HAL) inadvertently enables SysTick.
  ;
}
