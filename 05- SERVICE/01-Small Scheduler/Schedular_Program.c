/*
 * SCHD.c
 *
 * Created: 1/11/2020 6:21:59 PM
 *  Author: Mostafa Metwaly
 */ 

/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/
#include "std_types.h"
#include "common_macros.h"

#include "Schedular_interface.h"
#include "Schedular_CONFG.h"

#include "STK_interface.h"
//#include "sleep.h"








/************************************************************************/
/*				 DEFINES			        */
/************************************************************************/

#define READY	1
#define WAITING	0

#define FOUND		1
#define NOTFOUND	0

#define ZEROVALUE	0

#define COUNTING	5
#define NOTCOUNTING	6

#define STARTED		10
#define NOTSTARTED	11

#define INIT		1
#define NOTINIT		0
#define CONV_FROM_MILLIS_TO_MICROS  1000.00

//#define SCHD_MAX_SIZE	100


/************************************************************************/
/*						Structures Definitions					        */
/************************************************************************/
typedef struct str_SCHD_info_t {
	Ptrfunc Ptrfunc_Task; 
	uint16 u16_Period;
	uint16 u16_FuncTimeCounter;
	uint8 u8_Priority;
	uint8 u8_ReadyFlag;
	uint8 u8_StartState;
	uint16 u16_StartTime;
	}str_SCHD_info_t ;




/************************************************************************/
/*				  Static Global variables				        */
/************************************************************************/

static str_SCHD_info_t gas_SCHD_list[SCHD_MAX_SIZE];
static uint8 u8_TaskCounter;
static uint32 u32_NoTimerTicks;
str_STK_cfg_t str_STK_cfg;
static uint8 u8_CountingState;
static uint8 u8_InitState;




/************************************************************************/
/*						FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/




void SCHD_SortTasks(void)
{
	uint8 u8_firstLoopCounter;
	uint8 u8_secondLoopCounter;
	
	str_SCHD_info_t str_Temp;
	

	
	for (u8_firstLoopCounter=ZEROVALUE ; u8_firstLoopCounter < u8_TaskCounter ; u8_firstLoopCounter++)
	{
		for (u8_secondLoopCounter = u8_firstLoopCounter + 1 ; u8_secondLoopCounter < u8_TaskCounter;\
		u8_secondLoopCounter++)
		{
			if (gas_SCHD_list[u8_firstLoopCounter].u8_Priority > \
			gas_SCHD_list[u8_secondLoopCounter].u8_Priority)
			{
				str_Temp=gas_SCHD_list[u8_firstLoopCounter];
				gas_SCHD_list[u8_firstLoopCounter]=gas_SCHD_list[u8_secondLoopCounter];
				gas_SCHD_list[u8_secondLoopCounter]=str_Temp;
			}
			else
			{
			}
		}
	}
	
}


/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: it will be executed in ISR of timer . it compares time counter of each 
 *				function after increasing it with the its u16_Period to check if it is ready
 *				or not 
 * 							
 **************************************************************************/
void SCHD_Tick_CBK(void)
{
	//uint8 u8_loopCounter=0;

	u8_CountingState=COUNTING;	

		
}






/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the module.
 * 							
 **************************************************************************/




void SCHD_Init(void)
{

	/*initialize the static variables*/
	u8_InitState=INIT;
	u32_NoTimerTicks=ZEROVALUE;
	u8_TaskCounter=ZEROVALUE;
	u8_CountingState=NOTCOUNTING;
	
	/*initialize the timer*/
	str_STK_cfg.STK_Polling_Or_Interrupt=STK_INTERRUPT_MODE;
	str_STK_cfg.STK_CLKSource=AHB_DIV_8_SRC;
	str_STK_cfg.ptrf_STK_Cbk =SCHD_Tick_CBK ;
	
	STK_Init(&str_STK_cfg);
	
	/*calculate number of ticks which the timer will count*/
	float32 f32_OneTickTime;
	STK_GetTickTime(&f32_OneTickTime);
	u32_NoTimerTicks=(SCHD_Resolution*(CONV_FROM_MILLIS_TO_MICROS))/f32_OneTickTime;
	 	

}





