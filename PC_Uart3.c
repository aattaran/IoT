#include "tm4c123gh6pm.h"
#include "PC_Uart3.h"



void PC_UART3_Init(void){
// Using PC5,PC4
  SYSCTL_RCGCUART_R |= 0x08; // activate UART3
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port D
  UART3_CTL_R &= ~UART_CTL_UARTEN;      // disable UAR/
	/*
	* BAUD RATE calculation
	*/
  UART3_IBRD_R = 8;                    // IBRD = int(16,000,000 / (16 * 115200)) = int(8.68)
  UART3_FBRD_R = 44;                    // FBRD = round(0.68 * 64) = 44
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART3_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART3_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTC_AFSEL_R |= 0xC0;;           // enable alt funct on PC7,PC6
  GPIO_PORTC_DEN_R |= 0xC0;             // enable digital I/O on PC7,PC6
                                        // configure PC7,PC6 as UART3
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0x00FFFFFF)+0x11000000;//11 is required to alternate function of PC7,6 as UART3 ( from data sheet)
  GPIO_PORTC_AMSEL_R &= ~0xC0;          // disable analog functionality on PC7,PC6
}

void PC_UART3_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART3
  while((UART3_FR_R&UART_FR_TXFF) != 0);
  UART3_DR_R = data;
}

void PC_UART3_OutString(unsigned char buffer[]){
// as part of Lab 11 implement this function
	unsigned char i=0;
	while(buffer[i]!=0){
		//data=convert_to_ascii();
		PC_UART3_OutChar(buffer[i]);
		i++;
	}
	
}
