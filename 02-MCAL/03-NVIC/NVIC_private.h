/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 19 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define NVIC_ISER0       *((uint32*)0xE000E100) /* Enable External interrupts from 0  to 31 */
#define NVIC_ISER1       *((uint32*)0xE000E104) /* Enable External interrupts from 32 to 63 */

#define NVIC_ICER0       *((uint32*)0xE000E180)
#define NVIC_ICER1       *((uint32*)0xE000E184)

#define NVIC_ISPR0       *((uint32*)0xE000E200)
#define NVIC_ISPR1       *((uint32*)0xE000E204)

#define NVIC_ICPR0       *((uint32*)0xE000E280)
#define NVIC_ICPR1       *((uint32*)0xE000E284)

#define NVIC_IABR0       *((volatile uint32*)0xE000E300)
#define NVIC_IABR1       *((volatile uint32*)0xE000E304)
/*					without Dereference								*/
#define NVIC_IPR		  ((volatile uint8 *)0xE000E100 + 0x300)

#define SCB_AIRCR		 *((volatile uint32*)0xE000ED00 + 0x0C)



/* in (SCB => AIRCR) 4 bits for group and 0 sub => 4bits in (IPR) to determine group number	*/
#define MNVIC_GROUP_4_SUB_0      0x05FA0300
/* in (SCB => AIRCR) 3 bits for Group and 1 bit for sub										*/
#define MNVIC_GROUP_3_SUB_1      0x05FA0400
/* in (SCB => AIRCR) 2 bits for Group and 2 bit for sub										*/
#define MNVIC_GROUP_2_SUB_2      0x05FA0500
/* in (SCB => AIRCR) 1 bits for Group and 3 bit for sub										*/
#define MNVIC_GROUP_1_SUB_3      0x05FA0600
/* in (SCB => AIRCR) 0 group for 4 bits for sub												*/
#define MNVIC_GROUP_0_SUB_4      0x05FA0700

#endif
