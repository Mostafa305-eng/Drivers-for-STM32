/*
 * File:   DMA_program.c
 * Author: Metwaly
 *
 * Created on Sep 24, 2020, 9:55 PM
 */

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_Config.h"




/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define DONE		20
#define NOT_DONE	22

#define NOT_STARTED	30
#define RECEIVING	31
#define REPEATING	32

/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/
Ptrfunc ptrf_DMA_Cbk[7]={NULL};


/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/





/*****************************************************************************
 * Description: Initialize the required DMA channel  
 * @param str_DMA_cfg: pointnet to struct which it will hold the 
 *						required config of the channel
 * 
 *@note : you should enable the clock of DMA
 *****************************************************************************/
void DMA_voidInit(str_DMA_cfg_t * str_DMA_cfg)
{
	if((str_DMA_cfg->Copy_u8DMAChannel > 0) && (str_DMA_cfg->Copy_u8DMAChannel < 8))
	{
		str_DMA_cfg->Copy_u8DMAChannel--;

		/* disable the channel so we can do write the config */
		CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,0);
		
		/* clear the memory size bits */
		CLR_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,0xF<<8);
		/* configure the source and distination to the same memory size */
		switch(str_DMA_cfg->Copy_u8ElementSizeMask)
		{
			case BITS_16:
				SET_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR
				,((BITS_16<<2) | BITS_16)<<8);
				break;
				
			case BITS_32:
				SET_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,
				((BITS_32<<2) | BITS_32)<<8);
				break;

			default :
				break;

		}

		/* clear channel prioirty level bits*/
		CLR_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,0x3<<12);
		/* configure the prioirty of the channel */
		switch(str_DMA_cfg->Copy_u8ElementSizeMask)
		{
			case VERY_HIGH_PRIORITY:
				SET_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,
				VERY_HIGH_PRIORITY<<12);
				break;
				
			case HIGH_PRIORITY:
				SET_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,
				HIGH_PRIORITY<<12);
				break;

			case MED_PRIORITY:
				SET_MASK_BITS(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,
				MED_PRIORITY<<12);
				break;


			default :
				break;

		}
		
		/* enable or disable the increament of the memory address*/
		if(str_DMA_cfg->Copy_bMemoryIncreament == TRUE)
		{
			SET_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,7);
		}
		else
		{
			CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,7);
		}

		/* enable or disable the increament of the Peripheral address*/
		if(str_DMA_cfg->Copy_bPeriIncreament == TRUE)
		{
			SET_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,6);
		}
		else
		{
			CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,6);
		}
		
		/* enable or disable the cirular mode*/
		if(str_DMA_cfg->Copy_bCircular == TRUE)
		{
			SET_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,5);
		}
		else
		{
			CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,5);
		}
		
		/* enable or disable the transfer complete interrupt*/
		if(str_DMA_cfg->Copy_bInterrupt == TRUE)
		{
			SET_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,1);
			/* if the pointer to callback func isn't null , save the address of it*/
			if(str_DMA_cfg->ptrf_DMA_Cbk != NULL)
			{
				ptrf_DMA_Cbk[str_DMA_cfg->Copy_u8DMAChannel]=str_DMA_cfg->ptrf_DMA_Cbk;
			}
		}
		else
		{
			CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,1);
		}
		
		/* determine if the memory is the source or the peripheral*/
		if(str_DMA_cfg->Copy_bSource == MEMORY_SRC)
		{
			SET_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,4);
		}
		else
		{
			CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,4);			
		}


		/* determine if the memory is the source or the peripheral*/
		if(str_DMA_cfg->Copy_bMem2Mem == TRUE)
		{
			SET_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,14);
		}
		else
		{
			CLR_BIT(DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CCR,14);
		}



		/* set the counter of data to be transfered */
		DMA->Channel[str_DMA_cfg->Copy_u8DMAChannel].CNDTR=str_DMA_cfg->Copy_u16BlockLength;
			
	}
	else 
	{
	}
}


/*******************************************************************************
 * Description: start DMA to transfer data of a certain channel
 *
 * @param 	Copy_u8Channel: it will hold the required channel
 *		  	Copy_pu32MemoryAddress : holds the start address of memory
 *			Copy_pu32PeriAddress : holds the start address of peripheral
 *
 *
 *****************************************************************************/
void DMA_voidSetChannelAddresses(uint8 Copy_u8Channel ,	uint32 * Copy_pu32MemoryAddress,
									uint32 * Copy_pu32PeriAddress )
{
	if((Copy_u8Channel > 0) && (Copy_u8Channel < 8))
	{

		Copy_u8Channel--;

		/* disable the channel so we can do write the config */
		CLR_BIT(DMA->Channel[Copy_u8Channel].CCR,0);
		
		/* store the addresses of memory and peripheral */
		DMA->Channel[Copy_u8Channel].CMAR = Copy_pu32MemoryAddress;
		DMA->Channel[Copy_u8Channel].CPAR = Copy_pu32PeriAddress;
	}
	else
	{
	}
}




/*******************************************************************************
 * Description: start DMA to transfer data of a certain channel
 *
 * @param Copy_u8Channel: it will hold the required channel 
 *
 *
 *****************************************************************************/
void DMA_voidStartTransaction(uint8 Copy_u8Channel)
{
	if((Copy_u8Channel > 0) && (Copy_u8Channel < 8))
	{

		Copy_u8Channel--;

		/* Enable the channel to start transfer */
		SET_BIT(DMA->Channel[Copy_u8Channel].CCR,0);
	}
	else
	{
	}
}	







void DMA1_Channel1_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[0] != NULL)
	{
		ptrf_DMA_Cbk[0]();
	}
	DMA->IFCR = 2<<0 ;
}

void DMA1_Channel2_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[1] != NULL)
	{
		ptrf_DMA_Cbk[1]();
	}
	DMA->IFCR = 2<<4 ;

}

void DMA1_Channel3_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[2] != NULL)
	{
		ptrf_DMA_Cbk[2]();
	}
	DMA->IFCR = 2<<8 ;
}

void DMA1_Channel4_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[3] != NULL)
	{
		ptrf_DMA_Cbk[3]();
	}
	DMA->IFCR = 2<<12 ;
}

void DMA1_Channel5_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[4] != NULL)
	{
		ptrf_DMA_Cbk[4]();
	}
	DMA->IFCR = 2<<16 ;
}

void DMA1_Channel6_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[5] != NULL)
	{
		ptrf_DMA_Cbk[5]();
	}
	DMA->IFCR = 2<<20 ;
}

void DMA1_Channel7_IRQHandler(void)
{
	if(ptrf_DMA_Cbk[6] != NULL)
	{
		ptrf_DMA_Cbk[6]();
	}
	DMA->IFCR = 2<<24 ;
}
