/*
 * app_WindowLifterSM.c
 *
 *  Created on: 30/11/2017
 *      Author: uidj2522
 */

/******************************************
 * Includes
 ******************************************/
#include "stdtypedef.h"
#include "stdio.h"
#include "app_WindowLifterSM.h"
#include "app_UART.h"
#include "RGB_LEDs.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/******************************************
 * Constants
 ******************************************/
const T_UBYTE caub_WindowLifterCommands[] =
{
		OPENING_CMD,
		CLOSING_CMD,
		FULLY_OPEN_CMD,
		FULLY_CLOSED_CMD,
		SET_TO_ONE_CMD,
		STOP_CMD
};

const T_UBYTE caub_WindowLifterErrorCodes[] =
{
		OPENING_CMD,
		CLOSING_CMD,
		FULLY_OPEN_CMD,
		FULLY_CLOSED_CMD,
};

const T_UBYTE caub_WindowLifterLedPinNumbers[] =
{
		APP_WINDOW_LIFTER_LED0_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED1_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED2_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED3_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED4_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED5_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED6_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED7_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED8_PIN_NUMBER,
		APP_WINDOW_LIFTER_LED9_PIN_NUMBER
};

const PORT_Type* caub_WindowLifterLedPORTBases[] =
{
		APP_WINDOW_LIFTER_LED0_PORT_BASE,
		APP_WINDOW_LIFTER_LED1_PORT_BASE,
		APP_WINDOW_LIFTER_LED2_PORT_BASE,
		APP_WINDOW_LIFTER_LED3_PORT_BASE,
		APP_WINDOW_LIFTER_LED4_PORT_BASE,
		APP_WINDOW_LIFTER_LED5_PORT_BASE,
		APP_WINDOW_LIFTER_LED6_PORT_BASE,
		APP_WINDOW_LIFTER_LED7_PORT_BASE,
		APP_WINDOW_LIFTER_LED8_PORT_BASE,
		APP_WINDOW_LIFTER_LED9_PORT_BASE
};

const GPIO_Type* caub_WindowLifterLedGPIOBases[] =
{
		APP_WINDOW_LIFTER_LED0_GPIO_BASE,
		APP_WINDOW_LIFTER_LED1_GPIO_BASE,
		APP_WINDOW_LIFTER_LED2_GPIO_BASE,
		APP_WINDOW_LIFTER_LED3_GPIO_BASE,
		APP_WINDOW_LIFTER_LED4_GPIO_BASE,
		APP_WINDOW_LIFTER_LED5_GPIO_BASE,
		APP_WINDOW_LIFTER_LED6_GPIO_BASE,
		APP_WINDOW_LIFTER_LED7_GPIO_BASE,
		APP_WINDOW_LIFTER_LED8_GPIO_BASE,
		APP_WINDOW_LIFTER_LED9_GPIO_BASE
};

/******************************************
 * Variables
 ***************s***************************/
E_WINDOW_LIFTER_STATE re_WindowLifterState = WINDOW_LIFTER_STATE_IDLE;
T_UBYTE rub_CMDIndex;
T_UBYTE rub_WindowLifterExecuteFlag;
T_UBYTE rub_LastValidCMDReceived;
T_UBYTE rub_WindowPosition;
T_UBYTE rub_WindowLifterTaskCounter;
T_UBYTE rub_LEDToToggle;
static T_UBYTE rub_BlinkRequestFlag = FALSE;
E_LED_SELECTOR rub_BlinkLedSelector;

/******************************************
 * Prototypes
 ******************************************/
static T_UBYTE app_WindowLifterSM_DecryptData(T_UBYTE lub_Data);
static T_UBYTE app_WindowLifterSM_GetUpperNibble(T_UBYTE lub_Data);
static T_UBYTE app_WindowLifterSM_GetLowerNibble(T_UBYTE lub_Data);
static T_UBYTE app_WindowLifterSM_GetJoinNibbles(T_UBYTE lub_A,T_UBYTE lub_B);
static T_UBYTE app_WindowLifterSM_CommandValidation(T_UBYTE lub_Command);
static void app_WindowLifterSM_SendPositiveResponse(void);
static void app_WindowLifterSM_SendNegativeResponse(T_UBYTE lub_NRC);
static void app_WindowLifterSM_ExecuteRequest(void);

/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: app_WindowLifterSM_Init
 * Description: TBD
 ***********************************************/
