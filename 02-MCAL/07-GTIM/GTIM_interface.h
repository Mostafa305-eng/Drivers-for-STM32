/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 22 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/

#ifndef GTIM_INTERFACE_H
#define GTIM_INTERFACE_H


/************************************************************************/
/*						 		defines	                               */
/************************************************************************/

#define		GTIM_POLLING_MODE				0
#define		GTIM_INTERRUPT_MODE				1

#define 	TIM2							2
#define 	TIM3							3
#define 	TIM4							4

#define		PERIODIC						15
#define 	ONE_PULSE_MODE					16


#define BUFFERED							20
#define NOTBUFFERED							22



/************************************************************************/
/*			  Structures Definitions		        */
/************************************************************************/

typedef struct str_GTIM_cfg_t
{
	uint8 GTIM_TimerNo;					/* TIM2 , 3 or 4*/
	uint8 GTIM_Polling_Or_Interrupt;  /*GTIM_INTERRUPT_MODE  or GTIM_POLLING_MODE*/
	uint8 GTIM_PeriodMode;				/* PERIODIC or ONE_PULSE_MODE*/
	uint16 GTIM_PREScalerValue;			/* clk of timer = Fclk of ABP1 /(PSValue[0:15]+1) */
	Ptrfunc ptrf_GTIM_Cbk;
}str_GTIM_cfg_t;



/************************************************************************/
/*		         		 	FUNCTIONS' PROTOTYPES				        */
/************************************************************************/



/******************************************************************************
 * fun
 * Input: Pointer to a structure contains the information needed to initialize the required timer. 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Initiates the module.
 *
 **************************************************************************/
 void GTIM_Init(str_GTIM_cfg_t * str_GTIM_cfg);
 
 
 
 
 /****************************************************************************
 * Input: 
		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function starts the timer.
 * 							
 ***************************************************************************/
void GTIM_Start(uint8 GTIM_TimerNo);



 /****************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * In/Out:			
 * Return: 
 * Description: This function stops the timer.
 * 							
 ***************************************************************************/
void GTIM_Stop(uint8 GTIM_TimerNo);



/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * 	Data: A variable of type bool returns if the flag of the systick is raised or not.
 * In/Out:			
 * Return: 			
 * Description: This function is used to return if the flag of the timer is raised or not.
 * 							
 *****************************************************************************************/
void GTIM_GetStatus(uint8 GTIM_TimerNo,bool* Data);



/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * 	Data: This is the output variable of the function which holds the current value of the systick .
 * In/Out:			
 * Return: 			
 * Description: This function is used to return the current value of the systick .
 * 							
 *****************************************************************************************/
void GTIM_GetValue(uint8 GTIM_TimerNo, uint32 * Data);



/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * 		Data: This is the  variable of the function which holds the current that will be set in systick  .
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to set the current value of the counter .
 * 							
 *****************************************************************************************/
void GTIM_UpdateCounter(uint8 GTIM_TimerNo, uint16  Data);


/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * 		Data: This is the  variable of the function which holds the current that will be set in systick  .
 *      BufferState : BUFFERED or NOTBUFFERED
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to set the current Preload value.
 * 							
 *****************************************************************************************/
void GTIM_UpdatePreload(uint8 GTIM_TimerNo, uint16  Data ,uint8 BufferState);



/*****************************************************************************************
 * Input: 
 *		GTIM_TimerNo : contains the required timer to be started
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function is used to generates an update by software .
 * 							
 *****************************************************************************************/
void GTIM_SetTimerFlag(uint8 GTIM_TimerNo);




/******************************************************************************************
 * Input: 
 * Output:
 * 			Time : this is the time of one tick of the timer in milliseconds 
 * In/Out:			
 * Return:
 * Description: This function is used to return the value of the time of one tick.
 * 				
 *******************************************************************************************/
/*void GTIM_GetTickTime(float32 *Time);*/


#endif
