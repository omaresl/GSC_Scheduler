/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       periodic_tasks_init.h
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION : This file contains the prototypes functions                  */
/* to initialize the periodic tasks                                           */
/*============================================================================*/
/* FUNCTION COMMENT : Main header for periodic_task_init module               */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on initapp module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

#ifndef PERIODIC_TASKS_INIT_H                    /* To avoid double inclusion */
#define PERIODIC_TASKS_INIT_H

/* Includes */
/* -------- */
#include "stdtypedef.h"


/* Exported functions prototypes and macros */
/* ---------------------------------------- */

void periodic_tasks_init_MclDrvs(void);
void periodic_tasks_init_SysDrvs(void);
void periodic_tasks_init_task_5tks(void);
void periodic_tasks_init_task_10tks(void);
void periodic_tasks_init_task_20tks(void);
void periodic_tasks_init_task_50tks(void);
void periodic_tasks_init_task_100tks(void);
void periodic_tasks_init_task_500tks(void);
void periodic_tasks_init_task_1Mtks(void);

#endif


