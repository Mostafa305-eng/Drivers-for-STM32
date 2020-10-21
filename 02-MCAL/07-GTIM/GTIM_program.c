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


#include "GTIM_interface.h"
#include "GTIM_config.h"
#include "GTIM_private.h"


/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/

Ptrfunc PTR_TIM2_CallBck;
Ptrfunc PTR_TIM3_CallBck;
Ptrfunc PTR_TIM4_CallBck;


/************************************************************************/
/*				  		 FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/******************************************************************************
 * fun
 * Input: Pointer to a structure contains the information needed to the required timer.. 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Initiates the module.
 *
 **************************************************************************/
void GTIM_Init(str_GTIM_cfg_t * str_GTIM_cfg)
{
	switch(str_GTIM_cfg->GTIM_TimerNo)
	{
		case TIM2 :
		
			if ( (str_GTIM_cfg->GTIM_Polling_Or_Interrupt == GTIM_INTERRUPT_MODE) && ( str_GTIM_cfg->ptrf_GTIM_Cbk != NULL ))
			{
			 SET_BIT(TIM2_DIER,0);   /* SET UPDATE INTERRUPT ENABLE BIT */
			 PTR_TIM2_CallBck = str_GTIM_cfg->ptrf_GTIM_Cbk;
			}
			else 
			{
			}


			if(str_GTIM_cfg->GTIM_PeriodMode == PERIODIC)
			{
				CLR_BIT(TIM2_CR1,3);   /* clear one pulse mode bit*/
			}
			else if (str_GTIM_cfg->GTIM_PeriodMode == ONE_PULSE_MODE)
			{
				SET_BIT(TIM2_CR1,3);   /* SET one pulse mode bit*/
			}
			else 
			{
				
			}
			TIM2_PSC = str_GTIM_cfg-> GTIM_PREScalerValue;
			break;
	
	
		case TIM3 :
		
			if ( (str_GTIM_cfg->GTIM_Polling_Or_Interrupt == GTIM_INTERRUPT_MODE) && ( str_GTIM_cfg->ptrf_GTIM_Cbk != NULL ))
			{
			 SET_BIT(TIM3_DIER,0);   /* SET UPDATE INTERRUPT ENABLE BIT */
			 PTR_TIM3_CallBck = str_GTIM_cfg->ptrf_GTIM_Cbk;
			}
			else 
			{
			}


			if(str_GTIM_cfg->GTIM_PeriodMode == PERIODIC)
			{
				CLR_BIT(TIM3_CR1,3);   /* clear one pulse mode bit*/
			}
			else if (str_GTIM_cfg->GTIM_PeriodMode == ONE_PULSE_MODE)
			{
				SET_BIT(TIM3_CR1,3);   /* SET one pulse mode bit*/
			}
			else 
			{
				
			}
			
			TIM3_PSC = str_GTIM_cfg-> GTIM_PREScalerValue;
			break;	

		case TIM4 :

			if ( (str_GTIM_cfg->GTIM_Polling_Or_Interrupt == GTIM_INTERRUPT_MODE) && ( str_GTIM_cfg->ptrf_GTIM_Cbk != NULL ))
			{
			 SET_BIT(TIM4_DIER,0);   /* SET UPDATE INTERRUPT ENABLE BIT */
			 PTR_TIM4_CallBck = str_GTIM_cfg->ptrf_GTIM_Cbk;
			}
			else
			{
			}


			if(str_GTIM_cfg->GTIM_PeriodMode == PERIODIC)
			{
				CLR_BIT(TIM4_CR1,3);   /* clear one pulse mode bit*/
			}
			else if (str_GTIM_cfg->GTIM_PeriodMode == ONE_PULSE_MODE)
			{
				SET_BIT(TIM4_CR1,3);   /* SET one pulse mode bit*/
			}
			else
			{

			}

			TIM4_PSC = str_GTIM_cfg-> GTIM_PREScalerValue;
			break;

	}


}



 /****************************************************************************
 * Input: 
		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function starts the timer.
 * 							
 ***************************************************************************/
void GTIM_Start(uint8 GTIM_TimerNo)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			SET_BIT(TIM2_CR1,0); /* set counter enable bit to start the timer */
			break;

		case TIM3 :
			SET_BIT(TIM3_CR1,0); /* set counter enable bit to start the timer */
			break;

		case TIM4 :
			SET_BIT(TIM4_CR1,0); /* set counter enable bit to start the timer */
			break;
	}		
}



 /****************************************************************************
 * Input: 
		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function stops the timer.
 * 							
 ***************************************************************************/
void GTIM_Stop(uint8 GTIM_TimerNo)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			CLR_BIT(TIM2_CR1,0); /* clear counter enable bit to stop the timer */
			break;

		case TIM3 :
			CLR_BIT(TIM3_CR1,0); /* clear counter enable bit to stop the timer */
			break;

		case TIM4 :
			CLR_BIT(TIM4_CR1,0); /* clear counter enable bit to stop the timer */
			break;

	}		
}



