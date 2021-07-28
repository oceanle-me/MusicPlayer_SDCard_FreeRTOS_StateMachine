/*
 * SW_StateMachine.h
 *
 *  Created on: 28 thg 7, 2021
 *      Author: Dell
 */

#ifndef APPLICATION_SW_STATEMACHINE_H_
#define APPLICATION_SW_STATEMACHINE_H_
#include <stdbool.h>
#include <stdint.h>

typedef enum {STATE_ON,STATE_OFF,STATE_WAIT,STATE_NEXT,STATE_PREVIOUS} main_state;
typedef enum {STATE_SW1,STATE_SW2,STATE_NO} sw_state;


void    InitState(void);
void    UpdateStateMachine (void);
void    Update_StateOn(void);
void    Update_StateOff(void);

bool GetState_ChangeSong(void);

//extern main_state mainState;
extern sw_state   swState;
extern uint8_t  numOrderOfSong;


#endif /* APPLICATION_SW_STATEMACHINE_H_ */
