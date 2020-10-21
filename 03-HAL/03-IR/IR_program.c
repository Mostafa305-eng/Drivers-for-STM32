/*
 * File:   IR_program.c
 * Author: Metwaly
 *
 * Created on Sep 20, 2020, 9:55 PM
 */

/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/

#include "std_types.h"
#include "common_macros.h"

#include "IR_interface.h"
#include "IR_private.h"
#include "IR_config.h"

#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "GTIM_interface.h"
#include "AFIO_interface.h"



/************************************************************************/
/*						        defines                                */
/************************************************************************/

#define DONE		20
#define NOT_DONE	22

#define NOT_STARTED	30
#define RECEIVING	31
#define REPEATING	32

/************************************************************************/
/*						Static Variables                               	*/
/************************************************************************/
volatile uint32  u32FrameData[50]  = {0};
volatile uint8   u8EdgeCounter     = 0;
volatile uint8   u8FrameValue     = 0;
volatile uint8   u8FrameState     = NOT_STARTED;
volatile uint8   u8ReadingState     = DONE ;
/*volatile uint8   u8FrameAddresse     = 0;*/


/************************************************************************/
/*				         FUNCTIONS IMPLEMENTATION				        */
/************************************************************************/



/*****************************************************************************
 * Description: Set variables to init values to start over and receive another frame
 * 
 *
 *****************************************************************************/
void IR_StartOver(void)
{
	u8FrameState=NOT_STARTED;
	u8EdgeCounter=0;

}


/*****************************************************************************
 * Description: save the time among the falling edges
 *
 *
 *****************************************************************************/
void voidGetFrame(void)
{
	uint32 u32Data;
	if(u8FrameState == NOT_STARTED)
	{
		u8ReadingState=NOT_DONE;
		u8FrameState=RECEIVING;
		GTIM_Start(IR_TIMER);
	}
	else if(u8FrameState == RECEIVING)
	{
		if(u8EdgeCounter < 30)
		{
			u32Data=0;
			GTIM_GetValue(TIM2, &u32Data);
			u32FrameData[u8EdgeCounter] = u32Data;
			u8EdgeCounter++;
		}
		else
		{
			u8FrameState = REPEATING;
		}
	}
	GTIM_UpdateCounter(IR_TIMER, 0);

}






/*****************************************************************************
 * Description: Initialize the Pins of the IR sensor and the timer will be used
 *
 *@note : you should enable the clock of the AFIO,required Timer ,required port
 *****************************************************************************/
void IR_voidInit(void)
{
	/* IR_PIN Input Floating        */
	DIO_VoidPinInit(IR_PORT,IR_PIN,INPUT_FLOATING);

	/* EXTI Initializtion */
	NVIC_voidInit();

#if IR_PIN == PIN0
	EXTI_voidInit (LINE0 ,  voidGetFrame);
	EXTI_voidEnableEXTI(LINE0);
	EXTI_voidSetSignalLatch(LINE0 , FALLING);
	/* Enable EXTI from NVIC */
	NVIC_voidEnableInterrupt(EXTI0_INT); /* EXTI */

#if IR_PORT == GPIOA
	MAFIO_voidSetEXTIConfiguration(0,MAP_GPIOA );
#elif IR_PORT == GPIOB
	MAFIO_voidSetEXTIConfiguration(0,MAP_GPIOB );
#elif IR_PORT == GPIOC
	MAFIO_voidSetEXTIConfiguration(0,MAP_GPIOC );
#endif

	#elif IR_PIN == PIN1
	EXTI_voidInit (LINE1 ,              );
	EXTI_voidEnableEXTI(LINE1);
	EXTI_voidSetSignalLatch(LINE1 , FALLING);
	/* Enable EXTI from NVIC */
	NVIC_voidEnableInterrupt(EXTI1_INT); /* EXTI */

#if IR_PORT == GPIOA
	MAFIO_voidSetEXTIConfiguration(1,MAP_GPIOA );
#elif IR_PORT == GPIOB
	MAFIO_voidSetEXTIConfiguration(1,MAP_GPIOB );
#elif IR_PORT == GPIOC
	MAFIO_voidSetEXTIConfiguration(1,MAP_GPIOC );
#endif

#endif
	
#if IR_TIMER == TIM2
	NVIC_voidEnableInterrupt(TIM2_INT);
#elif IR_TIMER == TIM3
	NVIC_voidEnableInterrupt(TIM3_INT);
#elif IR_TIMER == TIM4
	NVIC_voidEnableInterrupt(TIM4_INT);
#endif

	str_GTIM_cfg_t str_GTIM_cfg={IR_TIMER,GTIM_INTERRUPT_MODE,ONE_PULSE_MODE,7, IR_StartOver };

	GTIM_Init(& str_GTIM_cfg);
	GTIM_UpdatePreload(IR_TIMER, 30000 ,NOTBUFFERED	);

}



/*******************************************************************************
 * Description: translate the time of the signal edges from IR sensor to frames
 *
 * @note : this function must be called in the system tick handler or in the
 *          super loop handler
 *****************************************************************************/
void IR_voidUpdate(void)
{
	uint8 u8counter;
	if((u8ReadingState == NOT_DONE) &&  (u8FrameState != RECEIVING  ))
	{
		if ( (u32FrameData[0] >= 10000) && (u32FrameData[0] <= 14000)   )
		{
			for (u8counter=0;u8counter<8;u8counter++)
			{
				if (  (u32FrameData[17+u8counter] >= 2000) && (u32FrameData[17+u8counter] <=2300) )
				{
					SET_BIT(u8FrameValue,u8counter);
				}

				else
				{
					CLR_BIT(u8FrameValue,u8counter);
				}
			}
		}
		u32FrameData[0] = 0;
		u8ReadingState=DONE;

	}
}




/*****************************************************************************
 * Description: Get the value of the frame that was sent
 * @param u8Frame: it will hold the value of the frame
 *
 *****************************************************************************/
void IR_voidGetFrame(uint8 * u8Frame)
{
	*u8Frame = u8FrameValue;
	
	if(u8FrameState == NOT_STARTED)
	{
		u8FrameValue=0;
	}
}



