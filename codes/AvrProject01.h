/*
 * AvrProject01.h
 *
 * Created: 2/12/2015 9:53:26 PM
 *  Author: Shun
 */

// Shift Registers
#define Data_Pin  0
#define Latch_Pin 1
#define Shift_Pin 2
#define Reset_Pin 3

#define Shift_High  PORTA |=  _BV(Shift_Pin)
#define Shift_Low PORTA &= ~_BV(Shift_Pin)
#define Latch_High  PORTA |=  _BV(Latch_Pin)
#define Latch_Low PORTA &= ~_BV(Latch_Pin)
#define Reset_On  PORTA &= ~_BV(Reset_Pin)
#define Reset_Clear PORTA |=  _BV(Reset_Pin)

#define Register(num) ((volatile _register_bits*)&PORTA)->bit##num

typedef struct {
  unsigned int bit0:1;
  unsigned int bit1:1;
  unsigned int bit2:1;
  unsigned int bit3:1;
  unsigned int bit4:1;
  unsigned int bit5:1;
  unsigned int bit6:1;
  unsigned int bit7:1;
} _register_bits;


// Status LED
#define Status_On PORTB &= ~(1 << 3)
#define Status_Off  PORTB |=  (1 << 3)

// Buttons
#define Btn_Red   0x10
#define Btn_Yellow  0x20
#define Btn_Green 0x40