/*
 ****************************************************************************************
 --	Project name:	dc_motor.h
 -- Author: 		M.Adel
 --	Description: 	
 ****************************************************************************************
 */
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "MCAL/pwm.h"
#include "MCAL/gpio.h"
/******************** Definitions *********************/
#define DC_MOTOR_EN_PORT	PORTB_ID
#define DC_MOTOR_EN_PIN		PIN3_ID

#define DC_MOTOR_IN1_PORT	PORTD_ID
#define DC_MOTOR_IN1_PIN	PIN6_ID

#define DC_MOTOR_IN2_PORT	PORTD_ID
#define DC_MOTOR_IN2_PIN	PIN7_ID

/********************* Types *********************/
typedef enum {
	STOP, CW, ACW
}DcMotor_State;


/********************* Function Prototypes *********************/
/* Description:
 * ➢ The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * ➢ Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void);

/* Description:
 * ➢ The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * ➢ Send the required duty cycle to the PWM driver based on the required
 * speed value
 */
void DcMotor_rotate(DcMotor_State state, uint8 speed);




#endif /* DC_MOTOR_H_ */
