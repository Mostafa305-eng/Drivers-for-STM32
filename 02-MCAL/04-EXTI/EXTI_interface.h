/**********************************************************/
/* Author    : Mostafa Metwaly                                */
/* Date      : 22 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H






#define			RISING				0
#define			FALLING				1
#define			ON_CHANGE			2

#define			LINE0				0
#define			LINE1				1
#define			LINE2				2
#define			LINE3				3
#define			LINE4				4
#define			LINE5				5
#define			LINE6				6
#define			LINE7				7
#define			LINE8				8
#define			LINE9				9
#define			LINE10				10
#define			LINE11				11
#define			LINE12				12
#define			LINE13				13
#define			LINE14				14
#define			LINE15				15



/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/


/****************************************************************************
 * Function: EXTI_voidInit 
 * Inputs:	Copy_u8Line 		-> the external interrupt linex (where x is 0:15) will be configured									
 *			ExternInt_CBF_Ptr 	-> ISR will be executed when the interrupt signal arrives
 * Outputs: 
 * In Out: 
 * Return: 
 * Description: Initiate the required external interrupt and its ISR
 *	Enable the required external interrupt but to allow the interrupt global interrupt must be set
 *****************************************************************************/
void EXTI_voidInit (uint8 Copy_u8Line , Ptrfunc ExternInt_CBF_Ptr );


/*****************************************************************************
 * Function: EXTI_voidEnableEXTI
 * Inputs: Copy_u8Line -> Specify one of the external interrupt linex (where x is 0:15)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Enable the required external interrupt.
 ******************************************************************************/
void EXTI_voidEnableEXTI(uint8 Copy_u8Line);


/*****************************************************************************
 * Function: EXTI_voidDisableEXTI
 * Inputs: Copy_u8Line -> Specify one of the external interrupt lineX (where X is 0:15)
 * Outputs:
 * In Out:
 * Return: 
 * Description: Disable the required external interrupt.
 ******************************************************************************/
void EXTI_voidDisableEXTI(uint8 Copy_u8Line);


/*****************************************************************************
 * Function: EXTI_voidSetSignalLatch
 * Inputs: Copy_u8Line -> Set required event the external interrupt lineX (where X is 0:15) 
 *         Copy_u8Mode -> the required mode (RISING,FALLING or ON_CHANGE)                   
 * Outputs: 
 * In Out:
 * Return: 
 * Description: function is used to set event of external interrupt lineX (where X is 0:15). 
 * 				
 ******************************************************************************/
void EXTI_voidSetSignalLatch(uint8 Copy_u8Line , uint8 Copy_u8Mode);


/*****************************************************************************
 * Function: EXTI_voidSwTrigger
 * Inputs: Copy_u8Line -> Specify one of the external interrupt lineX (where X is 0:15)
 * Outputs:
 * In Out:
 * Return: 
 * Description: set the interrupt signal of  the required external interrupt by software.
 ******************************************************************************/
void EXTI_voidSwTrigger(uint8 Copy_u8Line);

#endif
