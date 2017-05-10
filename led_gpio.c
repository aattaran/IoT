#include "tm4c123gh6pm.h"
#include "Led_gpio.h"

//PB7 as Output
void Led_GPIO_Init(){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;       // 1) B clock
  delay = SYSCTL_RCGC2_R;             // delay to allow clock to stabilize     
  GPIO_PORTB_AMSEL_R &= ~0x80;        // 2) disable analog function
  GPIO_PORTB_PCTL_R &=~ 0xF0000000;   // 3) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R |= 0x80;           // 4) PB7 Output,
  GPIO_PORTB_AFSEL_R &=~ 0x80;        // 5) no alternate function  
  GPIO_PORTB_DEN_R |= 0x80;           // 6) enable digital pins PB7
}

void Led_Turn_on(){
	GPIO_PORTB_DATA_R |= 0x00000080;
}

void Led_Turn_off(){
	GPIO_PORTB_DATA_R &=~ 0x00000080;
}
