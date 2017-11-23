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
	UART_EnableInterrupts(UART2, kUART_RxActiveEdgeInterruptEnable | kUART_TxDataRegEmptyInterruptEnable);
}
