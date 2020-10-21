/**********************************************************/
/* Author    : Ahmed Assaf                                */
/* Date      : 19 August 2020                             */
/* Version   : V01                                        */
/**********************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

/************************************************************************/
/*						 		defines	                               */
/************************************************************************/

#define   WWDG_INT                  0 
#define   PVD_INT                   1 
#define   TAMPER_INT                2 
#define   RTC_INT                   3 
#define   FLASH_INT                 4 
#define   RCC_INT                   5 
#define   EXTI0_INT                 6 
#define   EXTI1_INT                 7 
#define   EXTI2_INT                 8 
#define   EXTI3_INT                 9 
#define   EXTI4_INT                 10
#define   DMA1_Channel1_INT         11
#define   DMA1_Channel2_INT         12
#define   DMA1_Channel3_INT			13
#define   DMA1_Channel4_INT  		14
#define   DMA1_Channel5_INT  		15
#define   DMA1_Channel6_INT  		16
#define   DMA1_Channel7_INT  		17
#define   ADC1_2_INT         		18
#define   USB_HP_CAN_TX_INT  		19
#define   USB_LP_CAN_RX_INT  		20
#define   CAN_RX1_INT        		21
#define   CAN_SCE_INT        		22
#define   EXTI9_5_INT        		23
#define   TIM1_BRK_INT       		24
#define   TIM1_UP_INT        		25
#define   TIM1_TRG_COM_INT   		26
#define   TIM1_CC_INT        		27
#define   TIM2_INT           		28
#define   TIM3_INT           		29
#define   TIM4_INT           		30
#define   I2C1_EV_INT        		31
#define   I2C1_ER_INT        		32
#define   I2C2_EV_INT        		33
#define   I2C2_ER_INT        		34
#define   SPI1_INT           		35
#define   SPI2_INT           		36
#define   USART1_INT         		37
#define   USART2_INT         		38
#define   USART3_INT         		39
#define   EXTI15_10_INT      		40
#define   RTCAlarm_INT       		41
#define   USBWakeup_INT      		42
#define   TIM8_BRK_INT       		43
#define   TIM8_UP_INT        		44
#define   TIM8_TRG_COM_INT   		45
#define   TIM8_CC_INT        		46
#define   ADC3_INT           		47
#define   FSMC_INT           		48
#define   SDIO_INT           		49
#define   TIM5_INT           		50
#define   SPI3_INT           		51
#define   UART4_INT          		52
#define   UART5_INT          		53
#define   TIM6_INT           		54
#define   TIM7_INT           		55
#define   DMA2_Channel1_INT  		56
#define   DMA2_Channel2_INT  		57
#define   DMA2_Channel3_INT  		58
#define   DMA2_Channel4_5_INT		59

/************************************************************************/
/*				  		 FUNCTIONS PROTOTYPES					        */
/************************************************************************/


/*****************************************************************************
*
*
*In/Out:
*Description: This function init the NVIC
*****************************************************************************/
void NVIC_voidInit(void);



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function enables the interrupt of certain peripheral
*****************************************************************************/
void NVIC_voidEnableInterrupt  (uint8 Copy_u8IntNumber);



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function disables the interrupt of certain peripheral
*****************************************************************************/
void NVIC_voidDisableInterrupt (uint8 Copy_u8IntNumber);



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function set the interrupt signal of certain peripheral
*****************************************************************************/
void NVIC_voidSetPendingFlag   (uint8 Copy_u8IntNumber);



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out:
*Description: This function clear the interrupt signal of certain peripheral
*****************************************************************************/
void NVIC_voidClearPendingFlag (uint8 Copy_u8IntNumber);



/*****************************************************************************
*Input: Copy_u8IntNumber -> to get Peripheral name
*
*In/Out: pu8FlagStatus  -> pointer to store the status of Active flag
*Description: This function gets the status of the active flag
*****************************************************************************/
void NVIC_u8GetActiveFlag        (uint8 Copy_u8IntNumber , uint8 * pu8FlagStatus);


/*****************************************************************************
*Input: Copy_s8IntID -> to get Peripheral ID
*		Copy_u8GroupPriority  ->  to set group priority 
*		Copy_u8SubPriority    ->  to set sub priority
*In/Out:
*Description: This function sets the groub and sub priority of certain peripheral
*****************************************************************************/
void NVIC_voidSetPriority(sint8 Copy_s8IntID , uint8 Copy_u8GroupPriority ,uint8 Copy_u8SubPriority );


#endif