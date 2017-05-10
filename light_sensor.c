#include "sensor_gpio.h"
#include "led_gpio.h"
#include "misc.h"

void light_sensor(void){ 
	
	Light_Sensor_GPIO_Init();
	Led_GPIO_Init();
	//while(1){	
		//Every one second read the sensor output value
		
		if(Light_Sensor_Get_Value()==1){
			//delay100();
			Led_Turn_off();
		}
		else{
			//delay100();
			Led_Turn_on();
		}
	}
	
	
//}

