/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       28/05/2022         ********************/
/**************** SWC     :         HLCD             ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/
#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H

/*******************************************************************************************************/
/*                                 Macros for LCD Line                                                 */
/*******************************************************************************************************/
#define LCD_u8_LINE0           0
#define LCD_u8_LINE1           1
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                   Prototypes of the LCD driver                                      */
/*******************************************************************************************************/

void HLCD_voidInit        (void);

void HLCD_voidClear       (void);

void HLCD_voidCursorBlinkerOff(void);
					     
void HLCD_voidSendCmnd    (u8 Copy_u8Cmnd);

void HLCD_voidWriteChar   (u8 Copy_u8Char);
						
void HLCD_voidWriteString (u8 *Copy_pu8String);

u8 HLCD_u8_GoTo_XY        (u8 Copy_u8X,u8 Copy_u8Y);

void HLCD_voidWriteNumber (u32 Copy_u32Num);

void HLCD_voidSendSpecialChar(u8 Copy_u8CharNo,u8 Copy_u8X,u8 Copy_u8Y,u8 * Copy_PSpecialChar);

void HLCD_voidShiftDispRight(void);

void HLCD_voidShiftDispLeft(void);

/*#####################################################################################################*/



#endif                  
