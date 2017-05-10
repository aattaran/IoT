#include "tm4c123gh6pm.h"
#include "Fan_control.h"
/* Initialize GPIO PF1 as Output to control FAN
*/
void Fan_GPIO_Init(){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;      // 1) F clock
  delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
  GPIO_PORTE_AMSEL_R &= ~0x02;        // 2) disable analog function
  GPIO_PORTE_PCTL_R &=~ 0x000000F0;   // 3) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R |= 0x02;         // 4.1) PF1 Output,
  GPIO_PORTE_AFSEL_R &=~ 0x02;        // 5) no alternate function
  GPIO_PORTE_PUR_R |= 0x00;          // 6) enable pullup resistor on PF4       
  GPIO_PORTE_DEN_R |= 0x02;          // 7) enable digital pins PF4-PF1
}

void Fan_Turn_on(){
	GPIO_PORTE_DATA_R |= 0x00000002;
}

void Fan_Turn_off(){
	GPIO_PORTE_DATA_R &=~ 0x00000002;
}
