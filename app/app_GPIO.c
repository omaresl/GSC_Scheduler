/*
 * app_GPIO.c
 *
 *  Created on: 14/10/2017
 *      Author: uidj2522
 */

#include "stdio.h"
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "app_GPIO.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

void app_GPIO_Init(void)
{
	/* Enable the clock for the modules needed */
	CLOCK_EnableClock(kCLOCK_PortB);

	/* PORT Module Configuration */

	port_pin_config_t ls_PinConfig;

	ls_PinConfig.mux = kPORT_MuxAsGpio;
	ls_PinConfig.pullSelect = kPORT_PullUp;

	port_pin_config_t *lps_PinConfig;

	lps_PinConfig = &ls_PinConfig;

	PORT_SetPinConfig(PORTB, 18U, lps_PinConfig);

	/* GPIO Configuration for Inputs */

	gpio_pin_config_t ls_GPIOPinConfig;

	/* GPIO Configuration for Outputs */
	ls_GPIOPinConfig.pinDirection = kGPIO_DigitalOutput;
	ls_GPIOPinConfig.outputLogic = TRUE;

	GPIO_PinInit(GPIOB, 18U, &ls_GPIOPinConfig);

}

T_UBYTE app_GPIO_GetPinValue(GPIO_Type *lps_BaseAddress, T_UBYTE lub_PinNumber)
{
	T_UBYTE lub_PinValue;

	lub_PinValue = (T_UBYTE)GPIO_ReadPinInput(lps_BaseAddress, lub_PinNumber);

	return lub_PinValue;
}
