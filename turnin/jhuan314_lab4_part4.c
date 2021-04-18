/*	Author: jhuan314
 *	 *  Partner(s) Name:Jack Huang 
 *	  *	Lab Section:23
 *	   *	Assignment: Lab pound4  Exercise pound1
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM1_STATES { SM1_SMStart, presspound, releasepound, pressY, releaseY, lock} SM1_STATE;
void Tick_LoHi() { 
   switch(SM1_STATE) { 
      case SM1_SMStart:
         SM1_STATE = presspound;
         break;
      case presspound:
         if ((PINA&0x87)==0x80) {
             SM1_STATE = lock;
         }
         else if ((PINA&0x07)==0x04) {
            SM1_STATE = releasepound;
         }
         else {
            SM1_STATE = presspound;
         }
         break;
      case releasepound:
         if ((PINA&0x07)==0x04) {
            SM1_STATE = releasepound;
         }
         else if (PINA==0x00) {
            SM1_STATE = pressY;
         }
         break;
      case pressY:
         if (((PINA&0x07)==0x02)&&((PORTB&0x01)==0x01)) {
            SM1_STATE = lock;
         }
         else if ((PINA&0x07)==0x02) {
            SM1_STATE = releaseY;
         }
         else if (PINA!=0x00) {
            SM1_STATE = presspound;
         }
	     else {
            SM1_STATE = pressY;
         }
         break;
      case releaseY:
         if ((PINA&0x07)==0x02) {
            SM1_STATE = releaseY;
         }
         else {
            SM1_STATE = presspound;
         }
         break;
      case lock:
        if(((PINA&0x07)==0x02)){
            SM1_STATE = lock;
        }
        else if((PINA&0x87)==0x80){
            SM1_STATE = lock;
        }
        else{
            SM1_STATE = presspound;
        }
   }
   switch(SM1_STATE) { 
      case SM1_SMStart:   
         PORTB=0;     
         break;
      case presspound:
         break;
      case releasepound:    
         break;
      case pressY:      
         break;
      case releaseY:
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
