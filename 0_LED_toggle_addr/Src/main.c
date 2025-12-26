// where is the LED connected
// Port  - PD
// Pin 	 - 12


#define PERIPH_BASE (0x40000000UL)

// carry clock to the peripherals via BUS
#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET (0x0C00UL)
#define GPIOD_BASE (AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET (0x30L)
#define RCC_AHB1EN_R *(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET)

#define GPIODEN (1U<<3)

#define MODE_R_OFFSET (0x00UL)
#define GPIOD_MODE_R *(volatile unsigned int *)(GPIOD_BASE + MODE_R_OFFSET)

#define OD_R_OFFSET (0x14UL)
#define GPIOD_OD_R *(volatile unsigned int *)(GPIOD_BASE + OD_R_OFFSET)

#define PIN12 (1U<<12)
#define LED_PIN PIN12

/*
 *  (1U<<10) //set bit 10 to 1
 *  &=~(1U<<11) // set bit 11 to 0
 * */

int main() {
	/* Enable clock access to GPIOD */
	RCC_AHB1EN_R |= GPIODEN;

	/* Set PD12 as an output pin */
	GPIOD_MODE_R |= (1U<<24);	//set bit 24 as 1
	GPIOD_MODE_R &=~(1U<<25);	//set bit 25 as 0

	while(1) {
		/* Set PD12 high*/
		GPIOD_OD_R ^= LED_PIN;

		for (int i = 0; i < 100000; i ++);
	}

}
