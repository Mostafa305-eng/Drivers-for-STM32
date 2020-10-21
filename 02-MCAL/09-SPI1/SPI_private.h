/***************************************************************/
/* Author    : Ahmed Assaf                                     */
/* Version   : V01                                             */
/* Date      : 16 SEP 2020                                     */
/***************************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

typedef struct
{
	volatile uint32 CR1    ;
	volatile uint32 CR2    ;
	volatile uint32 SR     ;
	volatile uint32 DR     ;
	volatile uint32 CRCPR  ;
	volatile uint32 RXCRCR ;
	volatile uint32 TXCRCR ;
	volatile uint32 I2SCFGR;
	volatile uint32 I2SPR  ; 
	
}SPI_Register;


#define SPI1   ((SPI_Register*)0x40013000)

#endif