/*
 * AvrProject01.c
 *
 * Created: 2/12/2015 9:53:26 PM
 *  Author: Shun
 */

// Set Frequency to 1MHz
#define F_CPU 1000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "AvrProject01.h"

// --------- Global Variables ----------

/*
 * mode 0: Timer
 * mode 1: Clock
 * mode 2: Stop Watch
 */
uint8_t mode = 0;

uint16_t bits_to_show = 0x0000;

  
// ---------- Common Functions ----------
uint16_t digit_in_bits(uint8_t n){
  /*
   * 7-Seg     Dots
   * 00000000  00000000
   * -abcdefg  78945123
  */
  switch(n){
    case 0: return 0x7e00; break;
    case 1: return 0x3000; break;
    case 2: return 0x6D00; break;
    case 3: return 0x7900; break;
    case 4: return 0x3300; break;
    case 5: return 0x5B00; break;
    case 6: return 0x5F00; break;
    case 7: return 0x7000; break;
    case 8: return 0x7F00; break;
    case 9: return 0x7300; break;
  }
  return 0x0000;
}

void shift_in(void) {Shift_High; _delay_ms(1);Shift_Low;}
void latch_up(void) {Latch_High; _delay_ms(1);Latch_Low;}
void reset(void)  {Reset_On;   Reset_Clear; latch_up();}


void display(uint16_t bits){
  // Initialize Bits
  bits_to_show = 0x0000;
  Status_On;
  
  // Set Mode Bit
  switch(mode){
    case 0: bits_to_show |= ((0 << 0)|(0 << 1)|(1 << 2)); break;
    case 1: bits_to_show |= ((0 << 0)|(1 << 1)|(0 << 2)); break;
    case 2: bits_to_show |= ((1 << 0)|(0 << 1)|(0 << 2)); break;
  }
  
  // Set Digit Bits
  bits_to_show |= bits;
  
  // Send bits to Shift Registers
  for(int i=0;i<16;i++){
    Register(0) = (bits_to_show>>i)&1;
    shift_in();
  }
  latch_up();
  Status_Off;
}

void initialize(void){
  // Setup
  DDRA  = 0xFF; // Set PA to Output
  DDRB  = 0x8F; // Set PB5,6,7 to Input
  PORTA = 0x00;
  PORTB = 0x70;

  GIMSK |= _BV(PCIE0);
  sei();
  reset();
  
  // Start Animation
  for(int i=0;i<32;i++){
    Status_On;
    if (i<16) {
      Register(0) = 1;
    } else {
      Register(0) = 0;
    }
    shift_in();
    latch_up();
    _delay_ms(50);
    Status_Off;
  } 
}


// --------- Interrupts ----------
ISR(IO_PINS_vect){
  if(~PINB & Btn_Red){
    _delay_ms(100);
    if(~PINB&Btn_Red){
      if(mode<2){
        mode++;
      } else {
        mode = 0;
      }
    }
  } 
}

ISR(TIMER1_CMPA_vect){
  
}

ISR(TIMER1_CMPB_vect){
  
}

// --------- Main ----------
int main(void)
{
  // Initialize
  initialize();
  
  // Event Loop
  while(1){

    for(int i=0;i<10;i++){
      display(digit_in_bits(i));
      //_delay_ms(500);
    }
  }
  return 0;
}