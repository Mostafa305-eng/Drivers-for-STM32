#ifndef IR_INTERFACE_H
#define IR_INTERFACE_H

/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize the Pins of the IR sensor and the timer will be used 
 * 
 *@note : you should enable the clock of the AFIO,required Timer ,required port
 *****************************************************************************/
void IR_voidInit(void);



/*******************************************************************************
 * Description: translate the time of the signal edges from IR sensor to frames
 *
 * @note : this function must be called in the system tick handler or in the 
 *          super loop handler
 *****************************************************************************/
void IR_voidUpdate(void);




/*****************************************************************************
 * Description: Get the value of the frame that was sent 
 * @param u8Frame: it will hold the value of the frame
 *
 *****************************************************************************/
void IR_voidGetFrame(uint8 * u8Frame);



#endif
