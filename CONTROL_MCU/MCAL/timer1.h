/*
 ****************************************************************************************
 --	Project name:	timer1.h
 -- Author: 		M.Adel
 --	Description: 	simple driver for timer1
 ****************************************************************************************
 */
#ifndef TIMER1_H_
#define TIMER1_H_

#include "other_Headers/std_types.h"
#include <avr/iom32.h>

/* Structures to initialize the timer */
typedef enum{N1=1,N8,N64,N256,N1024,EXT_T0_FALLING,EXT_T0_RISING}Timer1_Prescaler;
typedef enum{NORMAL, CTC=4}Timer1_Mode;
/* Configuration structure */
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
