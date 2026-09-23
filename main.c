#include "stm32f10x.h"

// ????,??t=1000 ????1?
void Delay(uint32_t t)
{
	uint32_t i,j;
	for(i=0;i<t;i++)
		for(j=0;j<7200;j++);
}

int main(void)
{
	// ??GPIOA?GPIOB??
	RCC->APB2ENR |= (1U << 2) | (1U << 3);
	
	// PA0 ???? 50MHz
	GPIOA->CRL &= ~(0x0FU << 0);
	GPIOA->CRL |=  (0x03U << 0);
	
	// PB0 ???? 50MHz
	GPIOB->CRL &= ~(0x0FU << 0);
	GPIOB->CRL |=  (0x03U << 0);
	
	// PB1 ???? 50MHz
	GPIOB->CRL &= ~(0x0FU << 4);
	GPIOB->CRL |=  (0x03U << 4);
	
	// ??????
	GPIOA->ODR &= ~(1U << 0);
	GPIOB->ODR &= ~((1U << 0)|(1U << 1));
	
	while(1)
	{
		//PA0?
		GPIOA->ODR |= (1U << 0);
		GPIOB->ODR &= ~((1U << 0)|(1U << 1));
		Delay(1000);    // ??1?
		
		//PB0?
		GPIOA->ODR &= ~(1U << 0);
		GPIOB->ODR |= (1U << 0);
		GPIOB->ODR &= ~(1U << 1);
		Delay(1000);    // ??1?
		
		//PB1?
		GPIOA->ODR &= ~(1U << 0);
		GPIOB->ODR &= ~(1U << 0);
		GPIOB->ODR |= (1U << 1);
		Delay(1000);    // ??1?
	}
}
