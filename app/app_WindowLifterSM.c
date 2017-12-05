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
#define OPENING_CMD			(T_UBYTE)(0x01u)
#define CLOSING_CMD   		(T_UBYTE)(0x02u)
#define FULLY_OPEN_CMD      (T_UBYTE)(0x03u)
#define FULLY_CLOSED_CMD    (T_UBYTE)(0x04u)
#define STOP_CMD            (T_UBYTE)(0x0Fu)

/******************************************
 * Constants
 ******************************************/
const T_UBYTE caub_WindowLifterCommands[5] =
{
		OPENING_CMD,
		CLOSING_CMD,
		FULLY_OPEN_CMD,
		FULLY_CLOSED_CMD,
		STOP_CMD
};

/******************************************
 * Variables
 ******************************************/
E_WINDOW_LIFTER_STATE re_WindowLifterState = WINDOW_LIFTER_STATE_IDLE;
T_UBYTE rub_CMDIndex;
T_UBYTE rub_WindowLifterExecuteFlag;
T_UBYTE rub_LastValidCMDReceived;

/******************************************
 * Prototypes
 ******************************************/
static T_UBYTE app_WindowLifterSM_DecryptData(T_UBYTE lub_Data);
static T_UBYTE app_WindowLifterSM_GetUpperNibble(T_UBYTE lub_Data);
static T_UBYTE app_WindowLifterSM_GetLowerNibble(T_UBYTE lub_Data);
static T_UBYTE app_WindowLifterSM_GetJoinNibbles(T_UBYTE lub_A,T_UBYTE lub_B);
static T_UBYTE app_WindowLifterSM_CommandValidation(T_UBYTE lub_Command);

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
			/* Check if received data is valid */
			for(T_UBYTE lub_i = 0; lub_i < sizeof(caub_WindowLifterCommands);lub_i++)
			{
				/* Compare with the cmd table */
				if((lub_CMD_Received & APP_WINDOW_LIFTER_CMD_MASK) == caub_WindowLifterCommands[lub_i])
				{//Command Valid
					/* Store CMD Valid Index */
					rub_CMDIndex = lub_i;

					/* Store CMD Valid */
					rub_LastValidCMDReceived = lub_CMD_Received;

					/* Go to Decrypt State */
					re_WindowLifterState = WINDOW_LIFTER_STATE_DECRYPT;

					/* Finish the loop */
					lub_i = sizeof(caub_WindowLifterCommands);
				}
				else
				{
					/* Command not match with actual element */
				}
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

		/* Send Positive Response */

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

	if(lub_Command == CMD_OPENING ||
			lub_Command == CMD_CLOSING||
			lub_Command == CMD_FULLOPEN||
			lub_Command == CMD_FULLCLOSE||
			lub_Command == CMD_STOP
			)
	{
		lub_Result = TRUE;
	}
	else
	{
		lub_Result = FALSE;
	}

	return lub_Result;
}




