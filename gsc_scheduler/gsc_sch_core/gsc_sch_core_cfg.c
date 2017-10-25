/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        gsc_sch_core_cfg.c
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013    
*=============================================================================*/
/* DESCRIPTION : Configuartion file of the "Grandpa´s Clock Scheduler" core   */
/*============================================================================*/
/* FUNCTION COMMENT : Here is the table to configure the tasks of the system  */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on mw_schm_cfg module from the old version of   */
/* this scheduler.                                                            */
/*============================================================================*/

/* Includes */
/* -------- */
#include "gsc_sch_core.h"
#include "gsc_sch_core_cfg.h"
#include "periodic_tasks_exec.h"
#include "periodic_tasks_init.h"


/*======================================================================================================================*/
/* Manager/Application main function list */
const S_SCH_MANAGER_EXEC_TYPE cps_mngTaskList[SCHD_MANAGERS_NUMBER] = 
{
   /* Main function,               Init Function,                    Startup delay(ticks),  Execution Period(ticks),   Operation mode */
    {SCHM_NULL_PTR,                periodic_tasks_init_MclDrvs,      0,                     0,                         ALL_MODES},
    {SCHM_NULL_PTR,                periodic_tasks_init_SysDrvs,      0,                     0,                         ALL_MODES},
    {periodic_tasks_exec_5tks,     periodic_tasks_init_task_5tks,    5,                     5,                         ALL_MODES},
    {periodic_tasks_exec_10tks,    periodic_tasks_init_task_10tks,   1000,                  20,                        ALL_MODES},
    {periodic_tasks_exec_20tks,    periodic_tasks_init_task_20tks,   20,                    20,                        ALL_MODES},
    {periodic_tasks_exec_50tks,    periodic_tasks_init_task_50tks,   50,                    50,                        ALL_MODES},
    {periodic_tasks_exec_100tks,   periodic_tasks_init_task_100tks,  100,                   100,                       ALL_MODES},
    {periodic_tasks_exec_500tks,   periodic_tasks_init_task_500tks,  500,                   500,                       ALL_MODES},
    {periodic_tasks_exec_1Mtks,    periodic_tasks_init_task_1Mtks,   1000,                  1000,                      ALL_MODES},
    //{function_task_name,           task_initialization,              0,                     1,                         ALL_MODES},

    /* NOTE: this list shall be updated according to E_MODULES_ID_TYPE! */
};

/*======================================================================================================================*/

