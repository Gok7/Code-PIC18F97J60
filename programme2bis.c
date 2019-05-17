#include<18F97J60.h>
#DEVICE ADC=10
#use delay(clock=25M)
#fuses HS,NOWDT
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)
#include "LCD_PicDemNet.C"


int32 compteur=0;

void main(){

int32 frequence=0;  //long int pour aller jusqua 2^16

enable_interrupts(INT_TIMER1);
enable_interrupts(GLOBAL);
lcd_init();
	while(true){
		compteur=0;
		SET_TIMER1(0);//initialise le timer
		setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1);//timer externe, division par 1
		delay_ms(1000);
		setup_timer_1(T1_DISABLED);//desactive le timer
		frequence=GET_TIMER1();//retourne la frequence
		printf(lcd_putc,"\f %lu",frequence+(65536*compteur));

		//le registre du compteur est sur 16bits
		//(2^16*compteur) sert a continuer de compter quand le registre est plein.
		//2^16 = 65536
			}	
}

#INT_TIMER1
void fonction(){

	compteur++;
}	