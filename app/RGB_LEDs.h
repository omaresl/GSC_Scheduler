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


extern void init_leds(void);
extern void app_rgb_led(void);
extern void app_rgb_led_fsm(void);


#endif /* RGB_LEDS_H */