void app_WindowLifterSM_Init(void)
{
	port_pin_config_t lps_PortConfig;
	gpio_pin_config_t lps_GpioConfig;

	/* Pin Initialization */
	CLOCK_EnableClock(kCLOCK_PortC);

	lps_PortConfig.mux = kPORT_MuxAsGpio;

	for(T_UBYTE lub_i = 0; lub_i < sizeof(caub_WindowLifterLedPinNumbers);lub_i++)
	{
		PORT_SetPinConfig((PORT_Type*)caub_WindowLifterLedPORTBases[lub_i],caub_WindowLifterLedPinNumbers[lub_i], &lps_PortConfig);
	}

	lps_GpioConfig.outputLogic = TRUE;
	lps_GpioConfig.pinDirection = kGPIO_DigitalOutput;

	for(T_UBYTE lub_i = 0; lub_i < sizeof(caub_WindowLifterLedPinNumbers);lub_i++)
	{
		GPIO_PinInit((GPIO_Type*)caub_WindowLifterLedGPIOBases[lub_i], caub_WindowLifterLedPinNumbers[lub_i], &lps_GpioConfig);
	}

	re_WindowLifterState = WINDOW_LIFTER_STATE_IDLE;
	rub_CMDIndex = 0u;
	rub_WindowLifterExecuteFlag = FALSE;
	rub_BlinkRequestFlag = FALSE;
	rub_WindowPosition = APP_WINDOW_LIFTER_FULL_CLOSED_VALUE;
}

/***********************************************
 * Function Name: app_WindowLifterSM_Task
 * Description: TBD
 ***********************************************/
void app_WindowLifterSM_Task(void)
{
	T_UBYTE lub_CMD_Received;
	switch(re_WindowLifterState)
	{
	case WINDOW_LIFTER_STATE_IDLE:
	{
		/* Wait for a RX Succesfull */
		if(app_UART_ReadData(&lub_CMD_Received) == TRUE)
		{//Data received and stored

			if(app_WindowLifterSM_CommandValidation(lub_CMD_Received) == TRUE)
			{//Command Valid
				/* Go to Decrypt State */
				re_WindowLifterState = WINDOW_LIFTER_STATE_DECRYPT;
			}
			else
			{//Command Invalid
				/* Send NRC */
				app_WindowLifterSM_SendNegativeResponse(NRC_NOT_VALID_CMD);
			}

#ifdef APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE
			if(re_WindowLifterState == WINDOW_LIFTER_STATE_DECRYPT)
			{
				printf("\nCommand Valid Received\n");
				printf("\nWait for Encrypted Data\n");
			}
			else
			{
				printf("\nCommand Invalid Received\n");
				printf("\nWait for Valid Command\n");
			}
#endif

		}
		else
		{//There is not data to be read
			/* Do nothing */
		}
	}break;
	case WINDOW_LIFTER_STATE_DECRYPT:
	{
		/* Wait for a RX Succesfull */
		if(app_UART_ReadData(&lub_CMD_Received) == TRUE)
		{//Data received and stored
			/* Check if Data received is correctly encrypted */
			if(app_WindowLifterSM_DecryptData(lub_CMD_Received) == TRUE)
			{//Correctly Encrypted

				/* Go to Execute State */
				re_WindowLifterState = WINDOW_LIFTER_STATE_EXECUTE;
			}
			else
			{//Incorrectly Encrypted
				/* Send Negative Response */
				app_WindowLifterSM_SendNegativeResponse(NRC_VALIDATION_FAILED);

				/* Go to Error State */
				re_WindowLifterState = WINDOW_LIFTER_STATE_ERROR;
			}
#ifdef APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE
			if(re_WindowLifterState == WINDOW_LIFTER_STATE_EXECUTE)
			{
				printf("\nCommand Decrypted Correctly\n");
				printf("\nExecute Command\n");
			}
			else
			{
				printf("\nCommand Decryption Failed\n");
				printf("\nGo to Error State\n");
			}
#endif
		}
		else
		{//There is not data to be read
			/* Do nothing */
		}
	}break;
	case WINDOW_LIFTER_STATE_EXECUTE:
	{
		/* Execute Command */
#ifdef APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE
		RED_TOGGLE;
#endif
		app_WindowLifterSM_ExecuteRequest();

		/* Send Positive Response */
		app_WindowLifterSM_SendPositiveResponse();

		/* Go to Idle State */
		re_WindowLifterState = WINDOW_LIFTER_STATE_IDLE;
#ifdef APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE
		printf("\nCommand Executed\n");
#endif
	}break;
	case WINDOW_LIFTER_STATE_ERROR:
	default:
	{
#ifdef APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE
		if(re_WindowLifterState == WINDOW_LIFTER_STATE_ERROR)
		{
			printf("\nEnter in Error State\n");
		}
		else
		{
			printf("\nFSM Failed\n");
			printf("\nDefault case reached\n");
		}
		printf("\nGo to Idle\n");
#endif
		/* Go to Idle State */
		re_WindowLifterState = WINDOW_LIFTER_STATE_IDLE;
	}break;
	}
}

