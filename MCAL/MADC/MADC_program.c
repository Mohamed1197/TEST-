/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       01/06/2022         ********************/
/**************** SWC     :         MADC             ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/

/*******************************************************************************************************/
/*                                       Include LIB Layer                                             */
/*******************************************************************************************************/
#include "../../LIB/LBIT_MATH.h"
#include "../../LIB/LSTD_TYPES.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                    Include ADC Header Files                                         */
/*******************************************************************************************************/
#include "MADC_config.h"
#include "MADC_interface.h"
#include "MADC_private.h"
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                 Global Pointer To Function                                          */
/*******************************************************************************************************/
static void (*ADC_pfNotification)(u16) = NULL;
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                      Global Variables                                               */
/*******************************************************************************************************/
static u8 ADC_u8BusyFlag =0;
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                                    ADC Initialization Function                                      */
/*******************************************************************************************************/
void MADC_voidInit(void)
{


	/*  Select Vref  */
#if(ADC_VREF == AREF)
	{
	   CLR_BIT(ADC_u8_ADMUX_REG,7);
	   CLR_BIT(ADC_u8_ADMUX_REG,6);
	}
#elif(ADC_VREF == AVCC)
	{
	    CLR_BIT(ADC_u8_ADMUX_REG,7);
	    SET_BIT(ADC_u8_ADMUX_REG,6);
	}
#elif(ADC_VREF == INTERNAL)
	{
		SET_BIT(ADC_u8_ADMUX_REG,7);
	    SET_BIT(ADC_u8_ADMUX_REG,6);
	}
#endif

	/* ADC Adjust Result */
#if(ADJUST_RESULT == RIGHT_ADJUST)
	{
		CLR_BIT(ADC_u8_ADMUX_REG,5);
	}
#elif(ADJUST_RESULT == LEFT_ADJUST)
	{
		SET_BIT(ADC_u8_ADMUX_REG,5);
	}
#endif

	/* ADC AutoTrigger */
#if(ADC_AUTO_TRIG_MODE == ADC_AUTO_TRIG_ENABLE)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,5);
	}
#elif(ADC_AUTO_TRIG_MODE == ADC_AUTO_TRIG_DISABLE)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,5);
	}
#endif

	/* ADC Prescaler CLOCK */
#if(ADC_CLOCK == CLOCK_2)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,2);
		CLR_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_4)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    CLR_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_8)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_16)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		CLR_BIT(ADC_u8_ADCSRA_REG,1);
	    CLR_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_32)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		CLR_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_64)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    CLR_BIT(ADC_u8_ADCSRA_REG,0);
	}
#elif(ADC_CLOCK == CLOCK_128)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,2);
		SET_BIT(ADC_u8_ADCSRA_REG,1);
	    SET_BIT(ADC_u8_ADCSRA_REG,0);
	}
#endif

	/* ADC Enable Peripheral */
#if(ADC_MODE == ADC_ENABLE)
	{
		SET_BIT(ADC_u8_ADCSRA_REG,7);
	}
#elif(ADC_MODE == ADC_DISABLE)
	{
		CLR_BIT(ADC_u8_ADCSRA_REG,7);
	}
#endif
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                 ADC Get Digital Value Synchronous NonBlocking Function                              */
/*******************************************************************************************************/
u8 MADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelNb,u16* Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u8TimeOutCounter = 0;
	if((Copy_u8ChannelNb < 32) && (Copy_pu16DigitalValue != NULL))
	{
		/* Clear MUX 4..0 Bits */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		/* Wait Till Flag = 1 */
		while((GET_BIT(ADC_u8_ADCSRA_REG,4)==0) && (Local_u8TimeOutCounter < ADC_u8_TIME_OUT_MAX_VALUE))
		{
			Local_u8TimeOutCounter ++;
		}
		//while(!GET_BIT(ADC_u8_ADCSRA_REG,4));
		if(Local_u8TimeOutCounter >= ADC_u8_TIME_OUT_MAX_VALUE)
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
		else
		{
			/* Read Digital Value */
			*Copy_pu16DigitalValue = ADC_u16_ADC_REG;
			/* Clear Flag */
			SET_BIT(ADC_u8_ADCSRA_REG,4);
		}

	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                           ADC Get Digital Value ASynchronous Function                               */
/*******************************************************************************************************/
u8 MADC_u8GetDigitalValueAsync(u8 Copy_u8ChannelNb,void(*Copy_PfNotification)(u16))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_u8ChannelNb < 32) && (*Copy_PfNotification != NULL) && (ADC_u8BusyFlag == 0) )
	{
		/* ADC is Busy */
		ADC_u8BusyFlag = 1;
		/* Updating Global Pointer to a Function With the Notification Function */
		ADC_pfNotification = Copy_PfNotification;
		/* Enable Interrupt PIE */
		SET_BIT(ADC_u8_ADCSRA_REG,3);
		/* Clear MUX 4..0 Bits */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                Read ADC Register Function                                           */
/*******************************************************************************************************/

u8 MADC_u8ReadADCRegister(u16 * Copy_pu16ADCRegValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pu16ADCRegValue !=NULL)
	{
	    *Copy_pu16ADCRegValue = ADC_u16_ADC_REG;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*#####################################################################################################*/



/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*******************************************************************************************************/
/*                                 Prototype for ADC ISR Function                                      */
/*******************************************************************************************************/

void __vector_16(void)   __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotification != NULL)
	{
		/* Clear PIE */
		CLR_BIT(ADC_u8_ADCSRA_REG,3);
		/* Calling Notification Function */
		ADC_pfNotification(ADC_u16_ADC_REG);
		/* Clear Busy Flag */
		ADC_u8BusyFlag =0;
	}
}
/*#####################################################################################################*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
