/*
 * app_UART.c
 *
 *  Created on: 21/11/2017
 *      Author: uidj2522
 */

#include "MKL25Z4.h"
#include "stdtypedef.h"
#include "fsl_uart.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "app_UART.h"

T_UBYTE rub_UART_RX_Data[16u];
T_UBYTE rub_UART_TX_Data[16u];

T_UBYTE rub_RXRingBufferCounter = 0u;
T_UBYTE rub_TXRingBufferCounter = 0u;

T_UBYTE rub_RXReadBufferCounter = 0u;
T_UBYTE rub_TXReadBufferCounter = 0u;

T_UBYTE rub_DataToBeRead = 0u;
T_UBYTE rub_DataToBeWrite = 0u;

T_UBYTE app_UART_RXHasData(void);
T_UBYTE app_UART_TXIsEmpty(void);

void UART2_IRQHandler(void)//COMO se trata la interrupcion
{
	/* RX Task */
	if(app_UART_RXHasData() == TRUE)
	{
		rub_DataToBeRead++;

		rub_UART_RX_Data[rub_RXRingBufferCounter] = UART_ReadByte(UART2);

		if(rub_RXRingBufferCounter < 15u)
		{
			rub_RXRingBufferCounter++;
		}
		else
		{
			rub_RXRingBufferCounter = 0u;
		}
	}
	else
	{
		/* Do Nothing */
	}

	/* TX Task */
	if(app_UART_TXIsEmpty() == TRUE)
	{
		if(rub_DataToBeWrite)
		{
			rub_DataToBeWrite--;
			UART_WriteByte(UART2, rub_UART_TX_Data[rub_TXRingBufferCounter]);

			if(rub_RXRingBufferCounter < 15u)
			{
				rub_TXRingBufferCounter++;
			}
			else
			{
				rub_TXRingBufferCounter = 0u;
			}
		}
		else
		{
			UART_DisableInterrupts(UART2, kUART_TxDataRegEmptyInterruptEnable);
		}
	}
	else
	{
		/* Do nothing */
	}
}

void app_UART_Init(void)
{
	port_pin_config_t ls_PinConfig;
	uart_config_t ls_UartConfig;

	/* UART Clock Enable */
	CLOCK_EnableClock(kCLOCK_Uart2);
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
	UART_Init(UART2, &ls_UartConfig, CLOCK_GetPllFllSelClkFreq());

	/* UART Enable */
	UART_EnableRx(UART2, TRUE);
	UART_EnableTx(UART2, TRUE);

	/* UART Interrupt Enable */
	UART_EnableInterrupts(UART2, kUART_RxDataRegFullInterruptEnable | kUART_TxDataRegEmptyInterruptEnable);//QUE Interrumpio?
	EnableIRQ(UART2_IRQn);//QUIEN atendera la interrupcion?
}

T_UBYTE app_UART_ReadData(void)
{
	T_UBYTE lub_Data;

	lub_Data = 0u;

	if(rub_DataToBeRead > 0u)
	{
		rub_DataToBeRead--;
		lub_Data = rub_UART_RX_Data[rub_RXReadBufferCounter];

		if(rub_RXReadBufferCounter < 15u)
		{
			rub_RXReadBufferCounter++;
		}
		else
		{
			rub_RXReadBufferCounter = 0u;
		}
	}
	else
	{
		/* Do Nothing */
	}

	return lub_Data;
}

void app_UART_WriteData(T_UBYTE lub_Data)
{
	rub_DataToBeWrite++;

	rub_UART_TX_Data[rub_TXReadBufferCounter] = lub_Data;

	if(rub_TXReadBufferCounter < 15u)
	{
		rub_TXReadBufferCounter++;
	}
	else
	{
		rub_TXReadBufferCounter = 0u;
	}

	UART_EnableInterrupts(UART2, kUART_TxDataRegEmptyInterruptEnable);
}

T_UBYTE app_UART_RXHasData(void)
{
	T_ULONG lul_Status;
	T_UBYTE lub_Return;

	lul_Status = UART_GetStatusFlags(UART1);

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

T_UBYTE app_UART_TXIsEmpty(void)
{
	T_ULONG lul_Status;
	T_UBYTE lub_Return;

	lul_Status = UART_GetStatusFlags(UART1);

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

void app_UART_Task(void)
{

}
