/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       01/06/2022         ********************/
/**************** SWC     :         MADC             ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/
#ifndef MACD_CONFIG_H
#define MACD_CONFIG_H

/*******************************************************************************************************/
/*                               ADC MAX TIME OUT VALUE                                                */
/*******************************************************************************************************/
#define ADC_u8_TIME_OUT_MAX_VALUE                       100000
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                          ADC Select Reference Voltage (Vref)                                        */
/*******************************************************************************************************/
#define AREF                0
#define AVCC                1
#define INTERNAL            2
#define ADC_VREF          AVCC
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                               ADC Register Adjust Mode                                              */
/*******************************************************************************************************/
#define RIGHT_ADJUST              0
#define LEFT_ADJUST               1
#define ADJUST_RESULT         RIGHT_ADJUST
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                ADC Enable Peripheral                                                */
/*******************************************************************************************************/
#define ADC_ENABLE                0
#define ADC_DISABLE               1
#define ADC_MODE               ADC_ENABLE
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                               ADC Auto Trigger Enable                                               */
/*******************************************************************************************************/
#define ADC_AUTO_TRIG_ENABLE                 0
#define ADC_AUTO_TRIG_DISABLE                1
#define ADC_AUTO_TRIG_MODE            ADC_AUTO_TRIG_DISABLE
/*#####################################################################################################*/



/*******************************************************************************************************/
/*                                    ADC Prescaler                                                    */
/*******************************************************************************************************/
#define CLOCK_2                   0
#define CLOCK_4                   1
#define CLOCK_8                   2
#define CLOCK_16                  3
#define CLOCK_32                  4
#define CLOCK_64                  5
#define CLOCK_128                 6
#define ADC_CLOCK             CLOCK_64
/*#####################################################################################################*/




#endif



