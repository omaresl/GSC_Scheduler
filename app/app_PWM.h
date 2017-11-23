/*
 * app_PWM.h
 *
 *  Created on: 08/11/2017
 *      Author: uidj2522
 */

#ifndef APP_PWM_H_
#define APP_PWM_H_

#include "stdtypedef.h"

typedef enum
{
	STATE_PWM_UP,
	STATE_PWM_DOWN,
	STATE_PWM_ERROR
}E_PWM_STATE;

extern void app_PWM_Init(void);
extern void app_PWM_SetValue(T_UBYTE lub_Duty);
extern void app_PWM_Task(void);


#endif /* APP_PWM_H_ */
