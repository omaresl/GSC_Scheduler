/*
 * app_BtnDbnc.h
 *
 *  Created on: 20/10/2017
 *      Author: uidj2522
 */

#ifndef APP_BTNDBNC_H_
#define APP_BTNDBNC_H_

/******************************************
 * Includes
 ******************************************/
#include "stdtypedef.h"

/******************************************
 * Type definitions
 ******************************************/
typedef enum
{
	BUTTON_UNPRESSED,
	BUTTON_PRESSED
}T_BUTTON_STATES;

enum
{
	BUTTON0,
	BUTTON1,
	N_BUTTONS
};

/******************************************
 * Defines
 ******************************************/
/* Confiuration constants for buttons */

#define APP_BTNDBNC_N_BUTTONS				((T_UBYTE)N_BUTTONS)	//Number of buttons to configure

#define APP_BTNDBNC_BUTTON0_PIN_NUMBER		((T_UBYTE)9U)	//Button 0 Pin Number Assignement
#define APP_BTNDBNC_BUTTON1_PIN_NUMBER		((T_UBYTE)8U)	//Button 1 Pin Number Assignement

#define APP_BTNDBNC_BUTTON0_PIN_GPIO_BASE	GPIOC	//Button 0 Pin GPIO Base Assignement
#define APP_BTNDBNC_BUTTON1_PIN_GPIO_BASE	GPIOC	//Button 1 Pin GPIO Base Assignement

#define APP_BTNDBNC_BUTTON0_PIN_PORT_BASE	PORTC	//Button 0 Pin PORT Base Assignement
#define APP_BTNDBNC_BUTTON1_PIN_PORT_BASE	PORTC	//Button 1 Pin PORT Base Assignement

#define APP_BTNDBNC_BUTTON0_PIN_PORT_BASE	PORTC	//Button 0 Pin PORT Base Assignement
#define APP_BTNDBNC_BUTTON1_PIN_PORT_BASE	PORTC	//Button 1 Pin PORT Base Assignement

#define APP_BTNDBNC_BUTTON0_PIN_PORT_CLOCK	kCLOCK_PortC	//Button 0 Pin PORT Base Assignement
#define APP_BTNDBNC_BUTTON1_PIN_PORT_CLOCK	kCLOCK_PortC	//Button 1 Pin PORT Base Assignement

#define BUTTON_HW_PRESSED	FALSE
#define BUTTON_HW_UNPRESSED	TRUE

#define APP_BTNDBNC_DBNC_VALID_COUNT	((T_UWORD)3000U)

/******************************************
 * Variables
 ******************************************/

/******************************************
 * Prototypes
 ******************************************/
extern void app_BtnDbnc_Init(void);
extern void app_BtnDbnc_TaskMngr(void);

#endif /* APP_BTNDBNC_H_ */
