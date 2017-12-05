/*
 * app_UART.c
 *
 *  Created on: 21/11/2017
 *      Author: uidj2522
 */

/******************************************
 * Includes
 ******************************************/
#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "fsl_uart.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "app_UART.h"
#include "fsl_common.h"

/******************************************
 * Variables
 ******************************************/
T_UBYTE raub_UART_RX_Data[APP_UART_BUFFER_SIZE];
T_UBYTE raub_UART_TX_Data[APP_UART_BUFFER_SIZE];

T_UBYTE rub_RXBufferFullFlag = FALSE;
T_UBYTE rub_TXBufferFullFlag = FALSE;

T_UBYTE rub_DataToBeRead = 0u;
T_UBYTE rub_DataToBeWrite = 0u;

/******************************************
 * Prototypes
 ******************************************/
T_UBYTE app_UART_RXHasData(void);
T_UBYTE app_UART_TXIsEmpty(void);

/******************************************
 * Code
 ******************************************/

/***********************************************
 * Function Name: UART2_IRQHandler
 * Description: TBD
 ***********************************************/
void UART2_IRQHandler(void)
{
	/* RX Task */
	if((app_UART_RXHasData() == TRUE) && \
			(rub_RXBufferFullFlag == FALSE))
	{
		if(rub_DataToBeRead < APP_UART_BUFFER_SIZE - 1)
		{
			raub_UART_RX_Data[rub_DataToBeRead] = UART_ReadByte(UART2);
			rub_DataToBeRead++;
		}
		else
		{
			rub_RXBufferFullFlag = TRUE;
		}
	}
	else
	{
		if(rub_RXBufferFullFlag == TRUE)
		{
			//TODO: Error Callback
		}
		else
		{
			/* Do Nothing */
		}

	}

	/* TX Task */
	if(app_UART_TXIsEmpty() == TRUE)
	{
		/* Check if there is data to be write */
		if(rub_DataToBeWrite > 0u)
		{
			rub_DataToBeWrite--;
			UART_WriteByte(UART2, raub_UART_TX_Data[0]);

			//Re arrange the TX Buffer
			for(T_UBYTE lub_i = 0; lub_i < rub_DataToBeWrite; lub_i++)
			{
				raub_UART_TX_Data[lub_i] = raub_UART_TX_Data[lub_i + 1];
			}

			rub_TXBufferFullFlag = FALSE;
		}
		else
		{
			UART_DisableInterrupts(UART2, kUART_TxDataRegEmptyInterruptEnable);
		}
	}
	else
	{
		/* Do Nothing */
	}
}

/***********************************************
 * Function Name: app_UART_Init
 * Description: TBD
 ***********************************************/
void app_UART_Init(void)
{
	port_pin_config_t ls_PinConfig;
	uart_config_t ls_UartConfig;

	/* UART Clock Enable */
	CLOCK_EnableClock(kCLOCK_PortE);

	/* UART Pin Selection */
	ls_PinConfig.mux = kPORT_MuxAlt4;

	PORT_SetPinConfig(PORTE, 22u, &ls_PinConfig);
	PORT_SetPinConfig(PORTE, 23u, &ls_PinConfig);

	/* Get Default Configuration */
	UART_GetDefaultConfig(&ls_UartConfig);

	/* UART Structure Config */
	ls_UartConfig.parityMode = kUART_ParityEven;

	/* UART Init */
	UART_Init(UART2, &ls_UartConfig, CLOCK_GetFreq(BUS_CLK));

	/* UART Enable */
	UART_EnableRx(UART2, TRUE);
	UART_EnableTx(UART2, TRUE);

	/* UART Interrupt Enable */
	UART_EnableInterrupts(UART2, kUART_RxDataRegFullInterruptEnable);
	EnableIRQ(UART2_IRQn);
}

/***********************************************
 * Function Name: app_UART_ReadData
 * Description: TBD
 ***********************************************/
T_UBYTE app_UART_ReadData(T_UBYTE * lpub_Dst)
{
	T_UBYTE lub_Status;

	if(rub_DataToBeRead > 0u)
	{
		rub_DataToBeRead--;
		*lpub_Dst = raub_UART_RX_Data[0];

		/* Re arrange the RX Buffer */
		for(T_UBYTE lub_i = 0; lub_i < rub_DataToBeRead; lub_i++)
		{
			raub_UART_RX_Data[lub_i] = raub_UART_RX_Data[lub_i + 1];
		}

		rub_RXBufferFullFlag = FALSE;
		lub_Status = TRUE;
	}
	else
	{
		lub_Status = FALSE;
	}

	return lub_Status;
}

/***********************************************
 * Function Name: app_UART_WriteData
 * Description: TBD
 ***********************************************/
void app_UART_WriteData(T_UBYTE lub_Data)
{
	if(rub_DataToBeWrite < APP_UART_BUFFER_SIZE - 1)
	{
		raub_UART_TX_Data[rub_DataToBeWrite] = lub_Data;
		rub_DataToBeWrite++;
	}
	else
	{
		rub_TXBufferFullFlag = TRUE;
	}

	UART_EnableInterrupts(UART2, kUART_TxDataRegEmptyInterruptEnable);
}

/***********************************************
 * Function Name: app_UART_RXHasData
 * Description: TBD
 ***********************************************/
T_UBYTE app_UART_RXHasData(void)
{
	T_ULONG lul_Status;
	T_UBYTE lub_Return;

	lul_Status = UART_GetStatusFlags(UART2);

	/* Check if RX Register is full */
	/* Check bit 5 from UART->S1 register */
	if((lul_Status & (kUART_RxDataRegFullFlag) ) == kUART_RxDataRegFullFlag)
	{
		lub_Return = TRUE;
	}
	else
	{
		lub_Return = FALSE;
	}

	return lub_Return;
}

/***********************************************
 * Function Name: app_UART_TXIsEmpty
 * Description: TBD
 ***********************************************/
T_UBYTE app_UART_TXIsEmpty(void)
{
	T_ULONG lul_Status;
	T_UBYTE lub_Return;

	lul_Status = UART_GetStatusFlags(UART2);

	/* Check if TX Register is empty */
	/* Check bit 7 from UART->S1 register */
	if((lul_Status & (kUART_TxDataRegEmptyFlag) ) == kUART_TxDataRegEmptyFlag)
	{
		lub_Return = TRUE;
	}
	else
	{
		lub_Return = FALSE;
	}

	return lub_Return;
}

/***********************************************
 * Function Name: app_UART_Task
 * Description: TBD
 ***********************************************/
void app_UART_Task(void)
{

}
