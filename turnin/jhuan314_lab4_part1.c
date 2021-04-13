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
//void TimerISR() {
//   TimerFlag = 1;
//}

enum SM1_STATES { SM1_SMStart, SM1_s0, SM1_s1, SM1_s2, SM1_s4} SM1_STATE;
void Tick_LoHi() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         if (1) {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s0:
         if (!PINA&&0x01) {
            SM1_STATE = SM1_s4;
         }
         else if (PINA&&0x01) {
            SM1_STATE = SM1_s0;
         }
         else {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s1:
         if (!PINA&&0x01) {
            SM1_STATE = SM1_s2;
         }
         else if (PINA&&0x01) {
            SM1_STATE = SM1_s1;
         }
         else {
            SM1_STATE = SM1_s1;
         }
         break;
      case SM1_s2:
         if (PINA&&0x01) {
            SM1_STATE = SM1_s0;
         }
         else {
            SM1_STATE = SM1_s2;
         }
         break;
      case SM1_s4:
         if (PINA&&0x01) {
            SM1_STATE = SM1_s1;
         }
         else {
            SM1_STATE = SM1_s4;
         }
         break;
      default:
         SM1_STATE = SM1_s0;
         break;
   }
   switch(SM1_STATE) { 
      case SM1_SMStart:
         
         break;
      case SM1_s0:
         PORTB = 1;
         break;
      case SM1_s1:
         PORTB = 2;
         break;
      case SM1_s2:
         
         break;
      case SM1_s4:
         
         break;
   }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    DDRB = 0xFF;
    PORTA = 0xFF;
    PORTB = 0x00;
    /* Insert your solution below */
   int LoHiElapsedTime = 1000;
   int periodGCD = 1000;
   //TimerSet(periodGCD);
   //TimerOn();
   while(1){
      if (LoHiElapsedTime >= 1000){
         Tick_LoHi();
         LoHiElapsedTime = 0;
      }
      LoHiElapsedTime += 1000;
      while(!TimerFlag);
      TimerFlag=0;
   }
    return 1;
}
