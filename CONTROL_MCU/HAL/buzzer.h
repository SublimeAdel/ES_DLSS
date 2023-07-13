/*
 ****************************************************************************************
 --	Project name:	buzzer.h
 -- Author: 		M.Adel
 --	Description: 	inclusions for the buzzer driver
 ****************************************************************************************
 */
#ifndef BUZZER_H_
#define BUZZER_H_

/*********************** buzzer ***************************/
#include "other_Headers/common_macros.h"
#include "other_Headers/std_types.h"
#include "MCAL/gpio.h"

#define BUZZER_PORT	PORTC_ID
#define BUZZER_PIN	PIN5_ID

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
