/*
 ****************************************************************************************
 --	Project name:	timer1.c
 -- Author: 		M.Adel
 --	Description: 	simple driver for timer1
 ****************************************************************************************
 */

/********** Inclusions ************/
#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile void(*g_Timer1_Callback_ptr)(void);

ISR(TIMER1_COMPA_vect)	/*timer interrupt every one second */
{
	(*g_Timer1_Callback_ptr)();
}

ISR(TIMER1_OVF_vect)
{
	(*g_Timer1_Callback_ptr)();
}

/* Timer1 Initializer
   takes a pointer to a configuration structure */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = Config_Ptr->initial_value;	/* set initial value */
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);	/*NOT PWM*/
	TCCR1B = (TCCR1B&(0xF8)) | (Config_Ptr->prescaler&(0x07));	/* set prescaler */
	TCCR1B |= ((Config_Ptr->mode)>>2)<<3;	/*set mode */
	TCCR1A |= ((Config_Ptr->mode)&(0x03));

	if (Config_Ptr->mode == NORMAL)
	{
		TIMSK = (1<<TOIE1);
	}
	else if (Config_Ptr->mode == CTC)
	{
		TIMSK = (1<<OCIE1A);
		OCR1A = Config_Ptr->compare_value;
	}

}


void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_Timer1_Callback_ptr = a_ptr;
}

void Timer1_deInit(void)
{
	TCCR1B &= 0b11111000;
}
