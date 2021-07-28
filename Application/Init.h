/*
 * Init.h
 *
 *  Created on: 28 thg 7, 2021
 *      Author: Dell
 */

#ifndef APPLICATION_INIT_H_
#define APPLICATION_INIT_H_

void    InitGPIO(void);
void    InitPWM(void);
void    InitDebug(void);
void    Init_Timer0(void);


extern  void    PWM0Gen0IntHandler(void);
extern  void    GPIOIntHandler(void);
extern  void Timer0A_Int(void);


extern bool timeOutTimer0 ;

#endif /* APPLICATION_INIT_H_ */
