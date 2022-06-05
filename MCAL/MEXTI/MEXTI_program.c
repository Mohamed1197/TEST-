/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       31/05/2022         ********************/
/**************** SWC     :         MEXTI            ********************/
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
/*                                   Include EXTI Header Files                                         */
/*******************************************************************************************************/
#include "MEXTI_config.h"
#include "MEXTI_interface.h"
#include "MEXTI_private.h"
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                               Array of Global Pointers to Function                                  */
/*******************************************************************************************************/
static void (*EXTI_ApfEXTI[3])(void) = {NULL,NULL,NULL};
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                            EXTERNAL INTERRUPT set callBack Function                                 */
/*******************************************************************************************************/

u8 MEXTI_u8SetCallBack(void(*Copy_pf)(void),u8 Copy_u8CallBackIndex)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if((Copy_u8CallBackIndex <= EXTI_u8_INT2) && (Copy_pf != NULL ))
	{
		EXTI_ApfEXTI[Copy_u8CallBackIndex] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                             EXTERNAL INTERRUPT Enable Function                                      */
/*******************************************************************************************************/
u8 MEXTI_u8Enable (u8 Copy_u8_EXTIIndex , u8 Copy_u8EXTIEdge)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch (Copy_u8_EXTIIndex)
	{
	    case EXTI_u8_INT0:
	    	switch(Copy_u8EXTIEdge)
	    	{
	    	    case EXTI_u8_FALLING_EDGE:
	    	    	SET_BIT(EXTI_u8_MCUCR,1);
	    	    	CLR_BIT(EXTI_u8_MCUCR,0);
	    		break;
	    	    case EXTI_u8_RISING_EDGE:
	    	    	SET_BIT(EXTI_u8_MCUCR,1);
	    	    	SET_BIT(EXTI_u8_MCUCR,0);
	    		break;
	    	    case EXTI_u8_LOW_LEVEL:
	    	    	CLR_BIT(EXTI_u8_MCUCR,1);
	    	    	CLR_BIT(EXTI_u8_MCUCR,0);
	    		break;
	    	    case EXTI_u8_ANY_LOGICAL_CHANGE:
	    	    	SET_BIT(EXTI_u8_MCUCR,0);
	    	    	CLR_BIT(EXTI_u8_MCUCR,1);
	    		break;
	    	    default:  Local_u8ErrorState = STD_TYPES_NOK;
	    	}
	    	/* Enable PIE */
	    	SET_BIT(EXTI_u8_GICR,6);
		break;
		    case EXTI_u8_INT1:
		    	switch(Copy_u8EXTIEdge)
		    	{
		    	    case EXTI_u8_FALLING_EDGE:
		    	    	SET_BIT(EXTI_u8_MCUCR,3);
		    	    	CLR_BIT(EXTI_u8_MCUCR,2);
		    		break;
		    	    case EXTI_u8_RISING_EDGE:
		    	    	SET_BIT(EXTI_u8_MCUCR,3);
		    	    	SET_BIT(EXTI_u8_MCUCR,2);
		    		break;
		    	    case EXTI_u8_LOW_LEVEL:
		    	    	CLR_BIT(EXTI_u8_MCUCR,2);
		    	    	CLR_BIT(EXTI_u8_MCUCR,3);
		    		break;
		    	    case EXTI_u8_ANY_LOGICAL_CHANGE:
		    	    	SET_BIT(EXTI_u8_MCUCR,2);
		    	    	CLR_BIT(EXTI_u8_MCUCR,3);
		    		break;
		    	    default:  Local_u8ErrorState = STD_TYPES_NOK;
		    	}
		    	/* Enable PIE */
		    	SET_BIT(EXTI_u8_GICR,7);
			break;
			    case EXTI_u8_INT2:
			    	switch(Copy_u8EXTIEdge)
			    	{
			    	    case EXTI_u8_FALLING_EDGE:
                             CLR_BIT(EXTI_u8_MCUCSR,6);
			    		break;
			    	    case EXTI_u8_RISING_EDGE:
                             SET_BIT(EXTI_u8_MCUCSR,6);
			    		break;
			    	    default:  Local_u8ErrorState = STD_TYPES_NOK;
			    	}
			    	/* Enable PIE */
			    	SET_BIT(EXTI_u8_GICR,5);
				break;
			    	default: Local_u8ErrorState = STD_TYPES_NOK;

	}

	return Local_u8ErrorState;
}
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                             EXTERNAL INTERRUPT Enable Function                                      */
/*******************************************************************************************************/
u8 MEXTI_u8Disable(u8 Copy_u8_EXTIIndex)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8_EXTIIndex)
	{
	case EXTI_u8_INT0: CLR_BIT(EXTI_u8_GICR,6);break;
	case EXTI_u8_INT1: CLR_BIT(EXTI_u8_GICR,7);break;
	case EXTI_u8_INT2: CLR_BIT(EXTI_u8_GICR,5);break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;

}
/*#####################################################################################################*/




/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*******************************************************************************************************/
/*                       Prototype for External Interrupt ISR Functions                                */
/*******************************************************************************************************/
/*                                         EXTI0 ISR                                                   */
/*******************************************************************************************************/
void __vector_1(void)     __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INT0] != NULL)
	{
	EXTI_ApfEXTI[EXTI_u8_INT0]();
	}
}
/*******************************************************************************************************/
/*                                          EXTI1 ISR                                                  */
/*******************************************************************************************************/
void __vector_2(void)     __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INT1] != NULL)
	{
	EXTI_ApfEXTI[EXTI_u8_INT1]();
	}
}
/*******************************************************************************************************/
/*                                            EXTI2 ISR                                                */
/*******************************************************************************************************/
void __vector_3(void)     __attribute__((signal));
void __vector_3(void)
{
	if(EXTI_ApfEXTI[EXTI_u8_INT2] != NULL)
	{
	EXTI_ApfEXTI[EXTI_u8_INT2]();
	}
}
/*#####################################################################################################*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
