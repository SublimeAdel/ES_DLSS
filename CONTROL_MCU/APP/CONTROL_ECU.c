/*
 ****************************************************************************************
 --	Project name:	CONTROL_ECU.c
 --	Created on: 	Nov 4, 2022
 -- Author: 		Mohamed Adel

 I have developed this project following the embedded software architecture of abstraction layers MCAL/HAL/APP
 This is the main application in the application layer of the system.
 ****************************************************************************************
 */
#include <avr/io.h>
#include "MCAL.h"
#include "HAL.h"
#include <util/delay.h>
#include "app.h"

#define START_ADDRESS 0x0311
#define MAX_WRONG_ENTRIES 3		/* Maximum number of wrong Entries before the Alarm goes off*/
#define PASSWORD_SIZE 5			/* Size of the password in characters */
#define TIMER_COMPARE_VALUE 31250

uint8 g_PW_flag = 0;	/* Global Password flag = 1 if password is set and saved */
volatile uint8 g_sec = 0;

void Timer1_inc(void)	/* increment the timer */
{
	g_sec++;
}

void wait(uint8 time)	/* a Function to perform busy-wait operation */
{
	g_sec = 0;			/* reset the global seconds counter */
	while(g_sec<time)
	{
		/* wait */
	}
}


int main(void)
{
	/********** Initialization Code **********/
	uint8 password1[PASSWORD_SIZE +1];	/* Initialize two arrays wherein we will save the passwords*/
	uint8 password2[PASSWORD_SIZE +1];
	uint8 key=0,PW_flag2=0;					/* key: key recieved from HMI. PW_flag2: local password flag */
	SREG |= (1<<7);	/* enable interrupts */
	/********* UART ***********/
	UART_ConfigType UART_Config = {EIGHT, DISABLED, ONE_STOP_BIT,9600};
	UART_init(&UART_Config);
	/******** DC_Motor *******/
	DcMotor_init();
	/******** BUZZER *********/
	Buzzer_init();
	/******** Timer1 ********/
	Timer1_ConfigType Timer1_Config = {0,TIMER_COMPARE_VALUE,N256,CTC};
	Timer1_init(&Timer1_Config);
	Timer1_setCallBack(Timer1_inc);
	while(1)
	{
		/********** Application Code **********/
		if (g_PW_flag == 0)	/* A- if password is not set */
		{
			input_password(password1);	/* input password form user */
			input_password(password2);	/* input password again */
			g_PW_flag = check_pw(password1, password2);	/* compares passwords */
			if (g_PW_flag)	/* if matched */
			{
				Save_Password(password1);	/* save password into EEPROM*/
			}
		}
		else if (g_PW_flag)	/* B- if Password is set */
		{
			key = UART_recieveByte();		/* Recieve the key from the Human interface MCU */
			switch (key)	
			{
				/* 
				Case +: Open the door
				Case -: Change Password
				*/
				case '+':	/* +: open the door */
					PW_flag2 = 0;	/* RESET the local flag */
					input_password(password1);	/* input a password from user	*/
					Read_Password(password2);	/* read the original password from the external EEPROM */
					PW_flag2 = check_pw(password1, password2);	/* compare both Passwords */
					UART_sendByte(PW_flag2);	/* return result to HMI */
					if (PW_flag2)	/* if matched */
					{
						open_Door();
					}
					else if(UART_recieveByte()==MAX_WRONG_ENTRIES)	/* if reached MAX number of wrong entries */
					{
						/* ALERT */
						Buzzer_on();
						wait(60);
						Buzzer_off();
					}
					break;

				case '-':	/* -: change password */
					g_PW_flag = 0;	/* password is no longer set */
					break;
			}

		}


	}
    return 0;
}


uint8 check_pw(uint8* p1, uint8* p2)
{
	/* 
		A function to compare two passwords 
		returns 0 if not matching
		returns 1 if matching
	*/
	uint8 i = 0;
	for (i = 0; i < PASSWORD_SIZE; i++)
	{
		if (p1[i] != p2[i])		/* if charracters are not matching */
		{
			UART_sendByte(FALSE);	/* send FALSE to HMI */
			return 0;				/* return 0 : passwords are not matching */
		}
	}
	/* Oherwise, if passwords are matching */
	UART_sendByte(TRUE);			/* Send TRUE to HMI */
	return 1;						/* return 1: Passwords are matching*/
}

void Save_Password(const uint8* password)
{
	/* A function to save password into the external EEPROM */
	uint8 i;
	for (i = 0; i < PASSWORD_SIZE; i++)
	{
		EEPROM_writeByte(START_ADDRESS+i, password[i]); /* Write the value in the external EEPROM */
		_delay_us(10);
	}
}

void Read_Password(uint8* password)
{
	/* A function to read the password from the external EEPROM */
	uint8 i;
	for (i = 0; i < PASSWORD_SIZE; i++)
	{
		EEPROM_readByte(START_ADDRESS+i, &password[i]); /* Write the value in the external EEPROM */
		_delay_us(10);
	}
}

void input_password(uint8 * password)
{
	/* A function to  take an input password from the user */
	uint8 i = 0;
	while(i<=PASSWORD_SIZE +1)
	{
		password[i]= UART_recieveByte();
		if (password[i]=='=')
		{
			break;
		}
		_delay_us(1);
		i++;
	}
}


void open_Door(void)
{
	/* a function to control the DC Motor to open the door*/
	/* synchronize both ECUs */
	UART_sendByte(0);
	DcMotor_rotate(CW, 100);
	wait(15);
	DcMotor_rotate(STOP, 0);
	wait(3);
	DcMotor_rotate(ACW, 100);
	wait(15);
	DcMotor_rotate(STOP, 0);
}

