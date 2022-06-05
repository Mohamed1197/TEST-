

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../LIB/LSTD_TYPES.h"
#include "../LIB/LBIT_MATH.h"



/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/

#include"../MCAL/MDIO/MDIO_Interface.h"         //for DIO
#include"../MCAL/MEXTI/MEXTI_interface.h"       //for EXTI
#include "../MCAL/MADC/MADC_interface.h"        //for ADC
#include "../MCAL/MTimers/MTMR_interface.h"     //for TMR


/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/

#include"../HAL/HLCD/HLCD_interface.h"         //for LCD
#include"../HAL/HLED/HLED_Interface.h"         //for LED
#include"../HAL/HKPD/HKPD_interface.h"         //for KPD
#include"../HAL/HSTP/HSTP_interface.h"         //for STEPPER
#include"../HAL/HSRV/HSERVO_Interface.h"       //for SERVO


/*******************************************************************************************************/
/*                                   Service Layer  Components                                         */
/*******************************************************************************************************/

#define F_CPU  8000000UL
#include<util\delay.h>






int main(void)
{
	u8 a;
	u16 b;

	/* Peripherals Initialization */
	MDIO_u8Init  ();
	MADC_voidInit();
    HLCD_voidInit();


    MEXTI_u8Enable(EXTI_u8_INT0,EXTI_u8_RISING_EDGE);

    while(1)
    {

    	MADC_u8GetDigitalValueSynchNonBlocking(ADC_u8_CHANNEL_0,&b);
    	HLCD_voidWriteChar('a');

    	_delay_ms(1000);
        HLCD_voidClear();
    	_delay_ms(1000);

    	HLED_VoidLed_Toggle(LED_PORTA,LED_PIN6);

    	HKEYPAD_u8GetPressedKey(&a);




    }


	return 0;
}


