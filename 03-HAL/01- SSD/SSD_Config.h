#ifndef SSD_CONFIG_H_INCLUDED
#define SSD_CONFIG_H_INCLUDED


/************************************************************************/
/*									INCLUDES					        */
/************************************************************************/
#include "DIO_interface.h"

/************************************************************************/
/*						        defines                                */
/************************************************************************/




#define NUMBER_OF_SSDS_USES 1

#define SSD_0_GPIO	GPIOA
#define SSD_0_BIT	PIN8

#define SSD_1_GPIO	GPIOA
#define SSD_1_BIT	PIN9

#define SSD_2_GPIO	GPIOA
#define SSD_2_BIT	PIN3

#define SSD_3_GPIO 	GPIOA
#define SSD_3_BIT	PIN2


#define SSD_DATA_GPIO GPIOA
#define SSD_DATA_MASK 0x00ff	

 
#define	SSD_PINDATA0	PIN0
#define	SSD_PINDATA1	PIN1
#define	SSD_PINDATA2	PIN2
#define	SSD_PINDATA3	PIN3
#define	SSD_PINDATA4	PIN4
#define	SSD_PINDATA5	PIN5
#define	SSD_PINDATA6	PIN6
#define	SSD_PINDATA7	PIN7 




#endif
