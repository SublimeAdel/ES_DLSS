/*
 ****************************************************************************************
 --	Project name:	HMI_ECU.c
 -- Author: 		M.Adel
 --	Description: 	please note that proteus sometimes bugs on frequency 8 MHz if so please try  using 1 MHz instead
 ****************************************************************************************
 */
#include <avr/io.h>
#include "HAL.h"
#include "MCAL.h"
#include <util/delay.h>
#include "app.h"

#define MAX_WRONG_ENTRIES 3
#define TIMER_COMPARE_VALUE 31250

uint8 g_PW_flag = 0;
volatile uint8 g_sec = 0;

void Timer1_inc(void)
{
	g_sec++;
}

void wait(uint8 time)
{
	g_sec = 0;
	while(g_sec<time)
	{
		/* wait */
	}
}


int main(void) 
{
	/********** Initialization Code **********/
	uint8 key, false_count=0,check_flag=0;
	SREG |= (1<<7);	/* enable interrupts */
	/******* LCD *************/
	LCD_init();
	/********* UART ***********/
	UART_ConfigType UART_Config = {EIGHT, DISABLED, ONE_STOP_BIT,9600};
	UART_init(&UART_Config);
	/********* TIMER **********/
	Timer1_ConfigType Timer1_Config = {0,TIMER_COMPARE_VALUE,N256,CTC};
	Timer1_init(&Timer1_Config);
	Timer1_setCallBack(Timer1_inc);
	while(1)
	{
		/********** Application Code **********/
		if (g_PW_flag == 0)	/* password is not set */
		{
			enter_Password();
			g_PW_flag = check_Password();	/* check if passwords are matching */
		}
		else if (g_PW_flag == 1)	/* if Password is set */
		{
			/* display menu 2 */
			LCD_moveCursor(0, 0);
			LCD_displayString("+ : open door  ");
			LCD_moveCursor(1, 0);
			LCD_displayString("- : reset pass  ");
			/*********************/
			key = KEYPAD_getPressedKey();	/* input key */
			_delay_ms(300); /* Press time */
			switch (key)
			{
				case '+':	/* Open door */
					check_flag=0;
					while(check_flag == 0)
					{
						UART_sendByte(key);	/* send  '+' to MCU2 */
						enter_Password();	/* Enter Pass */
						check_flag= check_Password();
						if (check_flag == 1)	/* if password is correct */
						{
							HMI_open_door();
						}
						else
						{
							false_count++;
							UART_sendByte(false_count);	/* send wrong entry count to MCU2 */
							if (false_count == MAX_WRONG_ENTRIES)
							{
								wrong_pass();	/* timeout */
								break;	/* break from inner while */
							}
						}
					}
					break;	/* end case '+': */
				case '-':
					UART_sendByte(key);	/* send - to mcu2 */
					g_PW_flag = 0;	/* PW is not set */
					break;
			}	/* end switch */
		}

	}	/* end while */
    return 0;
}

void enter_Password(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString(" Enter Password: ");
	LCD_moveCursor(1, 0);
	send_Password();
	if(!g_PW_flag) /*PASSWORD IS NOT SET*/
	{
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString(" Re-Enter Pass: ");
	LCD_moveCursor(1, 0);
	send_Password();
	}
}

void send_Password(void)
{
	uint8 key = 0;
	while (1)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(300); /* Press time */
		if (key == '=')	 /* Enter is pressed */
		{
			UART_sendByte(key);
			break;	/* break out of the loop */
		}
		else if((key <= 9) && (key >= 0))	/* an integer is input */
		{
			LCD_displayCharacter('*');   /* display an asterisk */
			UART_sendByte(key);
		}
	}	/* end while */

}

uint8 check_Password(void)	 /* check password from MCU2 */
{
	uint8 byte=0;
	byte = UART_recieveByte();
	return byte;
}

void wrong_pass(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("WRONG PASSWORD!");
	UART_sendByte(MAX_WRONG_ENTRIES);
	wait(60);
}

void HMI_open_door(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	while(UART_recieveByte()!=0){}	/* wait for signal from control ecu */
	LCD_displayString("UNLOCKING DOOR");
	wait(15);
	LCD_clearScreen();
	wait(3);
	LCD_clearScreen();
	LCD_displayString(" LOCKING DOOR ");
	wait(15);
	LCD_clearScreen();
}
