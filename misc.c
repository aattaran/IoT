#include "misc.h"

void delay_one_second(){
unsigned char i;
	for(i=0;i<10;i++){ delay100();}
}


void delay100(void){
int i ;
 i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
}
