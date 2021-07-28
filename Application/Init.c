/*
 * Init.c
 *
 *  Created on: 28 thg 7, 2021
 *      Author: Dell
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "Init.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/tm4c123gh6pm.h"
#include "debug.h"
#include "driverlib/udma.h"
#include "driverlib/timer.h"
#include "driverlib/ssi.h"
#include "driverlib/pwm.h"


void InitGPIO(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    //unlock GPIO F0
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; ////#include "inc/hw_gpio.h"
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4 );

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);

    IntPrioritySet(INT_GPIOF, 5<<5); //highest priority in FreeRTOS
//    IntPrioritySet(INT_GPIOF, 0);
    IntRegister(INT_GPIOF, GPIOIntHandler);
    IntEnable(INT_GPIOF);
    IntMasterEnable();
}

void   InitPWM(void)
{
//      System clock with PLL is 200MHz/3; SYSCTL_SYSDIV_3
//      with SYSCTL_PWMDIV_16, we have PWM Clock is 200MHz/3/16, thus a period is 0.24us.
//      With 8-bit resolution, the max value 2^8 is about 260.
//      So, 1/ (260*0.24us) = 16KHz = sample rate of our music player
//      After the above calculation, we reached a solution for Tiva C launch pad to play audio 8bit - 16Khz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);//
    //
    // The PWM peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    //
    // Configure PWM0 to count down without synchronization.
    //
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

//  Sample rate is 16Khz
    DBG("Clock PWM= %d \n",(SysCtlClockGet()/16 / 16000));
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, (SysCtlClockGet()/16 / 16000));
    //16KHz equivalents  260 steps, 1/16KHz = 260*0.24s
    //

    //
    //200 steps
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1);


    IntMasterEnable();
    PWMIntEnable(PWM0_BASE, PWM_INT_GEN_0);

    //
    // Enable the PWM0 LOAD interrupt on PWM Gen 0.
    //
    PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_LOAD);

    //
    // Enable the interrupt for PWM Gen 0 on the processor (NVIC).
    //
    IntEnable(INT_PWM0_0);

    //
    // Enable the PWM Out Bit 0 (PB6) output signal.
    //
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    PWMGenIntRegister(PWM0_BASE, PWM_GEN_0, PWM0Gen0IntHandler);
    IntPrioritySet(INT_PWM0_0, 6<<5);

}

void Init_Timer0(void){
        timeOutTimer0 = false;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
        TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
        TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()-2);  // set value overflow 1s
        TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0A_Int);
        IntEnable(INT_TIMER0A);
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        IntPrioritySet(INT_TIMER0A, 6<<5);
        TimerEnable(TIMER0_BASE, TIMER_A);
}

void    InitDebug(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, SysCtlClockGet());
    DBG("Debug using UARTprintf\n");
}
