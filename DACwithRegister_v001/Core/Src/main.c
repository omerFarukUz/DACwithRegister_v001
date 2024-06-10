#include "string.h"
#include "main.h"
#include "stm32f439xx.h"


int count = 0;

void delay1(uint32_t data)
{
	while(data--);
}

void RCC_Config()
{
	RCC->CR |= 0x10000; 			  // HSEON enable
	while(!(RCC->CR & 0x20000));      // HSEON Ready Flag wait
	RCC->CR |= 0x80000;				  // CSS enable
	RCC->PLLCFGR |= 0x400000; 		  // PLL e HSE sectik
	RCC->PLLCFGR |= 0x000004; 		  // PLL M = 4
	RCC->PLLCFGR |= 0x005A00; 		  // PLL N=168
	RCC->PLLCFGR |= 0x000000; 		  // PLL P=2
	RCC->CFGR |= 0x000000; 		 	  // AHB Prescaler = 1
	RCC->CFGR |= 0x080000; 		  	  // APB2 Prescaler = 2
	RCC->CFGR |= 0x001400; 		  	  // APB1 Presclaer = 4
	RCC->CIR |= 0x00080000;			  // HSERDY Flag Clear
	RCC->CIR |= 0x00800000;			  // CSS Flag Clear

}

void DAC1_Config()
{
	RCC->AHB1ENR |=  RCC_AHB1ENR_GPIOAEN;		// RCC GPIOA Clock Enable
	RCC->APB1ENR |=  RCC_APB1ENR_DACEN;			// RCC DAC Clock enable
	DAC->CR |= DAC_CR_EN1;						// DAC Channel 1 enable
	DAC->SWTRIGR &= ~(DAC_SWTRIGR_SWTRIG1);		// DAC Channel 1 software trigger disable
	DAC->DHR12R1 = 0;									// DAC Channel 1 12-bit right alignment



}


int main(void)
{

	RCC_Config();
	DAC1_Config();



  while (1)
  {
	  for(;count < 4096; count++)
	  {
		  DAC->DHR12R1 = count;
		  delay1(16800);
	  }
	  count = 0;
  }

}
