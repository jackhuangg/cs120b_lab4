/*	Author: jhuan314
 *  Partner(s) Name:Jack Huang 
 *	Lab Section:23
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile int TimerFlag = 0;

enum SM1_STATES { SM1_SMStart, SM1_s0, SM1_s1, SM1_s2, SM1_s3, SM1_s5, SM1_s4, SM1_s6, SM1_s7} SM1_STATE;
void Tick_StateMachine1() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         if (1) {
            SM1_STATE = SM1_s5;
         }
         break;
      case SM1_s0:
         if (PINA&&0x01) {
            SM1_STATE = SM1_s1;
         }
         else if ((PINA&&0x02)) {
            SM1_STATE = SM1_s3;
         }
         else if ((PINA&&0x01) && (PINA&&0x02)) {
            SM1_STATE = SM1_s4;
         }
         else {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s1:
         if (1) {
            SM1_STATE = SM1_s2;
         }
         break;
      case SM1_s2:
         if ((PINA&&0x01) && (PINA&&0x02)) {
            SM1_STATE = SM1_s4;
         }
         else if (PINA&&0x01) {
            SM1_STATE = SM1_s2;
         }
         else if (!(PINA&&0x01)) {
            SM1_STATE = SM1_s7;
         }
         else {
            SM1_STATE = SM1_s2;
         }
         break;
      case SM1_s3:
         if (1) {
            SM1_STATE = SM1_s6;
         }
         break;
      case SM1_s5:
         if (1) {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s4:
         if (!((PINA&&0x01) && (PINA&&0x02))) {
            SM1_STATE = SM1_s0;
         }
         else if ((PINA&&0x01) && (PINA&&0x02)) {
            SM1_STATE = SM1_s4;
         }
         else {
            SM1_STATE = SM1_s4;
         }
         break;
      case SM1_s6:
         if (!(PINA&&0x02)) {
            SM1_STATE = SM1_s7;
         }
         else if ((PINA&&0x02)) {
            SM1_STATE = SM1_s6;
         }
         else if ((PINA&&0x01) && (PINA&&0x02)) {
            SM1_STATE = SM1_s4;
         }
         else {
            SM1_STATE = SM1_s6;
         }
         break;
      case SM1_s7:
         if ((PINA&&0x02) || (PINA&&0x01)) {
            SM1_STATE = SM1_s0;
         }
         else {
            SM1_STATE = SM1_s7;
         }
         break;
      default:
         SM1_STATE = SM1_s5;
         break;
   }
   switch(SM1_STATE) { 
      case SM1_SMStart:     
         break;
      case SM1_s0:
         break;
      case SM1_s1:
         if(PORTC<9){
	     PORTC=PORTC+1;
 	 }
         break;
      case SM1_s2:        
         break;
      case SM1_s3:
         if(PORTC>0){
	     PORTC=PORTC-1;
	 }
         break;
      case SM1_s5:
         PORTC=7;
         break;
      case SM1_s4:
         PORTC=0;
         break;
      case SM1_s6:
         break;
      case SM1_s7:
         break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x01;
    DDRC = 0xFF;
    PORTA = 0xFF;
    PORTC = 0x01;
    SM1_STATE = SM1_SMStart;
    /* Insert your solution below */
   while(1){
	Tick_StateMachine1();
   }
    return 1;
}