/***********************************************
 * Function Name: app_WindowLifterSM_Init
 * Description: The bits 4 to 7 will contain
 * 				random values which will generate the encrypted
 * 				byte to validate the command. The encryption will be
 * 				sent in a second byte of information and it will be
 * 				calculated as follows:
 *
 *              COMMAND
 *                 A		  B
 *              1 1 1 0    0 1 0 0
 *
 *              VALIDATION
 *                 C          D
 *              0 0 0 1    1 0 1 0
 *
 *              C = ~A.
 *              D = (A & (~B)).
 ***********************************************/
static T_UBYTE app_WindowLifterSM_DecryptData(T_UBYTE lub_Data)
{
	T_UBYTE lub_A,lub_B,lub_C,lub_D;
	T_UBYTE lub_Result;

	/* Pre fail */
	lub_Result = FALSE;

	/* Split Command */
	lub_A = app_WindowLifterSM_GetUpperNibble(rub_LastValidCMDReceived);
	lub_B = app_WindowLifterSM_GetLowerNibble(rub_LastValidCMDReceived);

	/* Encrypt command */
	lub_C = (T_UBYTE)~(lub_A);
	lub_D = (T_UBYTE)(lub_A & (T_UBYTE)~(lub_B));

	/* Compare Encryption with data received */
	if(lub_Data == app_WindowLifterSM_GetJoinNibbles(lub_C,lub_D))
	{//Valid Encryption
		lub_Result = TRUE;
	}
	else
	{//Invalid Encryption
		lub_Result = FALSE;
	}

	return lub_Result;
}

/***********************************************
 * Function Name: app_WindowLifterSM_GetUpperNibble
 * Description: TBD
 ***********************************************/
static T_UBYTE app_WindowLifterSM_GetUpperNibble(T_UBYTE lub_Data)
{
	return (T_UBYTE)((lub_Data >> 4u) & 0x0F);
}

/***********************************************
 * Function Name: app_WindowLifterSM_GetLowerNibble
 * Description: TBD
 ***********************************************/
static T_UBYTE app_WindowLifterSM_GetLowerNibble(T_UBYTE lub_Data)
{
	return (T_UBYTE)((lub_Data >> 0u) & 0x0F);
}

/***********************************************
 * Function Name: app_WindowLifterSM_GetLowerNibble
 * Description: TBD
 ***********************************************/
static T_UBYTE app_WindowLifterSM_GetJoinNibbles(T_UBYTE lub_A,T_UBYTE lub_B)
{
	return (T_UBYTE)(((lub_A << 4u) & 0xF0) | (lub_B & 0x0F));
}

/***********************************************
 * Function Name: app_WindowLifterSM_CommandValidation
 * Description: TBD
 ***********************************************/
static T_UBYTE app_WindowLifterSM_CommandValidation(T_UBYTE lub_Command)
{
	T_UBYTE lub_Result;

	lub_Result = FALSE;

	/* Check if received data is valid */
	for(T_UBYTE lub_i = 0; lub_i < sizeof(caub_WindowLifterCommands);lub_i++)
	{
		/* Compare with the cmd table */
		if((lub_Command & APP_WINDOW_LIFTER_CMD_MASK) == caub_WindowLifterCommands[lub_i])
		{//Command Valid
			/* Store CMD Valid Index */
			rub_CMDIndex = lub_i;

			/* Store CMD Valid */
			rub_LastValidCMDReceived = lub_Command;

			/* Positive Reult */
			lub_Result = TRUE;

			/* Finish the loop */
			lub_i = sizeof(caub_WindowLifterCommands);
		}
		else
		{
			/* Command not match with actual element */
		}
	}

	return lub_Result;
}

