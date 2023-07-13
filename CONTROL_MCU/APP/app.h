/*
 ****************************************************************************************
 --	Project name:	app.h
 -- Author: 		M.Adel
 --	Description: 	Function APIs for control MCU app layer
 ****************************************************************************************
 */
#ifndef APP_H_
#define APP_H_

void Timer1_inc(void);
void wait(uint8 time);
void open_Door(void);
void close_Door(void);
uint8 check_pw(uint8* p1, uint8* p2);
void Save_Password(const uint8* password);
void Read_Password(uint8* password);
void input_password(uint8 * password);
void wrong_pass(void);

#endif /* APP_H_ */
