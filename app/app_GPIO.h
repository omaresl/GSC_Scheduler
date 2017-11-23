/*
 * app_GPIO.h
 *
 *  Created on: 14/10/2017
 *      Author: uidj2522
 */

#ifndef APPLICATION_APP_GPIO_H_
#define APPLICATION_APP_GPIO_H_

/******************************************
 * Includes
 ******************************************/
#include "stdtypedef.h"
#include "fsl_gpio.h"

/******************************************
 * Prototypes
 ******************************************/
extern void app_GPIO_Init(void);
extern T_UBYTE app_GPIO_GetPinValue(GPIO_Type *lps_BaseAddress, T_UBYTE lub_PinNumber);

#endif /* APPLICATION_APP_GPIO_H_ */
