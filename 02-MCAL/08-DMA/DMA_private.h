#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H



typedef struct
{
	volatile uint32 CCR;
	volatile uint32 CNDTR;
	volatile uint32 CPAR;
	volatile uint32 CMAR;
	volatile uint32 Reserved;
}DMA_Channel;

typedef struct
{
	volatile uint32 ISR;
	volatile uint32 IFCR;
	DMA_Channel Channel[7];
}DMA_t;

#define DMA	((volatile DMA_t*)0x40020000)



#endif
