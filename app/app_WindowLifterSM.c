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

/******************************************
 * Defines
 ******************************************/
#define OPENING_CMD					(T_UBYTE)(0x01u)
#define CLOSING_CMD   				(T_UBYTE)(0x02u)
#define FULLY_OPEN_CMD      		(T_UBYTE)(0x03u)
#define FULLY_CLOSED_CMD    		(T_UBYTE)(0x04u)
#define STOP_CMD            		(T_UBYTE)(0x0Fu)

#define NRC_NOT_VALID_CMD			(T_UBYTE)(0x05u)
#define NRC_VALIDATION_FAILED   	(T_UBYTE)(0x06u)
#define NRC_OPEN_CMD_W_FOPEN  		(T_UBYTE)(0x07u)
#define NRC_CLOSED_CMD_W_FCLOSED 	(T_UBYTE)(0x08u)

#define APP_WINDOW_LIFTER_FULL_OPEN_VALUE		(T_UBYTE)(0u)
#define APP_WINDOW_LIFTER_FULL_CLOSED_VALUE		(T_UBYTE)(10u)
#define APP_WINDOW_LIFTER_SINGLE_STEP			(T_UBYTE)(2u)

/******************************************
 * Constants
 ******************************************/
const T_UBYTE caub_WindowLifterCommands[] =
{
		OPENING_CMD,
		CLOSING_CMD,
		FULLY_OPEN_CMD,
		FULLY_CLOSED_CMD,
		STOP_CMD
};

const T_UBYTE caub_WindowLifterErrorCodes[] =
{
		OPENING_CMD,
		CLOSING_CMD,
		FULLY_OPEN_CMD,
		FULLY_CLOSED_CMD,
};

typedef enum
{
	UPPER_LED,
	LOWER_LED
}E_LEDTOBETOGGLE;

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
	re_WindowLifterState = WINDOW_LIFTER_STATE_IDLE;
	rub_CMDIndex = 0u;
	rub_WindowLifterExecuteFlag = FALSE;
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
		RED_TOGGLE;
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
		/* Check which command was received */
		switch(rub_LastValidCMDReceived)
		{
		case OPENING_CMD:
		{/* Increase the Window position by 2 steps */
			rub_WindowLifterExecuteFlag = FALSE;
		}break;
		case CLOSING_CMD:
		{

		}break;
		case FULLY_OPEN_CMD:
		{

		}break;
		case FULLY_CLOSED_CMD:
		{

		}break;
		case STOP_CMD:
		{

		}break;
		default:
		{

		}break;
		}
	}
	else
	{//Execution not requested
		/* Do Nothing */
	}
}
