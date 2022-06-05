/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       04/06/2022         ********************/
/**************** SWC     :         MTMR             ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/
#ifndef MTMR_INTERFACE_H
#define MTMR_INTERFACE_H

/*******************************************************************************************************/
/*                                 Prototypes of the Timer driver                                      */
/*******************************************************************************************************/
void MTMR_voidTimer0Init(void);

u8   MTMR_u8Timer0OVFSetCallBack(void(*Copy_pf)(void));

u8   MTMR_u8Timer0CTCSetCallBack(void(*Copy_pf)(void));

void MTMR_voidTimer0SetCompareMatchValue(u8 Copy_u8OCRValue);

u8   MTMR_u8Timer0GetCounterValue(u16 * Copy_pu16CounterValue);

u8   MTMR_u8Timer0GeneratePWM(u8  Copy_u8DutyCycle);

void MTMR_voidTimer1Init(void);

void MTMR_voidTimer1SetCompareMatchValueChannelA(u16 Copy_u16CompareMatchValue);

u8   MTMR_u8Timer1GetCounterValue(u16 * Copy_pu16CounterValue);

u8   MTMR_u8Timer1OVFSetCallBack(void (*Copy_pf)(void));

u8   MTMR_u8Timer1CTCSetCallBack(void (*Copy_pf)(void));

u8   MTMR_u8Timer1GeneratePWM(u8  Copy_u8DutyCycle);

void MTMR_voidTimer1CTCCounter(u16 Copy_u16CTCCounter);

void MTMR_voidHWICUEnable(void);

void MTMR_voidHWICUDisable(void);

u8   MTMR_u8GetPWMTotalPeriod(u32 * Copy_pu32TotalPeriod);

u8   MTMR_u8GetPWMDutyCycle(u8 * Copy_pu8DutyCycle);

u8   MTMR_u8GetPWMOnPeriod(u16 * Copy_pu16OnPeriod);
/*#####################################################################################################*/

#endif
