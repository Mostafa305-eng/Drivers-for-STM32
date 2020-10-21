/*********************************************************************************/
/* Author    : Ahmed Atia                                                        */
/* Version   : V01                                                               */
/* Date      : 12 August 2020                                                    */
/*********************************************************************************/
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


/************************************************************************/
/*						PINS/BITS defines                               */
/************************************************************************/



#define GPIOA   0
#define GPIOB   1
#define GPIOC   2

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#define PIN8    8
#define PIN9    9
#define PIN10    10
#define PIN11    11
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15


#define FULL_PORT		0xFF


#define INPUT_ANLOG               0b0000
#define INPUT_FLOATING            0b0100
#define INPUT_PULLUP_PULLDOWN     0b1000

//For Speed 10
#define OUTPUT_SPEED_10MHZ_PP     0b0001
#define OUTPUT_SPEED_10MHZ_OD     0b0101
#define OUTPUT_SPEED_10MHZ_AFPP   0b1001
#define OUTPUT_SPEED_10MHZ_AFOD   0b1101

//For Speed 2
#define OUTPUT_SPEED_2MHZ_PP      0b0010
#define OUTPUT_SPEED_2MHZ_OD      0b0110
#define OUTPUT_SPEED_2MHZ_AFPP    0b1010
#define OUTPUT_SPEED_2MHZ_AFOD    0b1110

//For Speed 50
#define OUTPUT_SPEED_50MHZ_PP     0b0011
#define OUTPUT_SPEED_50MHZ_OD     0b0111
#define OUTPUT_SPEED_50MHZ_AFPP   0b1011
#define OUTPUT_SPEED_50MHZ_AFOD   0b1111


/************************************************************************/
/*				  GPIO FUNCTIONS PROTOTYPES				        */
/************************************************************************/



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
void DIO_VoidPinInit(uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Mode);




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
void DIO_VoidPinWrite (uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value);



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
void DIO_VoidPinRead (uint8 Copy_u8Port,uint8 Copy_u8Pin, uint8 *pu8_data);





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
*Output:  No output
*In/Out:
*Description: This function toggles the value of a full port
* 			  or even one pin.
*****************************************************************************/
void DIO_VoidPinToggle (uint8 Copy_u8Port, uint8 Copy_u8Pin);



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
void DIO_VoidMaskWrite (uint8 Copy_u8Port, uint16 Copy_u16Mask, uint16 Copy_u16Value);

#endif