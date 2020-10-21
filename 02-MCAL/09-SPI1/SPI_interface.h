/***************************************************************/
/* Author    : Ahmed Assaf                                     */
/* Version   : V01                                             */
/* Date      : 16 SEP 2020                                     */
/***************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H



/************************************************************************/
/*						 		defines	                               */
/************************************************************************/
/* SPI Mode */
#define SLAVE           (0)
#define MASTER          (1)


/* Data Mode */
#define RISING_LEAD_WRITING		0
#define FALLING_LEAD_WRITING	1
#define RISING_LEAD_READING		2
#define FALLING_LEAD_READING	3



/* Data order */
#define MSB             (0)
#define LSB             (1)

/* InterruptMode */
#define POLLING         (0)
#define INTERRUPT       (1)


/* NORMAL SPEED */
#define SPI_PRESCALER_2     (0)
#define SPI_PRESCALER_4     (1)
#define SPI_PRESCALER_8     (2)
#define SPI_PRESCALER_16    (3)
#define SPI_PRESCALER_32    (4)
#define SPI_PRESCALER_64    (5)
#define SPI_PRESCALER_128   (6)
#define SPI_PRESCALER_256   (7)



/* flags*/
#define BSY_FLAG		7
#define OVR_FLAG		6
#define MODF_FLAG		5
#define CRC_ERR_FLAG	4
#define UDR_FLAG		3
#define CHSIDE_FLAG		2
#define TXE_FLAG		1
#define REX_FLAG		0


/************************************************************************/
/*			  Structures Definitions		        */
/************************************************************************/

typedef struct {
	uint8 u8_SPIMode;		/* SLAVE or MASTER*/
	uint8 u8_ClkMode;
	uint8 u8_DataOrder;		/* MSB or LSB*/
	uint8 u8_InterruptMode;	/* POLLING or INTERRUPT */
	uint8 u8_Prescaler;		/* SPI_PRESCALER_2,4,8,16,32,64,128 or 256*/
	void (*CBK_Func) (void);
}SPI_Cfg_s_t;





/************************************************************************/
/*						FUNCTIONS' PROTOTYPES					        */
/************************************************************************/


/*****************************************************************************
 * Description: Initialize SPI module  
 * @param SPI_Cfg_s :  Pointer to Struct of SPI Configration
 * 
 *@note : you should enable the clock of SPI
 *****************************************************************************/
void SPI1_voidInit(SPI_Cfg_s_t * SPI_Cfg_s);





/*****************************************************************************
 * Description: Transmit one byte over SPI  
 *
 * @param u8_Data -> Byte to be sent
 * 
 *****************************************************************************/
void SPI1_voidSendByte(uint8 Copy_u8Data);




/*****************************************************************************
 * Description: Receive one byte over SPI 
 *
 * @param ptru8_Data -> points to where received byte is going to be stored in
 * 
 *****************************************************************************/
void SPI1_voidReceiveByte(uint8 *Copy_pu8Data);




/*****************************************************************************
 * Description: Get status of required flag 
 *
 * @param Copy_u8Flag -> holds the flag to be checked , it could be , or 
 *		  Copy_pbData-> points to where flag value is going to be stored in
 * 
 *****************************************************************************/
void SPI1_voidGetStatus(uint8 Copy_u8Flag,bool *Copy_pbData);


#endif
