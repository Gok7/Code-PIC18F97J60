#include<18F452.h>
#DEVICE ADC=10
#fuses xt,nolvp,nowdt
#use delay(clock=4M)
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)


int tour=0;
long position;
void main(){	
enable_interrupts(INT_CCP1);
enable_interrupts(GLOBAL);
SET_TIMER1(0);//initialise le timer
setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);//timer externe, division par 1
setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
	
/*0 a 255
en 5 s 
+1 chaque fois
0 -1000
255 - 2000*/
	while(true){

				for(tour=0;tour<255;tour=tour+1){
					delay_us(9803);  //2.5/255	
				}

				for(tour=255;tour>0;tour=tour-1){
					delay_us(9803);  //2.5/255	
				}
			}
}

#INT_CCP1
void fonction(){
static int etat=1;

position=((1000.0/255.0)*(float)(tour)+1000.0);

switch(etat){

	case 1:
	CCP_1=CCP_1+position;
	setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
	etat=etat+1;
	break;

	case 2:
	CCP_1=CCP_1+position;
	setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
	etat=1;
	break;
	}	

}
