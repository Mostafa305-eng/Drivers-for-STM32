/*
 * File:   STP_program.c
 * Author: Metwaly
 *
 * Created on Sep 29, 2020, 9:55 PM
 */

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "STP_interface.h"
#include "STP_private.h"
#include "STP_config.h"

#include "DIO_interface.h"



/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define SHIFT_CLK_HIGH			4
#define SHIFT_CLK_LOW			5
#define STORAGE_CLK_HIGH		6
#define STORAGE_CLK_LOW			7

#define EMPTY					10
#define FULL					11

/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/
sint8 s8ShiftCounter=7;
uint8 u8ClkState=SHIFT_CLK_LOW;
uint8 u8BufferState=EMPTY;
uint8 u8DataToSend=0;

/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the Pins of the STP and the timer will be used 
 * 
 *@note : you should enable the clock of the required Timer and the required port
 *****************************************************************************/
void STP_voidInit(void)
{
	/* Init I/O Pins */
	DIO_VoidPinInit(STP1_SERIAL_DATA,OUTPUT_SPEED_2MHZ_PP);
	DIO_VoidPinInit(STP1_SHIFT_CLOCK,OUTPUT_SPEED_2MHZ_PP);
	DIO_VoidPinInit(STP1_STORE_CLOCK,OUTPUT_SPEED_2MHZ_PP);
	

}



/*******************************************************************************
 * Description: send the bit to data pin and toggle the clk of the storage and shift clk
 *
 * @note : this function must be called in the system tick handler or in the 
 *          super loop handler every 1 MS
 *****************************************************************************/
void STP_voidUpdate(void)
{
	if(u8BufferState==FULL)
	{
		switch (u8ClkState) 
		{
			case SHIFT_CLK_LOW:
				if(s8ShiftCounter >=0)
				{
					DIO_VoidPinWrite(STP1_SERIAL_DATA, GET_BIT(u8DataToSend,s8ShiftCounter) );
					s8ShiftCounter--;	
					DIO_VoidPinToggle(STP1_SHIFT_CLOCK);
					u8ClkState=SHIFT_CLK_HIGH;
				}
				else
				{
					u8ClkState=STORAGE_CLK_HIGH;
					s8ShiftCounter=7;
				}
				break;
				
			case SHIFT_CLK_HIGH :
				DIO_VoidPinToggle(STP1_SHIFT_CLOCK);
				u8ClkState=SHIFT_CLK_LOW;
				break;
			
			case STORAGE_CLK_HIGH :
				DIO_VoidPinToggle(STP1_STORE_CLOCK);
				u8ClkState=STORAGE_CLK_LOW;
				break;
					
			case STORAGE_CLK_LOW :
				DIO_VoidPinToggle(STP1_STORE_CLOCK);
				u8ClkState=SHIFT_CLK_LOW;
				u8BufferState=EMPTY;
				break;
					
			default :
				break;
		}
	}
			
}



/*****************************************************************************
 * Description: Send the data  
 * @param Copy_u8Data: the data will be sent 
 *
 *@note : this function mustn't call before 20 MS after last call if you work on 8_bit mode 
 *		 , otherwise the data won't be written 
 *****************************************************************************/
void STP_voidSendAsync(uint8 Copy_u8Data)
{
	if(u8BufferState == EMPTY)
	{
		u8DataToSend = Copy_u8Data;
		u8BufferState = FULL;
	}
}







