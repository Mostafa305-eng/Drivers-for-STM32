#ifndef STP_CONFIG_H
#define STP_CONFIG_H

/* TIM2 , TIM3 or TIM4*/
#define STP_TIMER	TIM2	

/* 1 or 2*/
#define NUM_OF_STP	2

/* Please write pins in pairs port,pin */
#define STP1_SERIAL_DATA     GPIOA,0
#define STP1_SHIFT_CLOCK     GPIOA,1
#define STP1_STORE_CLOCK     GPIOA,2

#define STP2_SERIAL_DATA     GPIOA,3
#define STP2_SHIFT_CLOCK     GPIOA,4 
#define STP2_STORE_CLOCK     GPIOA,5


/* MODE_8_BITS or MODE_16_BITS*/
#define DATA_MODE	MODE_8_BITS


#endif
