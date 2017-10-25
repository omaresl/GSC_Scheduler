/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       periodic_tasks_exec.h
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION : This file contains the periodic tasks prototypes functions   */
/*============================================================================*/
/* FUNCTION COMMENT : Main header for periodic_task_exec module               */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on apptask module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

#ifndef PERIODIC_TASKS_EXEC_H                    /* To avoid double inclusion */
#define PERIODIC_TASKS_EXEC_H

/* Includes */
/* -------- */
#include "stdtypedef.h"


/* Exported functions prototypes and macros */
/* ---------------------------------------- */

void periodic_tasks_exec_5tks(void);
void periodic_tasks_exec_10tks(void);
void periodic_tasks_exec_20tks(void);
void periodic_tasks_exec_50tks(void);
void periodic_tasks_exec_100tks(void);
void periodic_tasks_exec_500tks(void);
void periodic_tasks_exec_1Mtks(void);

#endif /* PERIODIC_TASKS_EXEC_H  */


