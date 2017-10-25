/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       gsc_sch_core_tick_isr.h
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION : Header of the tick source file for the                       */
/* "Grandpa´s Clock Scheduler"                                                */
/*============================================================================*/
/* FUNCTION COMMENT : Header of the tick source file                          */
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

#ifndef GSC_SCH_CORE_TICK_ISR_H
#define GSC_SCH_CORE_TICK_ISR_H

 
/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "gsc_sch_core.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*======================================================*/ 
/* Declaration of exported constants                    */
/*======================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */


/* Custom type constants */


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/* Custom type RAM variables */
/* Module execution flag is set in timer interrupt handler */
PUBLIC_DATA volatile SCH_BOOLEAN re_sch_mngExecflag;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
void gsc_sch_core_tick_isr(void);

/* Functions macros */


/* Exported defines */


#endif /* GSC_SCH_CORE_TICK_ISR_H */


