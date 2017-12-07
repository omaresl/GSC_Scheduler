/*
 * app_WindowLifterSM.h
 *
 *  Created on: 30/11/2017
 *      Author: uidj2522
 */

#ifndef APP_WINDOWLIFTERSM_H_
#define APP_WINDOWLIFTERSM_H_

/******************************************
 * Typedefs
 ******************************************/
typedef enum
{
	WINDOW_LIFTER_STATE_IDLE,
	WINDOW_LIFTER_STATE_DECRYPT,
	WINDOW_LIFTER_STATE_EXECUTE,
	WINDOW_LIFTER_STATE_ERROR,
	WINDOW_LIFTER_STATE_N_STATES
}E_WINDOW_LIFTER_STATE;

typedef enum
{
	LOWER_LED = 0u,
	UPPER_LED = 9u
}E_LED_SELECTOR;

/******************************************
 * Defines
 ******************************************/
//#define APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE

#define APP_WINDOW_LIFTER_CMD_MASK	0x0F

#define CMD_OPENING		0x01u
#define CMD_CLOSING		0x02u
#define CMD_FULLOPEN	0x03u
#define CMD_FULLCLOSE	0x04u
#define CMD_STOP		0x0Fu

#define OPENING_CMD					(T_UBYTE)(0x01u)
#define CLOSING_CMD   				(T_UBYTE)(0x02u)
#define FULLY_OPEN_CMD      		(T_UBYTE)(0x03u)
#define FULLY_CLOSED_CMD    		(T_UBYTE)(0x04u)
#define SET_TO_ONE_CMD				(T_UBYTE)(0x0Eu)
#define STOP_CMD            		(T_UBYTE)(0x0Fu)

#define NRC_NOT_VALID_CMD			(T_UBYTE)(0x05u)
#define NRC_VALIDATION_FAILED   	(T_UBYTE)(0x06u)
#define NRC_OPEN_CMD_W_FOPEN  		(T_UBYTE)(0x07u)
#define NRC_CLOSED_CMD_W_FCLOSED 	(T_UBYTE)(0x08u)

#define APP_WINDOW_LIFTER_FULL_OPEN_VALUE		(T_UBYTE)(0u)
#define APP_WINDOW_LIFTER_FULL_CLOSED_VALUE		(T_UBYTE)(10u)
#define APP_WINDOW_LIFTER_SINGLE_STEP			(T_UBYTE)(2u)
#define APP_WINDOW_LIFTER_BLINKS_AT_LIMIT		(T_UBYTE)(1u)
#define APP_WINDOW_LIFTER_BLINKS_MULTIPLIER		(T_UBYTE)(2u)

#define APP_WINDOW_LIFTER_LED0_PIN_NUMBER	(T_UBYTE)(7u)
#define APP_WINDOW_LIFTER_LED1_PIN_NUMBER	(T_UBYTE)(0u)
#define APP_WINDOW_LIFTER_LED2_PIN_NUMBER	(T_UBYTE)(3u)
#define APP_WINDOW_LIFTER_LED3_PIN_NUMBER	(T_UBYTE)(4u)
#define APP_WINDOW_LIFTER_LED4_PIN_NUMBER	(T_UBYTE)(5u)
#define APP_WINDOW_LIFTER_LED5_PIN_NUMBER	(T_UBYTE)(6u)
#define APP_WINDOW_LIFTER_LED6_PIN_NUMBER	(T_UBYTE)(10u)
#define APP_WINDOW_LIFTER_LED7_PIN_NUMBER	(T_UBYTE)(11u)
#define APP_WINDOW_LIFTER_LED8_PIN_NUMBER	(T_UBYTE)(9u)
#define APP_WINDOW_LIFTER_LED9_PIN_NUMBER	(T_UBYTE)(8u)

#define APP_WINDOW_LIFTER_LED0_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED1_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED2_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED3_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED4_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED5_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED6_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED7_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED8_GPIO_BASE	(GPIOC)
#define APP_WINDOW_LIFTER_LED9_GPIO_BASE	(GPIOC)

#define APP_WINDOW_LIFTER_LED0_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED1_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED2_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED3_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED4_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED5_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED6_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED7_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED8_PORT_BASE	(PORTC)
#define APP_WINDOW_LIFTER_LED9_PORT_BASE	(PORTC)

/******************************************
 * Variables
 ******************************************/
extern E_LED_SELECTOR rub_BlinkLedSelector;

/******************************************
 * Prototypes
 ******************************************/
extern void app_WindowLifterSM_Init(void);
extern void app_WindowLifterSM_Task(void);
extern void app_WindowLifterSM_ActionsTask(void);
extern void app_WindowLifterSM_LEDController_Task(T_UBYTE lub_Position);
extern void app_WindowLifterSM_BlinkLed_Task(E_LED_SELECTOR lub_Selector);

#endif /* APP_WINDOWLIFTERSM_H_ */
