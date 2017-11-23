/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */

#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "fsl_gpio.h"


#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (1000000)
#define BLINK_DELAY     FAST_BLINK

#define RED				(18) 
#define RED_SHIFT		(1 << 18)
#define GREEN			(19)
#define GREEN_SHIFT		(1 << 19)
#define BLUE			(1)
#define BLUE_SHIFT		(1 << 1)

#define RED_OFF			(GPIOB->PSOR = RED_SHIFT)
#define RED_ON			(GPIOB->PCOR = RED_SHIFT)
#define RED_TOGGLE		(GPIOB->PTOR = RED_SHIFT)

#define GREEN_OFF		(GPIOB->PSOR = GREEN_SHIFT)
#define GREEN_ON		(GPIOB->PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE	(GPIOB->PTOR = GREEN_SHIFT)

#define BLUE_OFF		(GPIOD->PSOR = BLUE_SHIFT)
#define BLUE_ON			(GPIOD->PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE		(GPIOD->PTOR = BLUE_SHIFT)

enum
{
	OFF,
	ON,
	TOGGLING
};

T_UBYTE re_LEDaction = TOGGLING;

void delay_time(int);
void init_leds();
void red_on();
void red_off();
void green_on();
void green_off();
void blue_on();
void blue_off();

void app_rgb_led(void)
{
		red_on();
		delay_time(BLINK_DELAY);	/* Red */
		red_off();
		green_on();
		delay_time(BLINK_DELAY);	/* Green */
		green_off();
		blue_on();
		delay_time(BLINK_DELAY);	/* Blue */
		red_on();
		delay_time(BLINK_DELAY);	/* Blue + Red */
		green_on();
		blue_on();
		delay_time(BLINK_DELAY);	/* Red + Green */
		red_off();
		blue_on();
		delay_time(BLINK_DELAY);	/* Green + Blue */
		red_on();
		delay_time(BLINK_DELAY);	/* Green + Blue + Red */
		green_off();
		blue_off();
}

void app_rgb_led_fsm(void)
{
	static unsigned char rgb_state = 0;

	if(re_LEDaction == OFF)
	{
		/* All off */
		red_off();
		green_off();
		blue_off();
	}
	else if(re_LEDaction == ON)
	{
		/* White is LED ON */
		red_on();
		green_on();
		blue_on();
	}
	else if(re_LEDaction == TOGGLING)
	{
		/* Toggling LED color */
		switch(rgb_state)
		{
			case 0: /* RESET */
				/* All off */
				red_off();
				green_off();
				blue_off();
				rgb_state = 1;
				break;
			case 1: /* red on */
				red_on();
				green_off();
				blue_off();
				rgb_state = 2;
				break;
			case 2: /* green on */
				red_off();
				green_on();
				blue_off();
				rgb_state = 3;
				break;
			case 3: /* blue on */
				red_off();
				green_off();
				blue_on();
				rgb_state = 4;
				break;
			case 4: /* red + green */
				red_on();
				green_on();
				blue_off();
				rgb_state = 5;
				break;
			case 5: /* red + blue */
				red_on();
				green_off();
				blue_on();
				rgb_state = 6;
				break;
			case 6: /* green + blue */
				red_off();
				green_on();
				blue_on();
				rgb_state = 7;
				break;
			case 7: /* All on */
				red_on();
				green_on();
				blue_on();
				rgb_state = 1;
				break;
			default:
				/* Go to RESET */
				rgb_state = 0;
				break;
		}
	}
	else
	{
		/* Permanent RED means an error! */
		red_on();
		green_off();
		blue_off();
	}
}

void red_on(){
	RED_ON;
}

void red_off(){
	RED_OFF;
}

void green_on(){
	GREEN_ON;
}

void green_off(){
	GREEN_OFF;
}

void blue_on(){
	BLUE_ON;
}

void blue_off(){
	BLUE_OFF;
}

/********************************************************************/

void delay_time(int number){
  volatile int cnt;
  for(cnt=0;cnt<number;cnt++);
}
/********************************************************************/

/********************************************************************/
/*	init_leds()
 * initialize the ports for LEDs
 * ******************************************************************/
 

 void init_leds(void)
 {
	 
    /* 
	 * Initialize the Red LED (PTB18)
	 */

		/* Turn on clock to PortB module */
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;

		/* Set the PTB18 pin multiplexer to GPIO mode */
		PORTB->PCR[18] = PORT_PCR_MUX(1);

		/* Set the initial output state to high */
		GPIOB->PSOR |= RED_SHIFT;

		/* Set the pins direction to output */
		GPIOB->PDDR |= RED_SHIFT;


	/*
	 * Initialize the Green LED (PTB19)
	 */

//		/* Turn on clock to PortB module */
//		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
//
//		/* Set the PTB19 pin multiplexer to GPIO mode */
//		PORTB->PCR[19] = PORT_PCR_MUX(1);
//
//		/* Set the initial output state to high */
//		GPIOB->PSOR |= GREEN_SHIFT;
//
//		/* Set the pins direction to output */
//		GPIOB->PDDR |= GREEN_SHIFT;



	/*
	 * Initialize the Blue LED (PTD1)
	 */

		/* Turn on clock to PortB module */
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

		/* Set the PTD1 pin multiplexer to GPIO mode */
		PORTD->PCR[1]= PORT_PCR_MUX(1);

		/* Set the initial output state to high */
		GPIOD->PSOR = BLUE_SHIFT;

		/* Set the pins direction to output */
		GPIOD->PDDR |= BLUE_SHIFT;
}

 
