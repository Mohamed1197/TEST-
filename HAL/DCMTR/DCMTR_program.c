/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       01/06/2022         ********************/
/**************** SWC     :         DCMTR            ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/

/*******************************************************************************************************/
/*                                       Include  LIB Layer                                            */
/*******************************************************************************************************/
#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                       Include  DIO Driver                                           */
/*******************************************************************************************************/
#include "../../MCAL/MDIO/MDIO_interface.h"
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                Include  Stepper Header Files                                        */
/*******************************************************************************************************/
#include "DCMTR_interface.h"
#include "DCMTR_config.h"
#include "DCMTR_private.h"
/*#####################################################################################################*/


void DC_voidRotation(u8 Copy_u8Direction)
{
	if(Copy_u8Direction == DCMTR_Clockwise)
	{
		MDIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_REVERSE,DIO_u8_LOW);
		MDIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_FORWARD,DIO_u8_HIGH);
	}
	else if(Copy_u8Direction == DCMTR_AntiClockwise)
	{
		MDIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_FORWARD,DIO_u8_LOW);
		MDIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_REVERSE,DIO_u8_HIGH);
	}


}

void DC_voidStop(void)
{
	MDIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_FORWARD,DIO_u8_LOW);
	MDIO_u8SetPinValue(DC_MOTOR,DC_MOTOR_REVERSE,DIO_u8_LOW);
}
