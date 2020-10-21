/*
*	File name: common_macros.h
*	Author : Metwally
*
*/


#ifndef COMMON_MACROS_H_INCLUDED
#define COMMON_MACROS_H_INCLUDED


/*********************************/
/*            MACROS             */
/*********************************/

#define F_CPU (8000000UL)
#define F_CPU_MHZ 8.00
#define  _XTAL_FREQ 8000000


#define TICK_MS      20
/************************************************************************/
/*			       			BIT_MATH defines       	                    */
/************************************************************************/

/* Set Variable's Certin BIT High */

#define SET_BIT(VAR,BIT)          VAR |=  (1 << (BIT))

/* Set Variable's certain BIT Low */

#define CLR_BIT(VAR,BIT)          VAR &= ~(1 << (BIT)) 

/* Toggle Variable's Certain BIT */

#define TOG_BIT(VAR,BIT)          VAR ^=  (1 << (BIT))

/* Assign Variable's Certain BIT by a Certain Value */

#define ASSIGN_BIT(VAR,BIT_NB,VAL)  (VAR)=((VAR&(~(BIT_NB)))|(VAL&BIT_NB))

/* Get Variable's Certain BIT Value */

#define GET_BIT(VAR,BIT_NB) 		(((VAR)&(BIT_NB))/(BIT_NB))



#endif // COMMON_MACROS_H_INCLUDED
