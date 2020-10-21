/*********************************************************************************/
/* Author    : Ahmed Assaf                                                       */
/* Version   : V01                                                               */
/* Date      : 8 August 2020                                                     */
/*********************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H



/************************************************************************/
/*								 DEFINES						        */
/************************************************************************/

#define DMA1_PERI			0
#define DMA2_PERI			1
#define SRAM_PERI			2
#define FLITF_PERI			4
#define CRC_PERI			6
#define FSMC_PERI			8
#define SDIO_PERI			10

#define AFIO_PERI			32
#define IOPA_PERI			34
#define IOPB_PERI			35
#define IOPC_PERI			36
#define IOPD_PERI			37
#define IOPE_PERI			38
#define IOPG_PERI			40
#define IOPF_PERI			39
#define ADC1_PERI			41
#define ADC2_PERI			42
#define TIM1_PERI			43
#define SPI1_PERI			44
#define TIM8_PERI			45
#define USART1_PERI			46
#define ADC3_PERI			47
#define TIM9_PERI			51
#define TIM10_PERI			52
#define TIM11_PERI			53

#define TIM2_PERI			64
#define TIM3_PERI			65
#define TIM4_PERI			66
#define TIM5_PERI			67
#define TIM6_PERI			68
#define TIM7_PERI			69
#define TIM12_PERI			70
#define TIM13_PERI			71
#define TIM14_PERI			72
#define WWDG_PERI			75
#define SPI2_PERI			78
#define SPI3_PERI			79
#define USART2_PERI			81
#define USART3_PERI			82
#define USART4_PERI			83
#define USART5_PERI			84
#define I2C1_PERI			85
#define I2C2_PERI			86
#define USB_PERI			87
#define CAN_PERI			89
#define BKP_PERI			91
#define PWR_PERI			92
#define DAC_PERI			93



/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/



/*****************************************************************************
 * Description: Initialize RCC peripheral 
 *
 *
 *
 *****************************************************************************/
void RCC_voidInitSysClock(void);


/*****************************************************************************
 * Description: Enable the clock of the required peripheral
 * @param Copy_u8PerId: the required peripheral to enable its clock 
 *
 *
 *****************************************************************************/
void RCC_voidEnableClock( uint8 Copy_u8PerId);


/*****************************************************************************
 * Description: Enable the clock of the required peripheral
 * @param Copy_u8PerId: the required peripheral to disable its clock 
 *
 *
 *****************************************************************************/
void RCC_voidDisableClock( uint8 Copy_u8PerId);

#endif