/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * 	Data: A variable of type bool returns if the flag of the systick is raised or not.
 * In/Out:			
 * Return: 			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 *****************************************************************************************/
void GTIM_GetStatus(uint8 GTIM_TimerNo,bool* Data)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			* Data = GET_BIT(TIM2_SR,0); /* read update interrupt flag bit*/
			if(*Data == TRUE)
			{
				CLR_BIT(TIM2_SR,0);
			}
			break;

		case TIM3 :
			* Data = GET_BIT(TIM3_SR,0); /* read update interrupt flag bit*/
			if(*Data == TRUE)
			{
				CLR_BIT(TIM3_SR,0);
			}
			break;

		case TIM4 :
			* Data = GET_BIT(TIM4_SR,0); /* read update interrupt flag bit*/
			if(*Data == TRUE)
			{
				CLR_BIT(TIM4_SR,0);
			}
			break;

	}
}


/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * 	Data: This is the output variable of the function which holds the current value of the systick .
 * In/Out:			
 * Return: 			
 * Description: This function is used to return the current value of the systick .
 * 							
 *****************************************************************************************/
void GTIM_GetValue(uint8 GTIM_TimerNo, uint32 * Data)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			* Data = TIM2_CNT;
			break;

		case TIM3 :
			* Data = TIM3_CNT;
			break;

		case TIM4 :
			* Data = TIM4_CNT;
			break;

	}

}


/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * 		Data: This is the  variable of the function which holds the current that will be set in systick  .
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to set the current value of the counter .
 * 							
 *****************************************************************************************/
void GTIM_UpdateCounter(uint8 GTIM_TimerNo, uint16  Data)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			TIM2_CNT = Data ;
			break;

		case TIM3 :
			TIM3_CNT = Data ;
			break;

		case TIM4 :
			TIM4_CNT = Data ;
			break;

	}
}

/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * 		Data: This is the  variable of the function which holds the current that will be set in systick  .
 *      BufferState : BUFFERED or NOTBUFFERED
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to set the current Preload value.
 * 							
 *****************************************************************************************/
void GTIM_UpdatePreload(uint8 GTIM_TimerNo, uint16  Data ,uint8 BufferState)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			if(BufferState == BUFFERED)
			{
				SET_BIT(TIM2_CR1,7); /*set AUTO-relod preload enable bit*/
			}
			else if (BufferState == NOTBUFFERED)
			{
				CLR_BIT(TIM2_CR1,7); /*set AUTO-relod preload enable bit*/
			}
			TIM2_ARR = Data ;
			break;

		case TIM3 :
			if(BufferState == BUFFERED)
			{
				SET_BIT(TIM3_CR1,7); /*set AUTO-relod preload enable bit*/
			}
			else if (BufferState == NOTBUFFERED)
			{
				CLR_BIT(TIM3_CR1,7); /*set AUTO-relod preload enable bit*/
			}
			TIM3_ARR = Data ;
			break;

		case TIM4 :
			if(BufferState == BUFFERED)
			{
				SET_BIT(TIM4_CR1,7); /*set AUTO-relod preload enable bit*/
			}
			else if (BufferState == NOTBUFFERED)
			{
				CLR_BIT(TIM4_CR1,7); /*set AUTO-relod preload enable bit*/
			}
			TIM4_ARR = Data ;
			break;
	}	
}



/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to generates an update by software .
 * 							
 *****************************************************************************************/
void GTIM_SetTimerFlag(uint8 GTIM_TimerNo)
{
	switch (GTIM_TimerNo)
	{
		case TIM2 :
			SET_BIT(TIM2_EGR,0);
			break;

		case TIM3 :
			SET_BIT(TIM3_EGR,0);
			break;

		case TIM4 :
			SET_BIT(TIM4_EGR,0);
			break;

	}
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
/*void GTIM_GetTickTime(float32 *Time)
{
		if (u8_GTIM_CLKSrc == AHB_DIV_8_SRC)
		{
			* Time = (1.00*8.00)/(F_CPU_MHZ);
		}
		else if (u8_GTIM_CLKSrc == AHB_SRC)
		{
			* Time = (1.00)/(F_CPU_MHZ);
		}
		else
		{
		}
}*/






void TIM2_IRQHandler(void)
{
	if(NULL != PTR_TIM2_CallBck)
	{
		PTR_TIM2_CallBck();
	}
	CLR_BIT(TIM2_SR,0); /* clear interrupt flag*/

}


void TIM3_IRQHandler(void)
{
	if(NULL != PTR_TIM3_CallBck)
	{
		PTR_TIM3_CallBck();
	}
	CLR_BIT(TIM3_SR,0); /* clear interrupt flag*/
}

void TIM4_IRQHandler(void)
{
	if(NULL != PTR_TIM4_CallBck)
	{
		PTR_TIM4_CallBck();
	}
	CLR_BIT(TIM4_SR,0); /* clear interrupt flag*/

}

