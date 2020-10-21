/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 19 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/



/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"


/*****************************************************************************
*
*
*In/Out:
*Description: This function init the NVIC
*****************************************************************************/
void NVIC_voidInit(void)
{
	SCB_AIRCR = NO_OF_GROUPS_SUB ;
}



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function enables the interrupt of certain peripheral
*****************************************************************************/
void NVIC_voidEnableInterrupt  (uint8 Copy_u8IntNumber)
{
	if ( Copy_u8IntNumber <= 31)
	{
		NVIC_ISER0 = (1 << Copy_u8IntNumber);
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISER1 = (1 << Copy_u8IntNumber);
	}
	
	else
	{
		/* Return Error */
	}
	
}



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function disables the interrupt of certain peripheral
*****************************************************************************/
void NVIC_voidDisableInterrupt (uint8 Copy_u8IntNumber)
{
	if ( Copy_u8IntNumber <= 31)
	{
		NVIC_ICER0 = (1 << Copy_u8IntNumber);
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICER1 = (1 << Copy_u8IntNumber);
	}
	
	else
	{
		/* Return Error */
	}
	
}





/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function set the interrupt signal of certain peripheral
*****************************************************************************/
void NVIC_voidSetPendingFlag   (uint8 Copy_u8IntNumber)
{
	if ( Copy_u8IntNumber <= 31)
	{
		NVIC_ISPR0 = (1 << Copy_u8IntNumber);
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISPR1 = (1 << Copy_u8IntNumber);
	}
	
	else
	{
		/* Return Error */
	}
	
}



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function clear the interrupt signal of certain peripheral
*****************************************************************************/
void NVIC_voidClearPendingFlag (uint8 Copy_u8IntNumber)
{
	if ( Copy_u8IntNumber <= 31)
	{
		NVIC_ICPR0 = (1 << Copy_u8IntNumber);
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICPR1 = (1 << Copy_u8IntNumber);
	}
	
	else
	{
		/* Return Error */
	}
	
}

/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out: pu8FlagStatus  -> pointer to store the status of Active flag
*Description: This function gets the status of the active flag
*****************************************************************************/
void NVIC_u8GetActiveFlag        (uint8 Copy_u8IntNumber , uint8 * pu8FlagStatus)
{
	uint8 Local_u8Result = 0;

	if ( Copy_u8IntNumber <= 31)
	{
		Local_u8Result = GET_BIT(NVIC_IABR0,Copy_u8IntNumber);
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		Local_u8Result = GET_BIT(NVIC_IABR1,Copy_u8IntNumber);
	}
	
	else
	{
		/* Return Error */
	}
	
	* pu8FlagStatus = Local_u8Result;

}



/*****************************************************************************
*Input: Copy_s8IntID -> to get Peripheral ID
*		Copy_u8GroupPriority  ->  to set group priority 
*		Copy_u8SubPriority    ->  to set sub priority
*In/Out:
*Description: This function sets the groub and sub priority of certain peripheral
*****************************************************************************/
void NVIC_voidSetPriority(sint8 Copy_s8IntID , uint8 Copy_u8GroupPriority ,uint8 Copy_u8SubPriority )
{							/*0x05FA0400 3 Group & 1 sub priority*/
	uint8 Local_u8Priority = Copy_u8SubPriority|(Copy_u8GroupPriority<<((NO_OF_GROUPS_SUB - 0x05FA0300)/256));
	/* core peripheral 			*/
	if(Copy_s8IntID < 0)
	{

	}
	/* external peripheral		*/ 
	else if(Copy_s8IntID >= 0)
	{
		NVIC_IPR[Copy_s8IntID] = Local_u8Priority << 4 ;
	}
}
