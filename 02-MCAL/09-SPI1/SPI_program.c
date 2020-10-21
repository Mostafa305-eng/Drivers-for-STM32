/***************************************************************/
/* Author    : Metwaly                                     */
/* Version   : V01                                             */
/* Date      : 29 SEP 2020                                     */
/***************************************************************/

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include "std_types.h"
#include "common_macros.h"


#include "DIO_interface.h"
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"


/************************************************************************/
/*						        defines                                */
/************************************************************************/


/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/
Ptrfunc ptrf_SPI_Cbk=NULL;
uint8 u8PeriMode;



/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize SPI module
 * @param SPI_Cfg_s :  Pointer to Struct of SPI Configration
 *
 *@note : you should enable the clock of SPI
 *****************************************************************************/
void SPI1_voidInit(SPI_Cfg_s_t * SPI_Cfg_s)
{
	/* clear master selection bit to configure */
	CLR_BIT(SPI1->CR1,2);
	if(SPI_Cfg_s->u8_SPIMode == MASTER)
	{
		/* if the spi is master , it will be set the master selec bit */
		SET_BIT(SPI1->CR1,2);
		/* set the software slave managment bit */
		SET_BIT(SPI1->CR1,9);
		/* init the pin which will enable the slave as an output */
		DIO_VoidPinInit(SPI1_SLAVE_PIN,OUTPUT_SPEED_2MHZ_PP);
		/* should set the SSI bit to work as master correctly */
		SET_BIT(SPI1->CR1,8);		
	}

	/* clear the phase and the polarity of the clk to determine the leading edge and writing or reading at it */
	CLR_MASK_BITS(SPI1->CR1,0x3);
	if( SPI_Cfg_s->u8_ClkMode == RISING_LEAD_WRITING)
	{
		SET_BIT(SPI1->CR1,0);
	}
	else if(SPI_Cfg_s->u8_ClkMode == RISING_LEAD_READING)
	{
	}
	else if(SPI_Cfg_s->u8_ClkMode == FALLING_LEAD_READING)
	{
		SET_BIT(SPI1->CR1,1);
	}
	else if(SPI_Cfg_s->u8_ClkMode == FALLING_LEAD_WRITING)
	{
		SET_BIT(SPI1->CR1,0);
		SET_BIT(SPI1->CR1,1);
	}


	/* clear frame  format bit to config  MSB or LSB first */
	CLR_BIT(SPI1->CR1,7);
	if(SPI_Cfg_s->u8_DataOrder==LSB)
	{
		SET_BIT(SPI1->CR1,7);
	}

	/*clear the prescaler bits to config */
	CLR_MASK_BITS(SPI1->CR1,7<<3);
	if((SPI_Cfg_s->u8_Prescaler >=0) &&(SPI_Cfg_s->u8_Prescaler <8))
	{
		SET_MASK_BITS(SPI1->CR1,SPI_Cfg_s->u8_Prescaler<<3);
	}

	/*clear the interrupt bits rx and tx */
	CLR_MASK_BITS(SPI1->CR1,3<<6);
	if(SPI_Cfg_s->u8_InterruptMode == INTERRUPT)
	{
		u8PeriMode=INTERRUPT;
		SET_MASK_BITS(SPI1->CR1,3<<6);
		if(SPI_Cfg_s->CBK_Func != NULL)
		{
			ptrf_SPI_Cbk = SPI_Cfg_s->CBK_Func;
		}
	}
	else
	{
		u8PeriMode=POLLING;
	}
	

}





/*****************************************************************************
 * Description: Transmit one byte over SPI
 *
 * @param u8_Data -> Byte to be sent
 *
 *****************************************************************************/
void SPI1_voidSendByte(uint8 Copy_u8Data)
{
	if(u8PeriMode==INTERRUPT)
	{
		DIO_VoidPinWrite(MSPI1_SLAVE_PIN,LOW);
		SPI1 -> DR = Copy_u8Data;
		/*DIO_VoidPinWrite(SPI1_SLAVE_PIN,HIGH);*/
	}
	else
	{
		DIO_VoidPinWrite(MSPI1_SLAVE_PIN,LOW);
		while(GET_BIT(SPI1->SR,1) == 0);
		SPI1 -> DR = Copy_u8Data;
		DIO_VoidPinWrite(SPI1_SLAVE_PIN,HIGH);
	}

}


/*****************************************************************************
 * Description: Receive one byte over SPI
 *
 * @param ptru8_Data -> points to where received byte is going to be stored in
 *
 *****************************************************************************/
void SPI1_voidReceiveByte(uint8 *Copy_pu8Data)
{
	if(u8PeriMode==INTERRUPT)
	{
		if(Copy_pu8Data != NULL)
		{
			*Copy_pu8Data = SPI1 -> DR ;
		}
	}
	else
	{
		while(GET_BIT(SPI1->SR,0));
		if(Copy_pu8Data != NULL)
		{
			*Copy_pu8Data = SPI1 -> DR ;
		}
	}
}




/*****************************************************************************
 * Description: Get status of required flag
 *
 * @param Copy_u8Flag -> holds the flag to be checked , it could be , or
 *		  Copy_pu8Data-> points to where flag value is going to be stored in
 *
 *****************************************************************************/
void SPI1_voidGetStatus(uint8 Copy_u8Flag,bool *Copy_pbData)
{
	if(Copy_pu8Data != NULL)
	{
		* Copy_pbData = GET_BIT(SPI1->SR,Copy_u8Flag);
	}
}
