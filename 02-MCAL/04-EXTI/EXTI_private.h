/**********************************************************/
/* Author    : Mostafa Metwaly                                */
/* Date      : 22 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/


#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H


typedef struct{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RSTR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;
	
}EXTI_t;


#define EXTI ((volatile EXTI_t *) 0x40010400 )




#define			RISING				0
#define			FALLING				1
#define			ON_CHANGE			2


#endif
