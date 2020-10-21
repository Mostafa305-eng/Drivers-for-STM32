/*
 * SCHD.h
 *
 * Created: 1/11/2020 6:21:48 PM
 *  Author: Mostafa Metwaly
 */ 

#ifndef SCHD_INTERFACE_H_
#define SCHD_INTERFACE_H_






/************************************************************************/
/*						FUNCTIONS' PROTOTYPES		        */
/************************************************************************/



/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: Initiates the Schedular.
 **************************************************************************/

void SCHD_Init(void);







/******************************************************************************
 * fun
 * Input:  
 * Output:
 * In/Out:			
 * Return: 			
 * Description: call the functions when their time have come (Schedular main loop).
 * 							
 **************************************************************************/

void SCHD_RUN( void );






/******************************************************************************
 * fun
 * Input:  
 *		----> Func_ptr	: pointer to task which required to excute
 *		----> period	: the time of the period between each call
 *							===>if the period is zero , it will excute the task only
 *								once	
 *		----> priority	: determine the pirioty of the task 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: create the task and make the OS sees it .
 * 							
 **************************************************************************/

void SCHD_CreateTask( Ptrfunc Ptrfunc_Task,uint16 u16_StartTime, uint16 u16_Period ,\
						uint8 u8_Priority );





/******************************************************************************
 * fun
 * Input:  
 *		----> Func_ptr	: pointer to Task which required to deleted
 * Output:
 * In/Out:			
 * Return: 
 * Description: delete the entered task from OS .
 * 							
 **************************************************************************/

void SCHD_Delete( Ptrfunc Ptrfunc_Task  );





#endif /* SCHD_H_ */