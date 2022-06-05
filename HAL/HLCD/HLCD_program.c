/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       28/05/2022         ********************/
/**************** SWC     :         HLCD             ********************/
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
#include "HLCD_interface.h"
#include "HLCD_private.h"
#include "HLCD_config.h"
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                                    LCD Initialization Function                                      */
/*******************************************************************************************************/
void HLCD_voidInit     (void)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		_delay_ms(40);
		/*send function set command*/
		HLCD_voidSendCmnd(FUNCTION_SET);
		_delay_us(40);
		/*send LCD On Off command*/
		HLCD_voidSendCmnd(LCD_DISPLAY_ON_OFF);
		_delay_us(40);
		/*send LCD Display Clear command*/
		HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
		_delay_ms(2);
		/*send Entry Mode Set command*/
		HLCD_voidSendCmnd(LCD_ENTRY_MODE);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{


		_delay_ms(50);
		/*send function set command*/
		HLCD_voidSendCmnd(FUNCTION_SET_4BITS>>4);
		HLCD_voidSendCmnd(FUNCTION_SET_4BITS>>4);
		HLCD_voidSendCmnd(FUNCTION_SET_4BITS);
		_delay_ms(1);
		/*send LCD On Off command*/
		HLCD_voidSendCmnd(LCD_DISPLAY_ON_OFF>>4);
		HLCD_voidSendCmnd(LCD_DISPLAY_ON_OFF);
		_delay_ms(1);
		/*send LCD Display Clear command*/
		HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR>>4);
		HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
		_delay_ms(2);
		/*send Entry Mode Set command*/
		HLCD_voidSendCmnd(LCD_ENTRY_MODE>>4);
		HLCD_voidSendCmnd(LCD_ENTRY_MODE);
	}
#else
	{
      #error "Wrong LCD Mode Choice"
	}
#endif

}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                   Clears LCD Display Function                                       */
/*******************************************************************************************************/
void HLCD_voidClear       (void)
{

#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
		_delay_ms(2);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR>>4);
		HLCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
		_delay_ms(2);
	}
#endif
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                   Turns off Cursor Blinker Function                                 */
/*******************************************************************************************************/
void HLCD_voidCursorBlinkerOff(void)
{

#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_BLINKER_OFF);
		_delay_ms(2);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_BLINKER_OFF>>4);
		HLCD_voidSendCmnd(LCD_BLINKER_OFF);
		_delay_ms(2);
	}
#endif

}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                   LCD Send Command Function                                         */
/*******************************************************************************************************/
void HLCD_voidSendCmnd (u8 Copy_u8Cmnd)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		/* Rs = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
		/* Rw = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
		/* Send Cmnd byte to the Data Pins of LCD */
		MDIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
		/* Pulse of Enable E = 1 , E = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
		_delay_us(1);
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
		_delay_us(1);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		/* Rs = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
		/* Rw = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);

		/* Send Cmnd byte to the Data Pins of LCD */
		MDIO_u8Set4PinsValue(LCD_u8_DATA_PORT,LCD_u8_4BIT_START_PIN,Copy_u8Cmnd);

		/* Pulse of Enable E = 1 , E = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
		_delay_ms(2);
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);

	}
#endif

}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                              Configure LCD to Send Data Function                                    */
/*******************************************************************************************************/
static void HLCD_voidSendChar (u8 Copy_u8Char)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		/* Rs = 1 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
		/* Rw = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
		/* Send Char byte to the Data Pins of LCD */
		MDIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
		/* Pulse of Enable E = 1 , E = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
		_delay_us(1);
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
		_delay_us(1);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		/* Rs = 1 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
		/* Rw = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);

		/* Send Char byte to the 4 Data Pins of LCD */
		MDIO_u8Set4PinsValue(LCD_u8_DATA_PORT,LCD_u8_4BIT_START_PIN,Copy_u8Char);
		/* Pulse of Enable E = 1 , E = 0 */
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
		_delay_ms(2);
		MDIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);

	}
#endif

}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                               Display Character on LCD Function                                     */
/*******************************************************************************************************/
void HLCD_voidWriteChar (u8 Copy_u8Char)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		HLCD_voidSendChar ( Copy_u8Char);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		HLCD_voidSendChar ( Copy_u8Char>>4);
		HLCD_voidSendChar ( Copy_u8Char);
	}