/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: call the functions when their time have come .
 * 							
 **************************************************************************/

void SCHD_RUN( void )
{
	uint8 volatile u8_loopCounter;
	STK_SetValue( u32_NoTimerTicks);

	STK_Start();

	while (TRUE)
	{
			/*counting flag will check if the ISR came or not */
		if (u8_CountingState==COUNTING)
		{
			for (u8_loopCounter=0 ; u8_loopCounter<u8_TaskCounter ; u8_loopCounter++)
			{
				/*increase the counters of each funticon with the unit time which is the 
				resolution the user entered*/
				gas_SCHD_list[u8_loopCounter].u16_FuncTimeCounter += SCHD_Resolution;
			
				/*check if  each function is started or not & if it is true compare
				with the start time not the period*/
				if (gas_SCHD_list[u8_loopCounter].u8_StartState==NOTSTARTED)
				{
					/*check if the start time of each function is came or not & if it is true make 
					the flag ready to execute the function*/
					if (gas_SCHD_list[u8_loopCounter].u16_FuncTimeCounter == \
						gas_SCHD_list[u8_loopCounter].u16_StartTime)
					{
						gas_SCHD_list[u8_loopCounter].u8_ReadyFlag=READY;
					}
					else
					{
						/*do nothing*/		
					}		
				} 
				else if (gas_SCHD_list[u8_loopCounter].u8_StartState==STARTED)
				{
					/*check if the time of each function is came or not & if it is true make 
					the flag ready to execute the function*/
					if (gas_SCHD_list[u8_loopCounter].u16_FuncTimeCounter == \
						gas_SCHD_list[u8_loopCounter].u16_Period)
					{
						gas_SCHD_list[u8_loopCounter].u8_ReadyFlag=READY;
					}
					else
					{
						/*do nothing*/		
					}
				}
				else
				{
					/*do nothing*/
				}
				
			}
			/*reset the flag of the isr*/
			u8_CountingState=NOTCOUNTING;
		}
		else
		{
			/*do nothing*/
		}



		for (u8_loopCounter=0;u8_loopCounter<u8_TaskCounter;u8_loopCounter++)
		{
			/*if the tick is come before finishing the execution of the function, 
			break the loop to check from the start again (from higher priority) */
			if (u8_CountingState==COUNTING)
			{
				break;
			} 
			else
			{
				/*do nothing*/
			}
			
			/*execute the function if it is ready & after executing it make the flag waiting and reset 
			the counter of the flag*/
			if (gas_SCHD_list[u8_loopCounter].u8_ReadyFlag==READY)
			{
				gas_SCHD_list[u8_loopCounter].Ptrfunc_Task();
				gas_SCHD_list[u8_loopCounter].u8_ReadyFlag=WAITING;
				/* if (gas_SCHD_list[u8_loopCounter].u8_StartState==NOTSTARTED)
						gas_SCHD_list[u8_loopCounter].u8_StartState=STARTED;
						gas_SCHD_list[u8_loopCounter].u16_FuncTimeCounter -= u16_StartTime;
				   else if (gas_SCHD_list[u8_loopCounter].u8_StartState==STARTED) 
						gas_SCHD_list[u8_loopCounter].u8_StartState=STARTED;
						gas_SCHD_list[u8_loopCounter].u16_FuncTimeCounter -= u16_Period ; */


				gas_SCHD_list[u8_loopCounter].u8_StartState=STARTED;
				gas_SCHD_list[u8_loopCounter].u16_FuncTimeCounter=ZEROVALUE;   
				
				
				/*if the function is executed only once "period = zero" , delete it by overwriting
				 the last function in the same place and decreasing the number of 
				 function counter "TaskCounter" */
				if (gas_SCHD_list[u8_loopCounter].u16_Period==ZEROVALUE)
				{
					SCHD_Delete(gas_SCHD_list[u8_loopCounter].Ptrfunc_Task);
					u8_loopCounter--;
				}
				else
				{
				}
			}
			else
			{
			}

		}

		/*if the ISR didn't come , the ECU should enter sleep mode */
		if ((u8_CountingState==NOTCOUNTING))
		{
			/*CPU_Sleep(IDLE);*/
		}
		else
		{
			/*do nothing*/	
		}
	
	}

}







