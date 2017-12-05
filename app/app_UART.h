/*
 * app_UART.h
 *
 *  Created on: 21/11/2017
 *      Author: uidj2522
 */

#ifndef APP_UART_H_
#define APP_UART_H_

/******************************************
 * Defines
 ******************************************/
#define APP_UART_BUFFER_SIZE	((T_UBYTE)(16u))

/******************************************
 * Prototypes
 ******************************************/
extern void app_UART_Init(void);
extern void app_UART_Task(void);
extern T_UBYTE app_UART_ReadData(T_UBYTE * lpub_Dst);

#endif /* APP_UART_H_ */
