/*
 ****************************************************************************************
 --	Project name:	pwm.c
 -- Author: 		M.Adel
 --	Description: 	driver for the pwm driver
 ****************************************************************************************
 */

/********** Inclusions ************/
#include <avr/io.h>
#include "other_Headers/common_macros.h"
#include "pwm.h"

/* 	this function is responsible for triggering timer0 in PWM mode	*/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* PWM mode, non inverting
	 * Prescaler F_CPU/8
	 * compare value = input duty_cycle
	 * duty cycle value [ 0 : 100 ] percentage
	 * F= 500Hz */

	TCNT0 = 0;	/* set timer at 0*/
	SET_BIT(TCCR0, WGM01);		/*Fast PWM mode*/
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,CS01);	/* prescaler N = 8*/
	SET_BIT(TCCR0,COM01);	/* non-inverting mode*/
	OCR0 = (uint8)((255*duty_cycle)/100);	/* set OCR0 (duty_cycle% * 256)*/
}


