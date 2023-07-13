/*
 ****************************************************************************************
 --	Project name:	buzzer.c
 -- Author: 		M.Adel
 --	Description: 	Buzzer driver functions
 ****************************************************************************************
 */

/********** Inclusions ************/
#include "buzzer.h"


void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);		/* turn off the buzzer initially */
}
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}
