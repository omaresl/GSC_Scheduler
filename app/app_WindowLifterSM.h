/*
 * app_WindowLifterSM.h
 *
 *  Created on: 30/11/2017
 *      Author: uidj2522
 */

#ifndef APP_WINDOWLIFTERSM_H_
#define APP_WINDOWLIFTERSM_H_

/******************************************
 * Typedefs
 ******************************************/
typedef enum
{
	WINDOW_LIFTER_STATE_IDLE,
	WINDOW_LIFTER_STATE_DECRYPT,
	WINDOW_LIFTER_STATE_EXECUTE,
	WINDOW_LIFTER_STATE_ERROR,
	WINDOW_LIFTER_STATE_N_STATES
}E_WINDOW_LIFTER_STATE;

/******************************************
 * Defines
 ******************************************/
#define APP_WINDOW_LIFTER_DEBUG_IN_CONSOLE

#define APP_WINDOW_LIFTER_CMD_MASK	0x0F

#define CMD_OPENING		0x01u
#define CMD_CLOSING		0x02u
#define CMD_FULLOPEN	0x03u
#define CMD_FULLCLOSE	0x04u
#define CMD_STOP		0x0Fu

/******************************************
 * Variables
 ******************************************/

/******************************************
 * Prototypes
 ******************************************/
extern void app_WindowLifterSM_Init(void);
extern void app_WindowLifterSM_Task(void);

#endif /* APP_WINDOWLIFTERSM_H_ */