/******************************************************************************
 * fun
 * Input:  
 *		----> Ptrfunc_Task	: pointer to function which required to excute
 *		----> u16_Period	: the time of the u16_Period between each call
 *		----> Repeat	: is this function will be repeated or one shot 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: start the time for the the entered function.
 * 							
 **************************************************************************/
void SCHD_CreateTask( Ptrfunc Ptrfunc_Task,uint16 u16_StartTime, uint16 u16_Period ,\
						uint8 u8_Priority )
{
/*	uint8 u8_retval=SCHD_BASE_ERR+SUCCESS;*/
	
	if (u8_InitState==NOTINIT)
	{
		/*u8_retval=SCHD_BASE_ERR+NOT_INITIALIZED_ERR;*/
	}
	/*check if the number of functions reaches the max or not*/
	else if (u8_TaskCounter == SCHD_MAX_SIZE)
	{
		/*u8_retval=SCHD_BASE_ERR+RESOURCE_NOT_SUPPORTED_ERR;*/
	}
	else if (NULL == Ptrfunc_Task)
	{
		/*u8_retval=SCHD_BASE_ERR+NULL_PTR_ERR;*/
	}
	else
	{
		/*save the parameter in the struct*/
		gas_SCHD_list[u8_TaskCounter].Ptrfunc_Task=Ptrfunc_Task;
		gas_SCHD_list[u8_TaskCounter].u16_Period=u16_Period;
		gas_SCHD_list[u8_TaskCounter].u8_Priority=u8_Priority;
		gas_SCHD_list[u8_TaskCounter].u16_FuncTimeCounter=ZEROVALUE;
		gas_SCHD_list[u8_TaskCounter].u8_StartState=NOTSTARTED;
		gas_SCHD_list[u8_TaskCounter].u16_StartTime=u16_StartTime;
		gas_SCHD_list[u8_TaskCounter].u8_ReadyFlag=WAITING;
		//gas_SCHD_list[u8_TaskCounter].u8_StartState=STARTED;
		
		/*if the user created task with zero start time , it will start in the first cycle*/
		if (gas_SCHD_list[u8_TaskCounter].u16_StartTime==ZEROVALUE)
		{
			gas_SCHD_list[u8_TaskCounter].u8_ReadyFlag=READY;
		} 
		else
		{
		}

		
		/*increase the number of tasks*/
		u8_TaskCounter++;
		
		/*sort the tasks depending on the priority*/
		SCHD_SortTasks();
	}
	
	/*return u8_retval;*/
}




/******************************************************************************
 * fun
 * Input:  
 *		----> Ptrfunc_Task	: pointer to function which required to stopped
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: stop the time for the the entered function.
 * 							
 **************************************************************************/

void SCHD_Delete( Ptrfunc Ptrfunc_Task  )
{
	uint8 u8_loopCounter;
	uint8 u8_foundFlag=NOTFOUND;
	
	/*uint8 u8_retval=SCHD_BASE_ERR+SUCCESS;*/
	
	
	if (NULL == Ptrfunc_Task)
	{
		/*u8_retval=SCHD_BASE_ERR+NULL_PTR_ERR;*/
	}
	else
	{
		/*search for the required function by its name to stop*/
		for (u8_loopCounter=0;u8_loopCounter<u8_TaskCounter;u8_loopCounter++)
		{
			if (gas_SCHD_list[u8_loopCounter].Ptrfunc_Task==Ptrfunc_Task)
			{
				u8_TaskCounter--;
				u8_foundFlag=FOUND;
				break;
			}
			else
			{
			}
		}

		if (u8_foundFlag==FOUND)
		{
			gas_SCHD_list[u8_loopCounter] = gas_SCHD_list[u8_TaskCounter];
			/*if it is the last element stop the timer*/
			if (u8_TaskCounter==0)   
			{
				STK_Stop();
			}
			else
			{	
			}
			
			SCHD_SortTasks();
		} 
		else
		{
			/*u8_retval=SCHD_BASE_ERR+INVALID_ARGU_ERR;*/
		}
	
	}
	/*return u8_retval;*/
}



