#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/************************************************************************/
/*						 		defines	                               */
/************************************************************************/

#define BITS_8	0
#define BITS_16	1
#define BITS_32	2

#define VERY_HIGH_PRIORITY	3
#define HIGH_PRIORITY		2
#define MED_PRIORITY		1
#define LOW_PRIORITY		0

#define MEMORY_SRC			1
#define PERI_SRC			0


/************************************************************************/
/*			  Structures Definitions		        */
/************************************************************************/

typedef struct str_DMA_cfg_t
{
	uint8 Copy_u8DMAChannel;					/* 1 : 7*/
	uint8	Copy_u8ElementSizeMask;    /* 8BITS , 16BITS or 32BITS */
	uint8	Copy_u8SwPriority;			/* VERY_HIGH_PRIORITY , HIGH_PRIORITY ,
											MED_PRIORITY or LOW_PRIORITY */
	bool	Copy_bMemoryIncreament;
	bool	Copy_bPeriIncreament;
	bool	Copy_bCircular;
	bool 	Copy_bInterrupt;
	bool 	Copy_bSource;					/* MEMORY_SRC or PERI_SRC*/
	bool	Copy_bMem2Mem;
	uint16 	Copy_u16BlockLength;			/* no of bytes to be transfered*/
	Ptrfunc ptrf_DMA_Cbk;
}str_DMA_cfg_t;



/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the required DMA channel  
 * @param str_DMA_cfg: pointnet to struct which it will hold the 
 *						required config of the channel
 * 
 *@note : you should enable the clock of DMA
 *****************************************************************************/
void DMA_voidInit(str_DMA_cfg_t * str_DMA_cfg);




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
									uint32 * Copy_pu32PeriAddress );






/*******************************************************************************
 * Description: start DMA to transfer data of a certain channel
 *
 * @param Copy_u8Channel: it will hold the required channel 
 *
 *
 *****************************************************************************/
void DMA_voidStartTransaction(uint8 Copy_u8Channel);







#endif
