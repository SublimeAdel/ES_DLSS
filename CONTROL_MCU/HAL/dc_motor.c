/*
 ****************************************************************************************
 --	Project name:	dc_motor.c
 -- Author: 		M.Adel
 --	Description: 	dc motor driver
 ****************************************************************************************
 */

/********** Inclusions ************/
#include "dc_motor.h"



/* Description:
 * ➢ The Function responsible for setup the direction for the two
 * motor pins through the GPIO driver.
 * ➢ Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void)
{
	/* EN  -> PB3
	 * IN1 -> PD6
	 * IN2 -> PD7 */

	/* setup pin directions */
	GPIO_setupPinDirection(DC_MOTOR_EN_PORT,DC_MOTOR_EN_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT,DC_MOTOR_IN1_PIN , PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT,DC_MOTOR_IN2_PIN , PIN_OUTPUT);
	/* stop DC Motor at the beginning */
	GPIO_writePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
}



/*	Description:
 * ➢ The function responsible for rotate the DC Motor CW/ or A-CW or
 * stop the motor based on the state input state value.
 * ➢ Send the required duty cycle to the PWM driver based on the required
 * speed value.
 */
void DcMotor_rotate(DcMotor_State state, uint8 speed)
{
	switch (state) {
		case STOP:	/* Stop the motor */
			GPIO_writePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
			break;
		case CW:	/* Rotate Clockwise */
			GPIO_writePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_HIGH);
			break;
		case ACW:	/* Rotate Anti-clockwise */
			GPIO_writePin(DC_MOTOR_IN1_PORT, DC_MOTOR_IN1_PIN, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_IN2_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
			break;
	}
	PWM_Timer0_Start(speed);	/* start PWM*/
}
