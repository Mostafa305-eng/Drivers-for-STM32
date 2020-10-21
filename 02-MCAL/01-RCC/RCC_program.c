/*********************************************************************************/
/* Author    : Ahmed Assaf                                                       */
/* Version   : V01                                                               */
/* Date      : 8 August 2020                                                     */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "common_macros.h"


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"



/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



/*****************************************************************************
 * Description: Initialize RCC peripheral 
 *
 *
 *
 *****************************************************************************/
void RCC_voidInitSysClock(void)
{
	#if     RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		RCC_CR   = 0x00010000; /* Enable HSE with no bypass */
		RCC_CFGR = 0x00000001; /* Enter HSE to CLK system */
		
	#elif   RCC_CLOCK_TYPE == RCC_HSE_RC
		RCC_CR   = 0x00050000; /* Enable HSE with bypass */
		RCC_CFGR = 0x00000001; /* Enter HSE to CLK system */
		
	#elif   RCC_CLOCK_TYPE == RCC_HSI
		RCC_CR   = 0x00000081; /* Enable HSI + Trimming = 0 */
		RCC_CFGR = 0x00000000;
	
	#elif   RCC_CLOCK_TYPE == RCC_PLL & RCC_PLL_MUL_VAL < 17 & RCC_PLL_MUL_VAL > 1
		
		#if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
			RCC_CR   = 0x00000081; /* Enable HSI + Trimming = 0 */
			RCC_CFGR = 0x00000002 | ((uint32)(RCC_PLL_MUL_VAL -2) << 18);

		
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_RC_DIV_2
			RCC_CR   = 0x00050000; /* Enable HSE with bypass */
			RCC_CFGR = 0x00030002 | ((uint32)(RCC_PLL_MUL_VAL -2) << 18);	/*Enter HSE/2 to PLL and the PLL MUL value*/
	
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_RC
			
			RCC_CR   = 0x00050000; /* Enable HSE with bypass */
			RCC_CFGR = 0x00010002 | ((uint32)(RCC_PLL_MUL_VAL -2) << 18);	/*Enter HSE to PLL and the PLL MUL value*/

		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_CRYSTAL_DIV_2
			RCC_CR   = 0x00010000; /* Enable HSE with no bypass */
			RCC_CFGR = 0x00030002 | ((uint32)(RCC_PLL_MUL_VAL -2) << 18);	/*Enter HSE/2 to PLL and the PLL MUL value*/
	
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_CRYSTAL
			RCC_CR   = 0x00010000; /* Enable HSE with no bypass */
			RCC_CFGR = 0x00010002 | ((uint32)((RCC_PLL_MUL_VAL -2) << 18));	/*Enter HSE to PLL and the PLL MUL value*/
		
		#endif
		
		SET_BIT(RCC_CR,24); /* enable PLL */
	#else
		#error("You chosed Wrong Clock type")
	#endif
}




/*****************************************************************************
 * Description: Enable the clock of the required peripheral
 * @param Copy_u8PerId: the required peripheral to enable its clock 
 *
 *
 *****************************************************************************/
void RCC_voidEnableClock( uint8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31)
	{
		SET_BIT(RCC_AHBENR  ,Copy_u8PerId); 
	}

	else if(Copy_u8PerId <= 63)
	{
		Copy_u8PerId %=32;
		SET_BIT(RCC_APB2ENR ,Copy_u8PerId);
	}

	else if(Copy_u8PerId <= 95)
	{
		Copy_u8PerId %=32;
		SET_BIT(RCC_APB1ENR,Copy_u8PerId);
	}
	else
	{
		/* Return Error */
	}

}



/*****************************************************************************
 * Description: Enable the clock of the required peripheral
 * @param Copy_u8PerId: the required peripheral to disable its clock 
 *
 *
 *****************************************************************************/
void RCC_voidDisableClock( uint8 Copy_u8PerId)
{
	if (Copy_u8PerId <= 31)
	{
		CLR_BIT(RCC_AHBENR  ,Copy_u8PerId); 
	}

	else if(Copy_u8PerId <= 63)
	{
		Copy_u8PerId %=32;
		CLR_BIT(RCC_APB1ENR ,Copy_u8PerId);
	}

	else if(Copy_u8PerId <= 95)
	{
		Copy_u8PerId %=32;
		CLR_BIT(RCC_APB2ENR,Copy_u8PerId);
	}
	else
	{
		/* Return Error */
	}

}

