/*********************************************************************************/
/* Author    : Ahmed Atia                                                        */
/* Version   : V01                                                               */
/* Date      : 12 August 2020                                                    */
/*********************************************************************************/



/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/


#include "std_types.h"
#include "common_macros.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"



/************************************************************************/
/*				  DIO FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/

/*****************************************************************************
*Input: Copy_u8port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*		Copy_u8pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- PIN8
*					- PIN9
*					- PIN10
*					- PIN11
*					- PIN12
*					- PIN13
*					- PIN14
*					- PIN15
*	Copy_u8Mode   -> The desired value
*					-INPUT_ANLOG               
*					-INPUT_FLOATING            
*					-INPUT_PULLUP_PULLDOWN  
*					-OUTPUT_SPEED_10MHZ_PP  
*                   -OUTPUT_SPEED_10MHZ_OD  
*                   -OUTPUT_SPEED_10MHZ_AFPP
*                   -OUTPUT_SPEED_10MHZ_AFOD
*					-OUTPUT_SPEED_2MHZ_PP  
*                   -OUTPUT_SPEED_2MHZ_OD  
*                   -OUTPUT_SPEED_2MHZ_AFPP
*                   -OUTPUT_SPEED_2MHZ_AFOD
*					-OUTPUT_SPEED_50MHZ_PP  
*                   -OUTPUT_SPEED_50MHZ_OD  
*                   -OUTPUT_SPEED_50MHZ_AFPP
*                   -OUTPUT_SPEED_50MHZ_AFOD
*
*In/Out:
*Description: This function can set the Mode of a full port 
* 			  or even one pin.
*****************************************************************************/
void DIO_VoidPinInit(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Mode)
{

	switch(Copy_u8Port)
	{
	case GPIOA:

		if(Copy_u8Pin <= 7 )
		{//low

			GPIOA_CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ));// R M W
			GPIOA_CRL |= ( Copy_u8Mode ) << ( Copy_u8Pin * 4 );

		}
		else if(Copy_u8Pin <=15 )
		{//high

			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOA_CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
			GPIOA_CRH |= ( Copy_u8Mode ) << ( Copy_u8Pin * 4 );
		}

		break;

	case GPIOB:

		if(Copy_u8Pin <= 7 )
		{//low

			GPIOB_CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );// R M W
			GPIOB_CRL |= ( Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;

		}
		else if(Copy_u8Pin <=15 )
		{//high
			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOB_CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
			GPIOB_CRH |= ( Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
		}
		break;
	case GPIOC:
		if(Copy_u8Pin <= 7 )
		{//low
			GPIOC_CRL &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );// R M W
			GPIOC_CRL |= ( Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
		}
		else if(Copy_u8Pin <=15 )
		{//high
			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOC_CRH &= ~ ( ( 0b1111 )    << ( Copy_u8Pin * 4 ) );
			GPIOC_CRH |= ( Copy_u8Mode ) << ( Copy_u8Pin * 4 )  ;
		}
		break;
	default :break;
	}


}




/*****************************************************************************
*Input: Copy_u8Port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*		Copy_u8pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- PIN8
*					- PIN9
*					- PIN10
*					- PIN11
*					- PIN12
*					- PIN13
*					- PIN14
*					- PIN15
*	Copy_u8Value   -> The desired value
*					-HIGH
*					-LOW
*
*In/Out:
*Description: This function can set or clear the value of a full port
* 			  or even one pin.
*****************************************************************************/
void DIO_VoidPinWrite (uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value){

	switch(Copy_u8Port)
	{
	case GPIOA:
		if( Copy_u8Value == HIGH ){

			SET_BIT( GPIOA_ODR , Copy_u8Pin );

		}else if( Copy_u8Value == LOW ){
			CLR_BIT(  GPIOA_ODR , Copy_u8Pin );
		}
		break;
		
	case GPIOB:
		if( Copy_u8Value == HIGH ){

			SET_BIT( GPIOB_ODR  , Copy_u8Pin );

		}else if( Copy_u8Value == LOW ){
			CLR_BIT( GPIOB_ODR  , Copy_u8Pin );
		}
		break;
		
	case GPIOC:
		if( Copy_u8Value == HIGH ){

			SET_BIT( GPIOC_ODR , Copy_u8Pin );

		}else if( Copy_u8Value == LOW ){
			CLR_BIT( GPIOC_ODR , Copy_u8Pin );
		}
		break;

	}

}






/******************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- PIN8
*					- PIN9
*					- PIN10
*					- PIN11
*					- PIN12
*					- PIN13
*					- PIN14
*					- PIN15
*Output: data -> the acquired data which could be PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
******************************************************************************/
void DIO_VoidPinRead (uint8 Copy_u8Port,uint8 Copy_u8Pin, uint8 *pu8_data)
{
	switch(Copy_u8Port)
	{
	case GPIOA:
		*pu8_data = GET_BIT( GPIOA_IDR , Copy_u8Pin );

		break;
	case GPIOB:

		*pu8_data = GET_BIT( GPIOB_IDR , Copy_u8Pin );

		break;
	case GPIOC:

		*pu8_data = GET_BIT( GPIOC_IDR , Copy_u8Pin );

		break;
	}
}






/******************************************************************************
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- PIN8
*					- PIN9
*					- PIN10
*					- PIN11
*					- PIN12
*					- PIN13
*					- PIN14
*					- PIN15
*					- FULL_PORT
*Output:  No output
*In/Out:
*Description: This function toggles the value of a full port
* 			  or even one pin.
*****************************************************************************/
void DIO_VoidPinToggle (uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
	switch(Copy_u8Port)
	{
	case GPIOA:
		TOG_BIT( GPIOA_ODR , Copy_u8Pin );
		break;
	
	case GPIOB:
		TOG_BIT( GPIOB_ODR  , Copy_u8Pin );
		break;
		
	case GPIOC:
		TOG_BIT( GPIOC_ODR , Copy_u8Pin );
		break;
	}

}



/*****************************************************************************
*Input: Copy_u8Port -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*		Copy_u16Mask -> Mask to be written .
*
*	Copy_u16Value   -> The desired value
*In/Out:
*Description: This function can set or clear the value of a maskes pins.
*****************************************************************************/
void DIO_VoidMaskWrite (uint8 Copy_u8Port, uint16 Copy_u16Mask, uint16 Copy_u16Value){

	switch(Copy_u8Port)
	{
	case GPIOA:
		GPIOA_ODR  &= ~(Copy_u16Mask);
		GPIOA_ODR  |= (Copy_u16Value);
		break;

	case GPIOB:
		GPIOB_ODR  &= ~(Copy_u16Mask);
		GPIOB_ODR  |= (Copy_u16Value);
		break;

	case GPIOC:
		GPIOC_ODR  &= ~(Copy_u16Mask);
		GPIOC_ODR  |= (Copy_u16Value);
		break;

	}

}
