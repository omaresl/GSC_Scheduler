/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       gsc_sch_core.h
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION : Header of the core of the "Grandpa´s Clock Scheduler"        */
/*============================================================================*/
/* FUNCTION COMMENT : Header of the main scheduler file with                  */
/* initailization and manager                                                 */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on mw_schm module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

#ifndef GSC_SCH_CORE_H
#define GSC_SCH_CORE_H

 
/* Includes */
/* -------- */
#include "stdtypedef.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */

/* Operation mode type */
typedef T_UWORD T_OpModeType;

/* Task delay type */
typedef T_UWORD T_TaskDelayType;

/* Delay manager type */
typedef T_SWORD T_DelayMainType;

/* Boolean scheduler type */
typedef enum
{
    SCH_FALSE = 0,
    SCH_TRUE  = 1
}SCH_BOOLEAN;

/* Type definition for pointer to main functions of the managers */
typedef void (*T_SCH_MANAGER_API_TYPE)(void);

/* Type definition for main functions of the managers and their execution period */
typedef struct{
    /* The main function */
    T_SCH_MANAGER_API_TYPE  ManagerAPI; 
    /* The Init function */
    T_SCH_MANAGER_API_TYPE  ManagerInitAPI; 
    /* Delay of submodule execution from Scheduler start (in ticks) */
    const T_TaskDelayType StartUpDelay;
    /* Module is executed each 'ExecutionPeriod' time (in ticks) */
    const T_TaskDelayType ExecutionPeriod;
    /* Module is executed in the modes indicated  here */
    T_OpModeType UsedInMode; 
     
} S_SCH_MANAGER_EXEC_TYPE;


/*======================================================*/ 
/* Declaration of exported constants                    */
/*======================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 


/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
void gsc_sch_core_Init(void);
void gsc_sch_core_exec(void);

/* Functions macros */

/* Exported defines */
  /* Null constant if not App or Init routine */
#define SCHM_NULL_PTR (T_SCH_MANAGER_API_TYPE)0
 /* */
#define STEP_IN_TICKS (T_DelayMainType)1


#endif /* GSC_SCH_CORE_H */
