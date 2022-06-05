/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       30/05/2022         ********************/
/**************** SWC     :         HKPD             ********************/
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
/*                                    Include  LCD Header Files                                        */
/*******************************************************************************************************/
#include "HKPD_interface.h"
#include "HKPD_private.h"
#include "HKPD_config.h"
/*#####################################################################################################*/


static u8 KPD_Au8Keys[4][4] = KPD_Au8_KEY_VALUES;

static u8 KPD_Au8RowsPins[4]={KPD_u8_R1_PIN, KPD_u8_R2_PIN, KPD_u8_R3_PIN, KPD_u8_R4_PIN};
static u8 KPD_Au8ColsPins[4]={KPD_u8_C1_PIN, KPD_u8_C2_PIN, KPD_u8_C3_PIN, KPD_u8_C4_PIN};


/*******************************************************************************************************/
/*                            KEYPAD Function that Gets The Pressed KEY                                */
/*******************************************************************************************************/
/*                         ROWS are Output     &      COLUMNS  are Input                               */
/*******************************************************************************************************/
u8 HKEYPAD_u8GetPressedKey(u8 * Copy_pu8ReturnedKey)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8_RowsCounter,Local_u8_ColsCounter,Local_u8ReturnedPinValue,Local_u8Flag = 0;
	/* Check Pointer validation */
	if(Copy_pu8ReturnedKey != NULL)
	{
		*Copy_pu8ReturnedKey = KPD_u8_KEY_NOT_PRESSED;
		for(Local_u8_RowsCounter=0 ; Local_u8_RowsCounter <=3 ; Local_u8_RowsCounter++)
		{
			MDIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8_RowsCounter],DIO_u8_LOW);
			/* Read Coloumns */
			for(Local_u8_ColsCounter=0 ; Local_u8_ColsCounter<=3 ; Local_u8_ColsCounter++)
			{
				MDIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8_ColsCounter],&Local_u8ReturnedPinValue);
				/* Check if Switch is pressed */
				if(Local_u8ReturnedPinValue == DIO_u8_LOW)
				{
					/* Debouncing */
					_delay_ms(20);
					while(Local_u8ReturnedPinValue == DIO_u8_LOW)
					{
						MDIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8_ColsCounter],&Local_u8ReturnedPinValue);
					}
					_delay_ms(10);
					* Copy_pu8ReturnedKey = KPD_Au8Keys[Local_u8_RowsCounter][Local_u8_ColsCounter];
					Local_u8Flag = 1;
					/* to terminate the loop if the switch is pressed */
					break;

				}
			}
			/* Deactivate currently Row  */
			MDIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8_RowsCounter],DIO_u8_HIGH);
			if(Local_u8Flag == 1)
			{
				break;
			}
		}

	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;

}
/*#####################################################################################################*/
