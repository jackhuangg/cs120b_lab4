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

enum SM1_STATES { SM1_SMStart, SM1_s0, SM1_s1, SM1_s2, SM1_s3} SM1_STATE;
void Tick_LoHi() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         if (1) {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s0:
         if ((PINA&0x07)==0x04) {
            SM1_STATE = SM1_s1;
         }
         else {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s1:
         if ((PINA&0x07)==0x04) {
            SM1_STATE = SM1_s1;
         }
         else if (PINA==0x00) {
            SM1_STATE = SM1_s2;
         }
         else {
            SM1_STATE = SM1_s0;
         }
         break;
      case SM1_s2:
         if ((PINA&0x07)==0x02) {
            SM1_STATE = SM1_s3;
         }
         else if (!(PINA==0x00)) {
            SM1_STATE = SM1_s0;
         }
	 else {
            SM1_STATE = SM1_s2;
         }
         break;
      case SM1_s3:
         if ((PINA&0x07)==0x02) {
            SM1_STATE = SM1_s3;
         }
	 else if(PINA==0x00){
		SM1_STATE = SM1_s3;
	 }
         else if (PINA==0x80) {
            SM1_STATE = SM1_s0;
         }
         else {
            SM1_STATE = SM1_s0;
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
         PORTB=0;
         break;
      case SM1_s1:    
         break;
      case SM1_s2:      
         break;
      case SM1_s3:
         PORTB=1;
         break;
   }
}

int main(void) {
    DDRA = 0x00;
    DDRB = 0xFF;
    PORTA = 0xFF;
    PORTB = 0x00;
    SM1_STATE = SM1_SMStart;
   while(1){
	Tick_LoHi();
   }
    return 1;
}

