/*******************************************************************************************************/
/* Author            : Ahmed khaled Hammad                                                             */
/* Version           : V0.0.0                                                                          */
/* Data              : 18 May 2022                                                                     */
/* Description       : main.c --> IMT_Osliscope                                                        */
/* Project Features  :                                                                                 */
/*      1- Display Digital Signal On LCD                                                               */
/*		2- Calculate Digital Signal Frequency ,Duty Cycle                                              */
/*      3- Generate PWM with different Duty cycle controlled by potentiometer                          */
/*      4- Display Calculated  Signal Frequency ,Duty Cycle on LCD                                     */
/* Future Updates:                                                                                     */
/*      1- Generate and  Read Analog Signal like sine wave                                             */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../LIB/LSTD_TYPES.h"
#include "../LIB/LBIT_MATH.h"


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/

#include"../MCAL/MDIO/MDIO_Interface.h"         //for DIO


/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/

#include"../HAL/HLCD/HLCD_interface.h"         //for LCD
            //for LED

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                   Service Layer  Components                                         */
/*******************************************************************************************************/

#define F_CPU  8000000UL
#include<util\delay.h>

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Global Variables(Flag)                                         */
/*******************************************************************************************************/

/* Functions Prototype  */



int main(void)
{
   MDIO_u8Init();


	/* Peripherals Initialization */

    HLCD_voidInit();


	/* Calls a Functions that asks the user to enter Password */
//	Ask_For_Login();

    while(1)
    {

    	/* Calls a Functions that Displays The Current Temperature  */
    //	Display_Temperature_LCD();

    	HLCD_voidWriteChar('a');

    	_delay_ms(1000);
        HLCD_voidClear();
    	_delay_ms(1000);








    }


	return 0;
}

//
///* Functions Implementation  */
//void Display_Temperature_LCD(void)
//{
//	u16 Digital_Value, Analog_value;
//	u8 Temerature , Temerature_dec;
//
//	MADC_u8GetDigitalValueSunchNonBlocking(ADC_u8_CHANNEL_2,&Digital_Value);
//	Analog_value = (u16)((Digital_Value*5000UL)/1024);
//	Temerature_dec = (Analog_value % 10);
//	Temerature = (Analog_value/10);
//
//	HCLCD_voidCursorBlinkerOff();
//	HCLCD_voidClear();
//	HCLCD_u8_GoTo_XY(0,1);
//	HCLCD_voidWriteString("Temperature");
//	HCLCD_u8_GoTo_XY(1,1);
//	HCLCD_voidWriteNumber(Temerature);
//	HCLCD_voidWriteString(".");
//	HCLCD_voidWriteNumber(Temerature_dec);
//	HCLCD_u8_GoTo_XY(1,6);
//	HCLCD_voidWriteString("C");
//
//}
//
//
//
//void Ask_For_Login(void)
//{
//    u8 Local_u8Key;
//    static u16 password = 2580 ,value , Num1=0;
//    static u8 Operator = 0,counter=0 , counter2=0;
//
//    HCLCD_voidWriteString("Enter Passcode :");
//    HCLCD_u8_GoTo_XY(1,4);
//	while(1)
//	{
//	//	KPD_u8GetKey(&Local_u8Key);
//	       if(Local_u8Key != 0)
//	       {
//	    	   if(counter<4)
//	    	   {
//	    		   counter++;
//
//	    	   switch(Local_u8Key)
//	    	   {
//	    	   case '0':
//	    		   value =0;
//	    		   Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('0');
//	    		   break;
//	    	   case '1':
//	    		   value =1;
//	    		   Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('1');
//	    		   break;
//	    	   case '2':
//	    	       value =2;
//	    	       Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('2');
//	    	       break;
//	    	   case '3':
//	    	       value =3;
//	    	       Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('3');
//	    	       break;
//	    	   case '4':
//	    	       value =4;
//	    	       Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('4');
//	    	       break;
//	    	   case '5':
//	    	       value =5;
//	    	       Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('5');
//	    	       break;
//	    	   case '6':
//	    	       value =6;
//	    	       Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('6');
//	    	       break;
//	    	   case '7':
//	    	       value =7;
//	    	       Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('7');
//	    	        break;
//	       	   case '8':
//	        	   value =8;
//	        	   Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('8');
//	        	    break;
//	           case '9':
//	        	   value =9;
//	        	   Num1 = (Num1*10) +value ;
//	    		   HCLCD_voidSendChar('9');
//	        	    break;
//	           default:
//	        	   HCLCD_voidClear();
//
//	        	   HCLCD_u8_GoTo_XY(0,1);
//	        	   HCLCD_voidWriteString("Please Enter");
//
//	        	   HCLCD_u8_GoTo_XY(1,1);
//	        	   HCLCD_voidWriteString("Numbers Only");
//	        	   _delay_ms(1500);
//
//	        	   HCLCD_voidClear();
//	        	   HCLCD_voidWriteString("Try Again ");
//	        	   HCLCD_u8_GoTo_XY(1,4);
//	        	   _delay_ms(500);
//	        	   counter =0 ;
//
//	    	   }
//
//	    	   }
//	    	   if(counter>3)
//	    	   {
//	    		   if(Num1 == password)
//	    		   {
//	    		   _delay_ms(1000);
//
//	    		   HCLCD_voidClear();
//	    		   HCLCD_voidCursorBlinkerOff();
//	    		   HCLCD_voidWriteString(" Welcome Mohamed");
//	    		   _delay_ms(1000);
//	    		   break;
//	    		   }
//	    		   else
//	    		   {
//
//	    			   if(counter2 < 2)
//	    			   {
//	    	    		 _delay_ms(1000);
//	    	    		 HCLCD_voidInit();
//	    			     HCLCD_voidWriteString("  Try Again ");
//	    			     counter = 0 ;
//	    			     Num1=0;
//	    			     counter2++;
//	    			     HCLCD_u8_GoTo_XY(1,4);
//
//
//	    			   }
//	    			   else
//	    			   {
//	    				   _delay_ms(1000);
//	    				   HCLCD_voidClear();
//	    				   HCLCD_voidCursorBlinkerOff();
//	    				   HCLCD_voidWriteString(" Out of tries !");
//
//	    				   break;
//	    			   }
//
//	    		   }
//	    	   }
//
//
//	       }
//	}
//
//}
//
