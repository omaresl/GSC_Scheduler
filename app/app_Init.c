/*
 * app_Init.c
 *
 *  Created on: 23/10/2017
 *      Author: uidj2522
 */

/******************************************
 * Includes
 ******************************************/
#include "app_Init.h"
#include "app_GPIO.h"
#include "app_BtnDbnc.h"
#include "app_PWM.h"
#include "app_UART.h"
#include "app_WindowLifterSM.h"

/******************************************
 * Defines
 ******************************************/

/******************************************
 * Variables
 ******************************************/

/******************************************
 * Prototypes
 ******************************************/

/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_Init
 * Description: TBD
 ***********************************************/
void app_Init(void)
{
    /* GPIO Module Init */
    app_GPIO_Init();

    /* Button Debounce App Init */
    app_BtnDbnc_Init();

    /* PWM Init */
    app_PWM_Init();

    /* UART Init */
    app_UART_Init();

    /* Window Lifter Init */
    app_WindowLifterSM_Init();
}
