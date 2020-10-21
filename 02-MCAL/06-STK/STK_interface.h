/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 22 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H






/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/
#define 	AHB_SRC							1
#define 	AHB_DIV_8_SRC					2




#define		STK_POLLING_MODE				0
#define		STK_INTERRUPT_MODE				1


/************************************************************************/
/*			  Structures Definitions		        */
/************************************************************************/

typedef struct str_STK_cfg_t
{
	uint8 STK_Polling_Or_Interrupt;  /*STK_INTERRUPT_MODE  or STK_POLLING_MODE*/
	uint8 STK_CLKSource;			/* AHB_DIV_8_SRC or AHB_SRC*/
	Ptrfunc ptrf_STK_Cbk;
}str_STK_cfg_t;



/************************************************************************/
/*		         		 	FUNCTIONS' PROTOTYPES				        */
/************************************************************************/



/******************************************************************************
 * fun
 * Input: Pointer to a structure contains the information needed to initialize the systick. 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Initiates the module.
 *
 **************************************************************************/
 void STK_Init(str_STK_cfg_t * str_STK_cfg);
 
 
 
 
 /****************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function starts the systick.
 * 							
 ***************************************************************************/
void STK_Start();



 /****************************************************************************
 * Input: 
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function stops the systick.
 * 							
 ***************************************************************************/
void STK_Stop();



/*****************************************************************************************
 * Input: 
 * Output:
 * 	Data: A variable of type bool returns if the flag of the systick is raised or not.
 * In/Out:			
 * Return: 			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 *****************************************************************************************/
void STK_GetStatus(bool* Data);



/*****************************************************************************************
 * Input: 
 * Output:
 * 	Data: This is the output variable of the function which holds the current value of the systick .
 * In/Out:			
 * Return: 			
 * Description: This function is used to return the current value of the systick .
 * 							
 *****************************************************************************************/
void STK_GetValue( uint32 * Data);



/*****************************************************************************************
 * Input: 
 * 	Data: This is the  variable of the function which holds the current that will be set in systick  .
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to set the current value of the systick .
 * 							
 *****************************************************************************************/
void STK_SetValue( uint32  Data);



/******************************************************************************************
 * Input: 
 * Output:
 * 			Time : this is the time of one tick of the timer in milliseconds 
 * In/Out:			
 * Return:
 * Description: This function is used to return the value of the time of one tick.
 * 				
 *******************************************************************************************/
void STK_GetTickTime(float32 *Time);


#endif
