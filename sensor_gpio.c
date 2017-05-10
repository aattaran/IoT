#include "sensor_gpio.h"
#include "tm4c123gh6pm.h"
/* Initialize GPIO PB6 as Input to read Light_Sensor value
*/
void Light_Sensor_GPIO_Init(){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000002;      // 1) B clock
  delay = SYSCTL_RCGC2_R;            // delay to allow clock to stabilize     
  GPIO_PORTB_AMSEL_R &= ~0x40;        // 2) disable analog function
  GPIO_PORTB_PCTL_R &=~ 0x0F000000;   // 3) GPIO clear bit PCTL  
  GPIO_PORTB_DIR_R &= ~0x40;         // 4.1) PB6 Input,
  GPIO_PORTB_AFSEL_R &=~ 0x40;        // 5) no alternate function
 // GPIO_PORTB_PUR_R |= 0x00;          // 6) enable pullup resistor on PB6
  GPIO_PORTB_DEN_R |= 0x40;          // 7) enable digital pins PB6
}

unsigned int Light_Sensor_Get_Value(){
	return (GPIO_PORTB_DATA_R &= 0x00000040)>>6;
}

