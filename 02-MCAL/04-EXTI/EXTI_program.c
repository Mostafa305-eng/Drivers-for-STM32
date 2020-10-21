/**********************************************************/
/* Author    : Mostafa Metwaly                                */
/* Date      : 22 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/


/************************************************************************/
/*									 INCLUDES					        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"


/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/


Ptrfunc aptrf_LinesISRs[15];




/************************************************************************/
/*                       FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



/****************************************************************************
 * Function: EXTI_voidInit 
 * Inputs:	Copy_u8Line 		-> the external interrupt linex (where x is 0:15) will be configured									
 *			ExternInt_CBF_Ptr 	-> ISR will be executed when the interrupt signal arrives
 * Outputs: 
 * In Out: 
 * Return: 
 * Description: Initiate the required external interrupt and its ISR
 *	Enable the required external interrupt but to allow the interrupt global interrupt must be set
 *****************************************************************************/
void EXTI_voidInit (uint8 Copy_u8Line , Ptrfunc ExternInt_CBF_Ptr )
{
	if((ExternInt_CBF_Ptr != NULL) && (Copy_u8Line <= 15))
	{
		aptrf_LinesISRs[Copy_u8Line] = ExternInt_CBF_Ptr;
	}
	else
	{
	}
}



/*****************************************************************************
 * Function: EXTI_voidEnableEXTI
 * Inputs: Copy_u8Line -> Specify one of the external interrupt linex (where x is 0:15)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Enable the required external interrupt.
 ******************************************************************************/
void EXTI_voidEnableEXTI(uint8 Copy_u8Line)
{
	if (Copy_u8Line <= 15)
	{
		SET_BIT(EXTI->IMR , Copy_u8Line);
	}
	else 
	{
	}

}



/*****************************************************************************
 * Function: EXTI_voidDisableEXTI
 * Inputs: Copy_u8Line -> Specify one of the external interrupt lineX (where X is 0:15)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Disable the required external interrupt.
 ******************************************************************************/
void EXTI_voidDisableEXTI(uint8 Copy_u8Line)
{
	if (Copy_u8Line <= 15)
	{
		CLR_BIT(EXTI->IMR , Copy_u8Line);
	}
	else 
	{
	}
}



/*****************************************************************************
 * Function: EXTI_voidSetSignalLatch
 * Inputs: Copy_u8Line -> Set required event the external interrupt lineX (where X is 0:15) 
 *         Copy_u8Mode -> the required mode (RISING,FALLING or ON_CHANGE)                   
 * Outputs: 
 * In Out:
 * Return: 
 * Description: function is used to set event of external interrupt lineX (where X is 0:15). 
 * 				
 ******************************************************************************/
void EXTI_voidSetSignalLatch(uint8 Copy_u8Line , uint8 Copy_u8Mode)
{
	if (Copy_u8Line <= 15)
	{
		switch(Copy_u8Mode)
		{
			case RISING 	:	SET_BIT(EXTI -> RSTR , Copy_u8Line);
								CLR_BIT(EXTI -> FTSR , Copy_u8Line);    break;
			
			case FALLING	:	SET_BIT(EXTI -> FTSR , Copy_u8Line);
								CLR_BIT(EXTI -> RSTR , Copy_u8Line);   	break;
			
			case ON_CHANGE 	:	SET_BIT(EXTI -> RSTR , Copy_u8Line);
								SET_BIT(EXTI -> FTSR , Copy_u8Line); 	break;
		}	
	}
	else 
	{
	}

}


/*****************************************************************************
 * Function: EXTI_voidSwTrigger
 * Inputs: Copy_u8Line -> Specify one of the external interrupt lineX (where X is 0:15)
 * Outputs:
 * In Out:
 * Return: 
 * Description: set the interrupt signal of  the required external interrupt by software.
 ******************************************************************************/
void EXTI_voidSwTrigger(uint8 Copy_u8Line)
{
	if (Copy_u8Line <= 15)
	{
		SET_BIT(EXTI -> SWIER , Copy_u8Line);
	}
	else 
	{
	}
}








void EXTI0_IRQHandler(void)
{
	if(aptrf_LinesISRs[0] != NULL)
	{
		aptrf_LinesISRs[0]();
	}
	/* clear pending flag */
	SET_BIT(EXTI -> PR,0);

}

