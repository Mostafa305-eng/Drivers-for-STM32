#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the Pins of the STP and the timer will be used 
 * 
 *@note : you should enable the clock of the required Timer and the required port
 *****************************************************************************/
void STP_voidInit(void);



/*******************************************************************************
 * Description: send the bit to data pin and toggle the clk of the storage and shift clk
 *
 * @note : this function must be called in the system tick handler or in the 
 *          super loop handler every 1 MS
 *****************************************************************************/
void STP_voidUpdate(void);




/*****************************************************************************
 * Description: Send the data  
 * @param Copy_u8Data: the data will be sent 
 *
 *@note : this function mustn't call before 20 MS after last call if you work on 8_bit mode 
 *		 , otherwise the data won't be written 
 *****************************************************************************/
void STP_voidSendAsync(uint8 Copy_u8Data);



#endif
