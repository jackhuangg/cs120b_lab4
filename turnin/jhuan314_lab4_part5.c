/*	Author: jhuan314
 *	 *	 *  Partner(s) Name:Jack Huang 
 *	  *	  *	Lab Section:23
 *	   *	   *	Assignment: Lab #4  Exercise #5
 *	    *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *	     *
 *	      *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	       *	code, is my own original work.
 *	        *	        */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char temp=0;
unsigned char array[4]={4,1,2,1};
enum SM1_STATES { SM1_SMStart, presscheck, releasecheck, lock, unlock} SM1_STATE;
void Tick_LoHi() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         SM1_STATE = presscheck;
         break;
      case presscheck:
         if ((PINA&0x87)==0x80) {
             SM1_STATE = lock;
         }
         else if ((PINA&0x07)==array[temp]) {
            SM1_STATE = releasecheck;
         }
         else {
            SM1_STATE = presscheck;
         }
         break;
      case releasecheck:
	 if (((PINA&0x07)==0x01)&&((PORTB&0x01)==0x01)&&(temp==3)) {
            SM1_STATE = lock;
         }
         else if (((PINA&0x07)==0x01)&&(temp==3)) {
            SM1_STATE = unlock;
         }
         else if (PINA==0x00) {
	    temp++;
            SM1_STATE = presscheck;
         }
	 else{
	    SM1_STATE = releasecheck;
	 }
         break;
      case unlock:
        if (PINA==0x00) {
	    temp=0;
            SM1_STATE = presscheck;
         }
	else{
	    SM1_STATE = unlock;
	}
      case lock:
        if((PINA&0x87)==0x80){
            SM1_STATE = lock;
        }
        else{
	    temp=0;
            SM1_STATE = presscheck;
        }
   }
   switch(SM1_STATE) { 
      case SM1_SMStart:   
         PORTB=0;     
         break;
      case presscheck:
         break;
      case releasecheck:    
         break;
      case unlock:
	 PORTB=1;
	 break;
      case lock:
         PORTB=0;
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
