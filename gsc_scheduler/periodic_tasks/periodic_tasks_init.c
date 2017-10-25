/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        periodic_tasks_init.c
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013
*=============================================================================*/
/* DESCRIPTION :  Definition of functions to initialize periodic tasks        */
/*============================================================================*/
/* FUNCTION COMMENT : Add here the user initialization for the                */
/* functionalities to execute periodically. Be congruent with periodic        */
/* tasks contain                                                              */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on initapp module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

/* Includes */
/* -------- */
#include "periodic_tasks_init.h"
#include "periodic_tasks_modules.h"


/**************************************************************
 *  Name                 : periodic_tasks_init_MclDrvs
 *  Description          : Initialize needed microcontroller drivers (pheripherals) before start application
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
void periodic_tasks_init_MclDrvs(void)
{
	
}

/**************************************************************
 *  Name                 : periodic_tasks_init_SysDrvs
 *  Description          : Initialize needed system drivers (system elements) before start application
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
void periodic_tasks_init_SysDrvs(void)
{
	init_leds();
}

/**************************************************************
 *  Name                 : periodic_tasks_init_task_5tks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_5tks(void)
 {

 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_init_task_10tks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_10tks(void)
 {

 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_init_task_20tks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_20tks(void)
 {

 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_init_task_50tks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_50tks(void)
 {
	
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_init_task_100tks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_100tks(void)
 {

 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_init_task_500tks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_500tks(void)
 {

 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_init_task_1Mtks
 *  Description          : Container for initialization of functionality that is
                           executed periodically
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_init_task_1Mtks(void)
 {
 
 }
 
