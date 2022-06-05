/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       01/06/2022         ********************/
/**************** SWC     :         HSTP             ********************/
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
#include "HSTP_interface.h"
#include "HSTP_config.h"
#include "HSTP_private.h"
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                      Global Variables                                               */
/*******************************************************************************************************/

/*#####################################################################################################*/



/*******************************************************************************************************/
/*                             Stepper Motor Rotation Angle Function                                   */
/*******************************************************************************************************/

u8 Stepper_u8Rotation(u16 Copy_u16Angle , u8 Copy_u8Direction)
{
	u8  Local_u8ErrorState;
	u16 Local_u16_Counter ;
	if((Copy_u16Angle <=360))
	{
		Local_u8ErrorState = STD_TYPES_OK;
		u32 NumberofSteps = (u32)((Copy_u16Angle * 2048UL)/360);
		NumberofSteps = NumberofSteps / 4 ;

		if(Copy_u8Direction == STPR_AntiClockwise)
		{
			for(Local_u16_Counter=0; Local_u16_Counter < NumberofSteps ; Local_u16_Counter++)
			{

				//STEP 1
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_HIGH);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
				_delay_ms(5);

				//STEP 2
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_HIGH);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
				_delay_ms(5);

				//STEP 3
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_HIGH);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
				_delay_ms(5);

				//STEP 4
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_HIGH);
				_delay_ms(5);

			}
		}
		else if(Copy_u8Direction == STPR_Clockwise)
		{
			for(Local_u16_Counter=0; Local_u16_Counter < NumberofSteps ; Local_u16_Counter++)
			{

				//STEP 1
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_HIGH);
				_delay_ms(5);

				//STEP 2
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_HIGH);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
				_delay_ms(5);

				//STEP 3
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_HIGH);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
				_delay_ms(5);

				//STEP 4
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_HIGH);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
				MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);
				_delay_ms(5);
			}
		}
		MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
		MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
		MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
		MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);





	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                              Stepper Motor Stop Rotation Function                                   */
/*******************************************************************************************************/

void Stepper_voidStop(void)
{
	MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_BLUE_COIL,DIO_u8_LOW);
	MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_PINK_COIL,DIO_u8_LOW);
	MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_YELLOW_COIL,DIO_u8_LOW);
	MDIO_u8SetPinValue(STEPPER_MOTOR,STEPPER_MOTOR_ORANGE_COIL,DIO_u8_LOW);

}
