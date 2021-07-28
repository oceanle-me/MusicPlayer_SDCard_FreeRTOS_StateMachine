/*
 * SW_StateMachine.c
 *
 *  Created on: 28 thg 7, 2021
 *      Author: Dell
 */
#include "SW_StateMachine.h"

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "debug.h"
#include "utils/uartstdio.h"
#include "driverlib/pwm.h"
#include "Init.h"

static main_state mainState;
sw_state   swState;


void    InitState(void)
{
    mainState = STATE_ON;
}

void    UpdateStateMachine (void)
{
    //update states
    switch (mainState)
    {
    case    STATE_ON:
        if (swState == STATE_SW2){ //sw2 has more priority
            mainState = STATE_WAIT;
            DBG("on -> wait \n");
        }
        else if (swState == STATE_SW1) {
            mainState =  STATE_OFF;
            DBG("on -> off \n");
        }
        break;
    case    STATE_OFF:
        if (swState == STATE_SW2){ //sw2 has more priority
            mainState = STATE_WAIT;
            DBG("off -> wait \n");
        }
        else if (swState == STATE_SW1) {
            mainState =  STATE_ON;
            DBG("off -> on \n");
        }
        break;
    case    STATE_WAIT:
        if  (swState == STATE_SW2){
            mainState = STATE_PREVIOUS;
            DBG("wait -> previous \n");
        }
        else if (timeOutTimer0 == true){//timer overflows
            mainState = STATE_NEXT;
            DBG("wait -> next \n");
        }
        break;
    case    STATE_NEXT:
        mainState = STATE_ON;
        DBG("next -> on \n");
        break;
    case    STATE_PREVIOUS:
        mainState = STATE_ON;
        DBG("previous -> on \n");
        break;
    default:     break;
    }

    //state machine control

    swState = STATE_NO; //delete state of sw
    DBG("control - sw stateNO \n");
    switch (mainState)
    {
    case    STATE_ON:
        PWMGenEnable(PWM0_BASE, PWM_GEN_0);
        DBG("control - on \n");
        break;
    case    STATE_OFF:
        PWMGenDisable(PWM0_BASE, PWM_GEN_0);
        DBG("control - off \n");
        break;
    case    STATE_WAIT:
        PWMGenDisable(PWM0_BASE, PWM_GEN_0);
        DBG("control - wait \n");
        //timer overflow after 1s
        Init_Timer0();
        break;
    case    STATE_NEXT:
        DBG("control - next \n");
        PWMGenEnable(PWM0_BASE, PWM_GEN_0);
//        mainState == STATE_ON;  //this is a special state
        break;
    case    STATE_PREVIOUS:
        numOrderOfSong-=2;
        DBG("control - pre \n");
        PWMGenEnable(PWM0_BASE, PWM_GEN_0);
//        mainState == STATE_ON;  //this is a special state
        break;
    default:
        break;
    }
}

bool GetState_ChangeSong(void){
    if( (mainState == STATE_NEXT) || (mainState == STATE_PREVIOUS) ){
        return true;
    }
    else return false;
}

void Update_StateOn(void){
    mainState = STATE_ON;
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}

void Update_StateOff(void){
    PWMGenDisable(PWM0_BASE, PWM_GEN_0);
    mainState = STATE_OFF;
}