#endif

}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                               Display String on LCD Function                                        */
/*******************************************************************************************************/
void HLCD_voidWriteString (u8 * Copy_pu8String)
{
	if(Copy_pu8String != NULL )
	{
		u8 x = 0;
		u8 i = 0;
		while(Copy_pu8String[x] != '\0')
		{
			x++ ;
			for(  ; i < x; i++)
			{
				/* Write Character on LCD */
				HLCD_voidWriteChar (Copy_pu8String[i]);
			}

		}
	}

}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                           Configure Position on LCD Function                                        */
/*******************************************************************************************************/
u8 HLCD_u8_GoTo_XY     (u8 Copy_u8X,u8 Copy_u8Y)
{

	u8 Local_u8ReturnState = STD_TYPES_OK;
	if((Copy_u8X <=1)&&(Copy_u8Y <= 39))
	{
#if(LCD_MODE == LCD_8_BIT_MODE)
		{
			switch(Copy_u8X)
			{

			case LCD_u8_LINE0 : HLCD_voidSendCmnd(0x80 + Copy_u8Y);break;

			case LCD_u8_LINE1 : HLCD_voidSendCmnd(0xC0 + Copy_u8Y);break;
			}
		}
#elif(LCD_MODE == LCD_4_BIT_MODE)
		{
			switch(Copy_u8X)
			{

			case LCD_u8_LINE0 :
				HLCD_voidSendCmnd((0x80 + Copy_u8Y)>>4);
			    HLCD_voidSendCmnd (0x80 + Copy_u8Y);
			break;

			case LCD_u8_LINE1 :
				HLCD_voidSendCmnd((0xC0 + Copy_u8Y)>>4);
				HLCD_voidSendCmnd( 0xC0 + Copy_u8Y);
				break;
			}
		}
#endif

	}
	else
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}
	return Local_u8ReturnState;


}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                               Display Number on LCD Function                                        */
/*******************************************************************************************************/
void HLCD_voidWriteNumber (u32  Copy_u32Num)
{

	u8 Arr[10];
	u8 Local_Remainder = 1;
	u32 Local_Number = Copy_u32Num;
	u8 Local_Counter = 0;
	u8 Local_Counter2 ;


	for(u8 initial = 10 ; initial >=1 ; initial--)
	{
		Local_Remainder = Local_Number % 10 ;
		Local_Number    = Local_Number /10 ;

		if((Local_Remainder ==0) && (Local_Number<1) && (Local_Counter>0) )
		{
			break;
		}
		Local_Counter ++;
		Arr[initial-1] = Local_Remainder ;
	}

	for(Local_Counter2 = 10 - Local_Counter; Local_Counter2 < 10 ; Local_Counter2 ++)
	{
		HLCD_voidWriteChar(Arr[Local_Counter2]+48);
	}



}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                Send And Display Special Character on LCD Function                                   */
/*******************************************************************************************************/
void HLCD_voidSendSpecialChar(u8 Copy_u8CharNo,u8 Copy_u8X,u8 Copy_u8Y,u8 * Copy_PSpecialChar)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		switch(Copy_u8CharNo)
		{
		case 0:
			HLCD_voidSendCmnd(0b01000000);

			break;
		case 1:
			HLCD_voidSendCmnd(0b01001000);
			break;
		case 2:
			HLCD_voidSendCmnd(0b01010000);
			break;
		case 3:
			HLCD_voidSendCmnd(0b01011000);
			break;
		case 4:
			HLCD_voidSendCmnd(0b01100000);
			break;
		case 5:
			HLCD_voidSendCmnd(0b01101000);
			break;
		case 6:
			HLCD_voidSendCmnd(0b01110000);
			break;
		case 7:
			HLCD_voidSendCmnd(0b01111000);
			break;
		}
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		switch(Copy_u8CharNo)
		{
		case 0:
			HLCD_voidSendCmnd(0b01000000>>4);
			HLCD_voidSendCmnd(0b01000000);
			break;
		case 1:
			HLCD_voidSendCmnd(0b01001000>>4);
			HLCD_voidSendCmnd(0b01001000);
			break;
		case 2:
			HLCD_voidSendCmnd(0b01010000>>4);
			HLCD_voidSendCmnd(0b01010000);
			break;
		case 3:
			HLCD_voidSendCmnd(0b01011000>>4);
			HLCD_voidSendCmnd(0b01011000);
			break;
		case 4:
			HLCD_voidSendCmnd(0b01100000>>4);
			HLCD_voidSendCmnd(0b01100000);
			break;
		case 5:
			HLCD_voidSendCmnd(0b01101000>>4);
			HLCD_voidSendCmnd(0b01101000);
			break;
		case 6:
			HLCD_voidSendCmnd(0b01110000>>4);
			HLCD_voidSendCmnd(0b01110000);
			break;
		case 7:
			HLCD_voidSendCmnd(0b01111000>>4);
			HLCD_voidSendCmnd(0b01111000);
			break;
		}
	}
#endif



     /* Display Special Character on LCD */
	for(u8 specialchar=0 ; specialchar<8 ; specialchar++ )
	{
		HLCD_voidWriteChar(Copy_PSpecialChar[specialchar]);
	}

	HLCD_u8_GoTo_XY( Copy_u8X, Copy_u8Y);
	HLCD_voidWriteChar(Copy_u8CharNo);


}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                        LCD Shift Display to The Right Function                                      */
/*******************************************************************************************************/
void HLCD_voidShiftDispRight(void)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_SHIFT_RIGHT);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_SHIFT_RIGHT>>4);
		HLCD_voidSendCmnd(LCD_SHIFT_RIGHT);
	}
#endif
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                        LCD Shift Display to The Left Function                                      */
/*******************************************************************************************************/
void HLCD_voidShiftDispLeft(void)
{
#if(LCD_MODE == LCD_8_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_SHIFT_LEFT);
	}
#elif(LCD_MODE == LCD_4_BIT_MODE)
	{
		HLCD_voidSendCmnd(LCD_SHIFT_LEFT>>4);
		HLCD_voidSendCmnd(LCD_SHIFT_LEFT);
	}
#endif
}
/*#####################################################################################################*/


