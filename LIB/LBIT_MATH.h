/************************************************************************/
/**************** Name    : Mohamed Ahmed Abdelhamid ********************/
/**************** Date    :       28/05/2022         ********************/
/**************** SWC     :      LBIT_MATH           ********************/
/**************** Version :         1.0              ********************/
/************************************************************************/

#ifndef LBIT_MATH_H
#define LBIT_MATH_H

#define SET_BIT(REG,BITNO)  (REG|=(1<<BITNO))
#define CLR_BIT(REG,BITNO)  (REG&=~(1<<BITNO))
#define TOG_BIT(REG,BITNO)  (REG^=(1<<BITNO))
#define GET_BIT(REG,BITNO)  ((REG>>BITNO)&1)

#endif
