/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */
#ifndef RGB_LEDS_H                       /* To avoid double inclusion */
#define RGB_LEDS_H

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

extern void init_leds(void);
extern void app_rgb_led(void);
extern void app_rgb_led_fsm(void);


#endif /* RGB_LEDS_H */