/***********************************************
 * Function Name: app_WindowLifterSM_SendPositiveResponse
 * Description: TBD
 ***********************************************/
static void app_WindowLifterSM_SendPositiveResponse(void)
{
	/*Send Last Valid Command Received and Current Position*/
	app_UART_WriteData(app_WindowLifterSM_GetJoinNibbles(rub_WindowPosition,rub_LastValidCMDReceived));
}

/***********************************************
 * Function Name: app_WindowLifterSM_SendNegativeResponse
 * Description: TBD
 ***********************************************/
static void app_WindowLifterSM_SendNegativeResponse(T_UBYTE lub_NRC)
{
	/*Send Last Valid Command Received and Current Position*/
	app_UART_WriteData(app_WindowLifterSM_GetJoinNibbles(rub_WindowPosition, lub_NRC));
}

/***********************************************
 * Function Name: app_WindowLifterSM_ExecuteRequest
 * Description: TBD
 ***********************************************/
static void app_WindowLifterSM_ExecuteRequest(void)
{
	/* Set the flag for execution */
	rub_WindowLifterExecuteFlag = TRUE;

	/* Clear Task Counter */
	rub_WindowLifterTaskCounter = 0u;
}

/***********************************************
 * Function Name: app_WindowLifterSM_ActionsTask
 * Description: TBD
 ***********************************************/
void app_WindowLifterSM_ActionsTask(void)
{
	/* Check if an execution was requested */
	if(rub_WindowLifterExecuteFlag == TRUE)
	{//Execution Requested
		/* Increase Task Counter */
		rub_WindowLifterTaskCounter++;
		/* Check which command was received */
		switch(rub_LastValidCMDReceived)
		{
		case OPENING_CMD:
		{/* Decrease the Window position by 2 steps */
			if(rub_WindowPosition > APP_WINDOW_LIFTER_FULL_OPEN_VALUE)
			{
				/* Start Opening the window */
				rub_WindowPosition--;
				if(rub_WindowLifterTaskCounter < APP_WINDOW_LIFTER_SINGLE_STEP &&
						rub_WindowPosition > APP_WINDOW_LIFTER_FULL_OPEN_VALUE)
				{
					/* Keep the Execute Flag Unchanged */
				}
				else
				{
					/* Clear the Execute Flag */
					rub_WindowLifterExecuteFlag = FALSE;
				}
			}
			else
			{
				/* Blink Lower Led */
				rub_BlinkRequestFlag = TRUE;
				rub_BlinkLedSelector = LOWER_LED;


				/* Clear Task Counter */
				rub_WindowLifterTaskCounter = 0u;

				/* Clear the Execute Flag */
				rub_WindowLifterExecuteFlag = FALSE;
			}
		}break;
		case CLOSING_CMD:
		{/* Increase the Window position by 2 steps */
			if(rub_WindowPosition < APP_WINDOW_LIFTER_FULL_CLOSED_VALUE)
			{
				/* Start Closing the window */
				rub_WindowPosition++;
				if(rub_WindowLifterTaskCounter < APP_WINDOW_LIFTER_SINGLE_STEP &&
						rub_WindowPosition < APP_WINDOW_LIFTER_FULL_CLOSED_VALUE)
				{
					/* Keep the Execute Flag Unchanged */
				}
				else
				{
					/* Clear the Execute Flag */
					rub_WindowLifterExecuteFlag = FALSE;
				}
			}
			else
			{
				/* Blink Lower Led */
				rub_BlinkRequestFlag = TRUE;
				rub_BlinkLedSelector = UPPER_LED;

				/* Clear Task Counter */
				rub_WindowLifterTaskCounter = 0u;

				/* Clear the Execute Flag */
				rub_WindowLifterExecuteFlag = FALSE;
			}
		}break;
		case FULLY_OPEN_CMD:
		{/* Increase the Window position until reach the min value */
			if(rub_WindowPosition > APP_WINDOW_LIFTER_FULL_OPEN_VALUE)
			{
				/* Start Opening the window */
				rub_WindowPosition--;

				/* Check if Limit has been reached */
				if(rub_WindowPosition > APP_WINDOW_LIFTER_FULL_OPEN_VALUE)
				{
					/* Do nothing */
				}
				else
				{
					/* Clear the Execute Flag */
					rub_WindowLifterExecuteFlag = FALSE;
				}
			}
			else
			{
				/* Blink Lower Led */
				rub_BlinkRequestFlag = TRUE;
				rub_BlinkLedSelector = LOWER_LED;

				/* Clear Task Counter */
				rub_WindowLifterTaskCounter = 0u;

				/* Clear the Execute Flag */
				rub_WindowLifterExecuteFlag = FALSE;
			}
		}break;
		case FULLY_CLOSED_CMD:
		{/* Increase the Window position until reach the max value */
			if(rub_WindowPosition < APP_WINDOW_LIFTER_FULL_CLOSED_VALUE)
			{
				/* Start Closing the window */
				rub_WindowPosition++;

				/* Check if Limit has been reached */
				if(rub_WindowPosition < APP_WINDOW_LIFTER_FULL_CLOSED_VALUE)
				{
					/* Do nothing */
				}
				else
				{
					/* Clear the Execute Flag */
					rub_WindowLifterExecuteFlag = FALSE;
				}
			}
			else
			{
				/* Blink Lower Led */
				rub_BlinkRequestFlag = TRUE;
				rub_BlinkLedSelector = UPPER_LED;

				/* Clear Task Counter */
				rub_WindowLifterTaskCounter = 0u;

				/* Clear the Execute Flag */
				rub_WindowLifterExecuteFlag = FALSE;
			}
		}break;
		case STOP_CMD:
		{
			/* Clear the Execute Flag */
			rub_WindowLifterExecuteFlag = FALSE;
		}break;
		case SET_TO_ONE_CMD:
		{
			/* Set to one window position */
			rub_WindowPosition = 0x01u;

			/* Clear the Execute Flag */
			rub_WindowLifterExecuteFlag = FALSE;
		}break;
		default:
		{
			/* Do nothing */
		}break;
		}
	}
	else
	{//Execution not requested
		/* Do Nothing */
	}

	/* Led Controller Task */
	app_WindowLifterSM_LEDController_Task(rub_WindowPosition);
}

