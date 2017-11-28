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

T_UBYTE rub_UART_RX_Data;
T_UBYTE rub_UART_TX_Data;

void UART2_IRQHandler(void)//COMO se trata la interrupcion
{
	/* RX Task */
	if(app_UART_RXHasData() == TRUE)
	{
		rub_UART_RX_Data = app_UART_ReadData();
	}
	else
	{
		/* Do Nothing */
	}

	/* TX Task */
	if(app_UART_TXIsEmpty() == TRUE)
	{
		app_UART_WriteData(rub_UART_TX_Data);
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
	return UART_ReadByte(UART2);
}

void app_UART_WriteData(T_UBYTE lub_Data)
{
	UART_WriteByte(UART2, lub_Data);
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
