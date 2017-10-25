/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        gsc_sch_core.c
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION : Tick source file for the "Grandpa´s Clock Scheduler"         */
/*============================================================================*/
/* FUNCTION COMMENT : Tick generation source file                             */
/*                                                                            */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on mw_schm_tmr_isr module from the old version  */
/* of this scheduler.                                                         */
/*============================================================================*/

/* Includes */
/* -------- */
#include "gsc_sch_core_tick_isr.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */


/* Custom type constants */


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/* Custom type RAM variables */
/* Module execution flag */
volatile SCH_BOOLEAN re_sch_mngExecflag = SCH_FALSE;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : gsc_sch_core_tick_isr
 *  Description          : This is the tick flag generation. This function must be 
                           called from a periodic high priority interrupt. The period
						   of this interrupt must define the "tick cycle time"
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
INLINE_FCT void gsc_sch_core_tick_isr (void)
{
	/* Set flag so background will run */
    re_sch_mngExecflag = SCH_TRUE;
}