/***********************************************
 * Function Name: app_WindowLifterSM_LEDController_Task
 * Description: TBD
 ***********************************************/
void app_WindowLifterSM_LEDController_Task(T_UBYTE lub_Position)
{
	T_UBYTE lub_LEDsOn;

	/* Check if Position is less or equal as the Led outputs Available */
	if(lub_Position <= sizeof(caub_WindowLifterLedPinNumbers))
	{
		/* Store the leds to must be On */
		lub_LEDsOn = lub_Position;
	}
	else
	{
		lub_LEDsOn = sizeof(caub_WindowLifterLedPinNumbers);
	}


	for(T_UBYTE lub_i = 0;lub_i < sizeof(caub_WindowLifterLedPinNumbers);lub_i++)
	{
		if(lub_i < lub_LEDsOn)
		{
			/* Turn Led On */
			GPIO_ClearPinsOutput((GPIO_Type*)caub_WindowLifterLedGPIOBases[lub_i],1u << caub_WindowLifterLedPinNumbers[lub_i]);
		}
		else
		{
			/* Turn Led Off */
			GPIO_SetPinsOutput((GPIO_Type*)caub_WindowLifterLedGPIOBases[lub_i],1u << caub_WindowLifterLedPinNumbers[lub_i]);
		}
	}
}

/***********************************************
 * Function Name: app_WindowLifterSM_LEDController_Task
 * Description: TBD
 ***********************************************/
void app_WindowLifterSM_BlinkLed_Task(E_LED_SELECTOR lub_Selector)
{
	/* Check if blink is requested */
	if(rub_BlinkRequestFlag == TRUE)
	{//Blink Request

		if(rub_WindowLifterTaskCounter < (APP_WINDOW_LIFTER_BLINKS_AT_LIMIT*APP_WINDOW_LIFTER_BLINKS_MULTIPLIER))
		{
			/* Increase Task Counter */
			rub_WindowLifterTaskCounter++;
			GPIO_TogglePinsOutput((GPIO_Type*)caub_WindowLifterLedGPIOBases[lub_Selector], 1 << caub_WindowLifterLedPinNumbers[lub_Selector]);
		}
		else
		{
			/* Clear Task Counter */
			rub_WindowLifterTaskCounter = 0u;

			/* Increase Task Counter */
			rub_BlinkRequestFlag = FALSE;
		}
	}
	else
	{//Blink not requested
		/* Do Nothing */
	}
}
