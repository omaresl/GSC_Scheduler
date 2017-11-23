/*
 * app_Encryption.c
 *
 *  Created on: 21/11/2017
 *      Author: uidj2522
 */

#include "stdtypedef.h"

T_UBYTE rub_LowerNibble;
T_UBYTE rub_HighNibble;

T_UBYTE rub_RXBuffer[8u];

static T_UBYTE app_Encrypt_GetUpperNibble(T_UBYTE lub_Data);
static T_UBYTE app_Encrypt_GetLowerNibble(T_UBYTE lub_Data);

void app_Encrypt_Task(void)
{
	//TODO: Encrypt module tasks
}

static T_UBYTE app_Encrypt_GetUpperNibble(T_UBYTE lub_Data)
{
	T_UBYTE lub_UpperByte;

	lub_UpperByte = (lub_Data & 0xF0) >> 4u;

	return lub_UpperByte;
}

static T_UBYTE app_Encrypt_GetLowerNibble(T_UBYTE lub_Data)
{
	T_UBYTE lub_LowerByte;

	lub_LowerByte = (lub_Data & 0x0F);

	return lub_LowerByte;
}
