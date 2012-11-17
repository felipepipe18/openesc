// Adc.h

#include <stm32f10x_adc.h>

#define LEN_BUFF_INJECT	500

// offset for access to the measured values
#define I_IN		0
#define U_IN		1
#define U_BACKEMF_A	2
#define U_BACKEMF_B	3
#define U_BACKEMF_C	4

#define U_BACKEMF	2

#define Chanal_BACKEMF_A	ADC_Channel_0
#define Chanal_BACKEMF_B	ADC_Channel_1
#define Chanal_BACKEMF_C	ADC_Channel_2
#define	Chanal_UIN		ADC_Channel_3
#define Chanal_IIN		ADC_Channel_8

void	Adc_init(void);
//void 	InterruptHandlerADC(uint16_t Emf, uint16_t Uin);