/*
*	File name: std_types.h
*	Author : Metwally
*
*/


#ifndef STD_TYPES_H_INCLUDED
#define STD_TYPES_H_INCLUDED

/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
//typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
//typedef signed long long sint64;
typedef volatile uint32* const reg_type;
typedef float float32;

typedef void(*Ptrfunc) (void) ;




/************************************************************************/
/*			  			 defining bool values                         	*/
/************************************************************************/
typedef uint8 bool;
#define FALSE 					0
#define TRUE 					1


/************************************************************************/
/*			    		 LOW/HIGH defines                 	            */
/************************************************************************/
#define LOW  					0
#define HIGH 					1


#endif // STD_TYPES_H_INCLUDED
