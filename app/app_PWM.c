/*
 * app_PWM.c
 *
 *  Created on: 08/11/2017
 *      Author: uidj2522
 */

#include "stdtypedef.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_tpm.h"
#include "app_PWM.h"

/******************************************
 * Variables
 ******************************************/
T_UBYTE rub_PWMDutyCycle = 0u;
E_PWM_STATE re_PWMState = STATE_PWM_UP;


void app_PWM_IncreaseDutyCycle(void);
void app_PWM_DecreaseDutyCycle(void);
/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_PWM_Init
 * Description: TBD
 ***********************************************/
void app_PWM_Init(void)
{
	tpm_config_t ls_TPMConfig;
	port_pin_config_t ls_PortConfig;
	tpm_chnl_pwm_signal_param_t ls_PWMParam;

	/* Enable Clock */
	//CLOCK_EnableClock(kCLOCK_Tpm2); //FOR LED RED
	CLOCK_SetTpmClock(1);

	/* PWM PIN Config */
	ls_PortConfig.mux = kPORT_MuxAlt3; //For PTB19, ALT3 is TPM2_CH1
	ls_PortConfig.pullSelect = kPORT_PullUp;

	PORT_SetPinConfig(PORTB, 19u, &ls_PortConfig);

	/* Get Default Config */
	TPM_GetDefaultConfig(&ls_TPMConfig);

	TPM_Init(TPM2, &ls_TPMConfig);

	/* PWM Setup */
	ls_PWMParam.chnlNumber = kTPM_Chnl_1;
	ls_PWMParam.dutyCyclePercent = rub_PWMDutyCycle;
	ls_PWMParam.level = kTPM_LowTrue;
	TPM_SetupPwm(TPM2, &ls_PWMParam, 1u, kTPM_CenterAlignedPwm, 24000u, CLOCK_GetFreq(kCLOCK_PllFllSelClk));

	/* Start PWM Timer */
	TPM_StartTimer(TPM2, kTPM_SystemClock);
}

/***********************************************
 * Function Name: app_PWM_SetValue
 * Description: TBD
 ***********************************************/
void app_PWM_SetValue(T_UBYTE lub_Duty)
{
	/* Update duty cycle */
	TPM_UpdatePwmDutycycle(TPM2, kTPM_Chnl_1, kTPM_CenterAlignedPwm, lub_Duty);
}

/***********************************************
 * Function Name: app_PWM_Task
 * Description: TBD
 ***********************************************/
void app_PWM_Task(void)
{
	/* PWM State Machine */
	switch(re_PWMState)
	{
	case STATE_PWM_UP:
	{
		app_PWM_IncreaseDutyCycle();
	}break;
	case STATE_PWM_DOWN:
	{
		app_PWM_DecreaseDutyCycle();
	}break;
	case STATE_PWM_ERROR:
	default:
	{
		rub_PWMDutyCycle = 0u;
		re_PWMState = STATE_PWM_UP;
	}break;
	}

	/* Set PWM DutyCycle */
	app_PWM_SetValue(rub_PWMDutyCycle);
}

/***********************************************
 * Function Name: app_PWM_IncreaseDutyCycle
 * Description: TBD
 ***********************************************/
void app_PWM_IncreaseDutyCycle(void)
{
	if(rub_PWMDutyCycle < 100u)
	{
		rub_PWMDutyCycle++;
	}
	else if(rub_PWMDutyCycle == 100u)
	{
		rub_PWMDutyCycle--;
		re_PWMState = STATE_PWM_DOWN;
	}
	else
	{//rub_PWMDutyCycle > 100
		/* Code never reached */
		re_PWMState = STATE_PWM_ERROR;
	}
}

/***********************************************
 * Function Name: app_PWM_DecreaseDutyCycle
 * Description: TBD
 ***********************************************/
void app_PWM_DecreaseDutyCycle(void)
{
	if(rub_PWMDutyCycle > 0u)
	{
		rub_PWMDutyCycle--;
	}
	else if(rub_PWMDutyCycle == 0u)
	{
		rub_PWMDutyCycle++;
		re_PWMState = STATE_PWM_UP;
	}
	else
	{//rub_PWMDutyCycle < 0
		/* Code never reached */
		rub_PWMDutyCycle = 0u;
		re_PWMState = STATE_PWM_ERROR;
	}
}
