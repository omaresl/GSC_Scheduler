/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* name:            stdtypedef.h
* version:         3.1
* created_by:      MDRR
* date_created:    July 30 2013
*=============================================================================*/
/* DESCRIPTION : Header file for basic types definitions                      */
/*============================================================================*/
/* FUNCTION COMMENT : Defines basic data types to be used by project.         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/may/2010 |                               | C                */
/* Initial version for the Smart Car Race 2010 contest using Freescale        */
/* Bolero micro.                                                              */
/*----------------------------------------------------------------------------*/
/*  2.0      | 28/dec/2012 |                               | MDRR             */
/* Revision of typedefs, added new types. Bitfield order changed to match     */
/* Power PC architecture, boolean macro added, boolean enum aded              */
/*----------------------------------------------------------------------------*/
/*  3.0      | 30/jul/2013 |                               | MDRR             */
/* Modify the included header for the selected microcontroller.               */
/*----------------------------------------------------------------------------*/
/*  3.1      | 26/oct/2013 |                               | Carlos Calvillo  */
/* Filling macro INLINE_FCT with C "inline" keyword.	                      */
/*============================================================================*/
#ifndef STDTYPEDEF_H                             /* To avoid double inclusion */
#define STDTYPEDEF_H

/* Register definitions for selected microcontroller */
#include "MKL25Z4.h"


/* Basic Scalar types */

typedef unsigned char     	T_UBYTE;
typedef unsigned short    	T_UWORD;
typedef unsigned long int 	T_ULONG;
typedef signed char       	T_SBYTE;
typedef signed short      	T_SWORD;
typedef signed long int   	T_SLONG;
typedef unsigned int      	T_FLAG_ARRAY;

/* table of entry pochars */
typedef void(*T_PPROC)(void);

/* basic type pointers */
typedef T_UBYTE * PTR_UBYTE;
typedef T_UWORD * PTR_UWORD;
typedef T_ULONG * PTR_ULONG;
typedef T_SBYTE * PTR_SBYTE;
typedef T_SWORD * PTR_SWORD;
typedef T_SLONG * PTR_SLONG;

typedef T_UBYTE T_BOOLEAN;

/* Carrier of 8 bits */
typedef struct {
	unsigned int	bit7:1;
	unsigned int	bit6:1;
	unsigned int	bit5:1;
	unsigned int	bit4:1;
	unsigned int	bit3:1;
	unsigned int	bit2:1;
	unsigned int	bit1:1;
	unsigned int	bit0:1;
}T_BITFLD8;

/* Carrier of 16 bits */
typedef struct {
	unsigned int	bit15:1;
	unsigned int	bit14:1;
	unsigned int	bit13:1;
	unsigned int	bit12:1;
	unsigned int	bit11:1;
	unsigned int	bit10:1;
	unsigned int	bit9:1;
	unsigned int	bit8:1;
	unsigned int	bit7:1;
	unsigned int	bit6:1;
	unsigned int	bit5:1;
	unsigned int	bit4:1;
	unsigned int	bit3:1;
	unsigned int	bit2:1;
	unsigned int	bit1:1;
	unsigned int	bit0:1;
}T_BITFLD16;

/* Carrier of 32 bits */
typedef struct {
	unsigned int	bit31:1;
	unsigned int	bit30:1;
	unsigned int	bit29:1;
	unsigned int	bit28:1;
	unsigned int	bit27:1;
	unsigned int	bit26:1;
	unsigned int	bit25:1;
	unsigned int	bit24:1;
	unsigned int	bit23:1;
	unsigned int	bit22:1;
	unsigned int	bit21:1;
	unsigned int	bit20:1;
	unsigned int	bit19:1;
	unsigned int	bit18:1;
	unsigned int	bit17:1;
	unsigned int	bit16:1;
	unsigned int	bit15:1;
	unsigned int	bit14:1;
	unsigned int	bit13:1;
	unsigned int	bit12:1;
	unsigned int	bit11:1;
	unsigned int	bit10:1;
	unsigned int	bit9:1;
	unsigned int	bit8:1;
	unsigned int	bit7:1;
	unsigned int	bit6:1;
	unsigned int	bit5:1;
	unsigned int	bit4:1;
	unsigned int	bit3:1;
	unsigned int	bit2:1;
	unsigned int	bit1:1;
	unsigned int	bit0:1;
}T_BITFLD32;

/* Word with msb and lsb handling */
typedef union{
	T_UWORD	wo;
	struct{
		T_UBYTE	msb;
		T_UBYTE	lsb;
		}by;
}T_BYTEFLD;

/* Long with word and byte handling */
typedef union{
	T_ULONG lo;
    struct {
             T_UBYTE highword_msb;
             T_UBYTE highword_lsb;
             T_UBYTE lowword_msb;
             T_UBYTE lowword_lsb;
            } by;
        
    struct {
             T_UWORD highword;
             T_UWORD lowword;
           } wo;
               
}T_BYTEFLD32;

/* Carrier of 8 bits with byte handling */
typedef union {
	T_UBYTE by;
	T_BITFLD8 bi;
}T_FLAG8;

/* Carrier of 16 bits with word or byte (msb & lsb) carrier handling */
typedef union {
	T_BYTEFLD cr;
	T_BITFLD16 bi;
}T_FLAG16;

/* Carrier of 32 bits with word or byte (msb & lsb) carrier handling */
typedef union {
	T_BYTEFLD32 cr;
	T_BITFLD32 bi;
}T_FLAG32;

/* Boolean enum, recomended to use instead of TRUE/FALSE macro */
typedef enum
{
	BFALSE = 0u,
	BTRUE	
}E_BOOLEAN;

/***** Macros definition *****/
#ifndef FALSE
#define FALSE ((T_BOOLEAN)0u)
#endif

#ifndef TRUE
#define TRUE ((T_BOOLEAN)1u)
#endif

#ifndef NULL
#define NULL 0
#endif

/***** Compiler customization *****/
/** Memory macros definition **/
#define IRAM                            /* RAM declaration into internal RAM */
#define NEAR                            /* RAM declaration into near RAM */
#define FAR                             /* RAM declaration into near RAM */
#define PRIVATE_DATA static             /* static data definition */
#define PRIVATE_FCT static              /* private function definition */
#define PUBLIC_DATA extern              /* Public (extern) data definition */
#define PUBLIC_FCT extern               /* Public (extern) function definition */
#define NEAR_FCT                        /* near function definition */
#define FAR_FCT                         /* far function definition */
#define INLINE_FCT inline               /* inline function definition */ 


#endif /* #ifndef STDTYPEDEF_H    #define STDTYPEDEF_H */
