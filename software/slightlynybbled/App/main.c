// main.c

#include <stm32f10x.h>
#include <stdint.h>
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>

static void InitClock(void);
static void InitGPIO(void);
static void InitNVIC(void);

void ControlEC_Task(void *param);
void Comm_Task(void *param);

int main(void)
{
	SystemInit();		// CMSIS
	InitClock();
	InitNVIC();
	InitGPIO();
	
	
	xTaskCreate(ControlEC_Task, "ControlEC_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(Comm_Task, "Comm_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
#ifndef NDEBUG
	//printf("Hello World!\n");
#endif
	vTaskStartScheduler();
	
	return 0;
}


// inclusion clock used peripherals
static void InitClock(void)
{
  	TIM_DeInit(TIM1);
	
	// Enable AHB periph clocks
	RCC_AHBPeriphClockCmd(
		RCC_AHBPeriph_DMA1
		, ENABLE);

	// Enable APB1 periph clocks
	RCC_APB1PeriphClockCmd(
		RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM2
		, ENABLE);
	
	// Enable APB2 periph clocks
	RCC_APB2PeriphClockCmd(
		RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC
		| RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO
		| RCC_APB2Periph_USART1 | RCC_APB2Periph_SPI1 | RCC_APB2Periph_TIM1 
		| RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2
		, ENABLE);
}


// port initialization
static void InitGPIO(void)
{
	typedef struct tag_GpioCfg
	{
		GPIO_TypeDef *port;
		uint16_t pin;
		GPIOSpeed_TypeDef speed;
		GPIOMode_TypeDef mode;
	}
	GpioCfg;
	
	GpioCfg cfg[] =
	{
		  {GPIOB, GPIO_Pin_5, 	GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	  // LED1 !!!STATUS!!!
		, {GPIOB, GPIO_Pin_4,	GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	  // LED2 !!!ERROR!!!

		, {GPIOB, GPIO_Pin_6, 	GPIO_Speed_50MHz, GPIO_Mode_AF_PP}	  // TX1
		, {GPIOB, GPIO_Pin_7,	GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}  // RX1	USART1

		, {GPIOA, GPIO_Pin_8, 	GPIO_Speed_50MHz, GPIO_Mode_AF_PP }	// PA8	AH
		, {GPIOA, GPIO_Pin_9, 	GPIO_Speed_50MHz, GPIO_Mode_AF_PP }	// PA9	BH
		, {GPIOA, GPIO_Pin_10,	GPIO_Speed_50MHz, GPIO_Mode_AF_PP }	// PA10	CH
		
		, {GPIOB, GPIO_Pin_15, 	GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	// PB15	AL
		, {GPIOB, GPIO_Pin_14, 	GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	// PB14	BL
		, {GPIOB, GPIO_Pin_13, 	GPIO_Speed_50MHz, GPIO_Mode_Out_PP}	// PB13	CL
		
		, {GPIOA, GPIO_Pin_0,	GPIO_Speed_50MHz, GPIO_Mode_AIN}	// PA0 ENA	backEMF phaseA
		, {GPIOA, GPIO_Pin_1,	GPIO_Speed_50MHz, GPIO_Mode_AIN}	// PA1 ENB	backEMF phaseB
		, {GPIOA, GPIO_Pin_2,	GPIO_Speed_50MHz, GPIO_Mode_AIN}	// PA2 ENC	backEMF phaseC
		, {GPIOA, GPIO_Pin_3,	GPIO_Speed_50MHz, GPIO_Mode_AIN}	// PA3 Volt input voltage
		, {GPIOB, GPIO_Pin_0,	GPIO_Speed_50MHz, GPIO_Mode_AIN}	// PB0 input current VIOUT
                
                , {GPIOA, GPIO_Pin_7,	GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING}// PA7 input current no FAULT
                , {GPIOB, GPIO_Pin_3,	GPIO_Speed_50MHz, GPIO_Mode_IPU}        // PB3 input PWM (while not use!!!)
                
                , {GPIOA, GPIO_Pin_11,	GPIO_Speed_50MHz, GPIO_Mode_AF_PP}  // (while not use!!!)
                , {GPIOA, GPIO_Pin_12,	GPIO_Speed_50MHz, GPIO_Mode_AF_PP}  // (while not use!!!)
	};

	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);	

	for (int i = 0; i < sizeof(cfg) / sizeof(cfg[0]); ++i)
	{
		GPIO_InitTypeDef gpio = {cfg[i].pin, cfg[i].speed, cfg[i].mode};
		GPIO_Init(cfg[i].port, &gpio);
	}
	
	// Alternative USART1 remaping
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
	
	// Alternative TIM1 remaping
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
}


// Interrupt controller initialization
static void InitNVIC(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);		// 4 bits for preemption	
	
	/* Enable the TIM1 Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM2 Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the TIM3 Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}


#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* expr, uint8_t* file, uint32_t line)
{
  	uint16_t a = 0;
	//printf("%s:%d %s -- assertion failed\n", file, line, expr);

	for( ;; )
	{
	  	a++;
	}
}
#endif


