
#include "ADC.h"
#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "Fan_control.h"
#include "misc.h"
#include "led_gpio.h"
#include "light_sensor.h"
#include "sensor_gpio.h"
#include "PC_Uart3.h"
//void EnableInterrupts(void);  // Enable interrupts


unsigned char TEMP[]={'T','E','M','P','E','R','A','T','U','R','E','\r','\n','\0'}; // null-terminated ASCII string
unsigned char ALERT[]={'A','L','E','R','T','\r','\n','\0'}; 
//unsigned char ALI[13]={'E','N','G','R',32,'8','4','8',001,003,'\r','\n','\0'}; 
unsigned long ADCdata;    // 12-bit 0 to 4095 sample
unsigned char Temp_s[20];



void Convert_data_to_temp(unsigned long data){
	unsigned long result;
	unsigned char i=0;
	// 3.3volts*(data)/4096
	result=((33*1000*data)/4096)%100000;//rounding off to maximum 5 digits
	
	//result=((((33*1000*data)/4096)%100000)*5/9)-32;//rounding off to maximum 5 digits

	Temp_s[0]=0x30;
	Temp_s[3]='.';
	for(i=0;i<6;i++)
		{
		if(i==2){continue;}
			Temp_s[5-i]=(result%10)+0x30;
			result=result/10;
		}
		Temp_s[i]=32; Temp_s[i+1]=32;Temp_s[i+2]='*';Temp_s[i+3]=32;Temp_s[i+4]='C';Temp_s[i+5]=13;Temp_s[i+6]=10;
}


int main(void){ 
		
	/*
	*  temperature Initializations
	*/
	Temperature_sensor_ADC0_Init();
  Nokia5110_Init();             
	Fan_GPIO_Init();
	PC_UART3_Init();

	
	/*
	*  light Initializations
	*/
	Light_Sensor_GPIO_Init();
	Led_GPIO_Init();
	//delay100();
	/* Sending initial messages to LCD module
	*
	*/
	Nokia5110_SetCursor(0, 0);
	Nokia5110_OutString(TEMP);
	PC_UART3_OutString(TEMP);
		// 
	/*main loop */
  while(1){
		

	 delay_one_second();
	 ADCdata = read_temperature();
	 Convert_data_to_temp(ADCdata);
	 //
		light_sensor();
		
	 if(ADCdata < 970) {//800 means round 70 degrees 
		 Nokia5110_Clear();
		 Nokia5110_SetCursor(1, 0);
		 Nokia5110_OutString(Temp_s);
		 PC_UART3_OutString(Temp_s);
		 Fan_Turn_off();
		 light_sensor();
	 }
	 else{
		 
		 Nokia5110_Clear();
		 Nokia5110_SetCursor(1, 0);
		 Nokia5110_OutString(ALERT);
		 PC_UART3_OutString(ALERT);
		 Fan_Turn_on();
		 light_sensor();
		 
		 
		 while (ADCdata < 970){
			 Nokia5110_Clear();
			 Nokia5110_SetCursor(1, 0);
			 Nokia5110_OutString(Temp_s);
			 PC_UART3_OutString(Temp_s);
			 Fan_Turn_off();
			 light_sensor();
			 

		 }
		}
	}
}
