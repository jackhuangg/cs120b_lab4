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

enum SM1_STATES { SM1_SMStart, check, plus, waitplus, minus, init, reset, waitminus, waitreset} SM1_STATE;
void Tick_StateMachine1() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         SM1_STATE = init;
         break;
      case check:
         if((PINA&0x03)==0x03){
	    SM1_STATE = reset;
	 }
         else if ((PINA&0x01)==0x01) {
            SM1_STATE = plus;
         }
         else if ((PINA&0x02)==0x02) {
            SM1_STATE = minus;
         }
         //else if ((PINA&0x03) == 0x03) {
         //   SM1_STATE = reset;
         //}
         else {
            SM1_STATE = check;
         }
         break;
      case plus:
         SM1_STATE = waitplus;
         break;
      case waitplus:
         //if ((PINA&0x03) == 0x03) {
         //   SM1_STATE = reset;
         //}
         if ((PINA&0x01)==0x01) {
            SM1_STATE = waitplus;
         }
         else{
	    SM1_STATE = check;
	 }
         break;
      case minus:
         if (1) {
            SM1_STATE = waitminus;
         }
         break;
      case init:
         if (1) {
            SM1_STATE = check;
         }
         break;
      case reset:
         if ((PINA&0x03)==0x03) {
            SM1_STATE = reset;
         }
         else {
            SM1_STATE = check;
         }
         break;
      case waitminus:
         if ((PINA&0x03) == 0x03) {
            SM1_STATE = reset;
         }
         else if ((PINA&0x02)==0x02) {
            SM1_STATE = waitminus;
         }
         else {
            SM1_STATE = check;
         }
         break;
      case waitreset:
         if ((PINA&0x03) == 0x03){
            SM1_STATE = waitreset;
         }
         else {
            SM1_STATE = check;
         }
         break;
      default:
         SM1_STATE = SM1_SMStart;
         break;
   }
   switch(SM1_STATE) { 
      case SM1_SMStart: 
         PORTC=7;    
         break;
      case check:
         break;
      case plus:
         if(PORTC<9){
	     PORTC=PORTC+1;
 	 }
         break;
      case waitplus:        
         break;
      case minus:
         if(PORTC>0){	     
	     PORTC=PORTC-1;
	 }
         break;
      case init:
         PORTC=7;
         break;
      case reset:
         PORTC=0;
         break;
      case waitminus:
         break;
      case waitreset:
         break;
      default:
	 PORTC=7;
         break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    DDRC = 0xFF;
    PORTA = 0xFF;
    PORTC = 0x00;
	
    /* Insert your solution below */
   while(1){
	Tick_StateMachine1();
   }
    return 1;
}
