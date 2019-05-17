#include<18F97J60.h>
#DEVICE ADC=10
#use delay(clock=25M)
#fuses HS,NOWDT
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,STOP=1)

//#include "LCD_PicDemNet.C"

void main(){

int bouton=1;     //si 0 alors appui,si 1 alors relaché
int etat=0b00000001;
SET_TRIS_B(0xFF);  //en entree
SET_TRIS_J(0x00);  //en sortie
//lcd_init();
ext_int_edge(L_TO_H); //front montant
enable_interrupts(INT_EXT);
enable_interrupts(GLOBAL);

	while(true){
		while(etat!=0b00000000){
		
			delay_ms(500);
			output_J(etat);
			etat=etat<<1;
		
		       }

		etat=0b00000001;

	}	
}

#INT_EXT//gere l'entree RBO
fonctionIT(){
	
	int i;
	int sav_led;
	sav_led=input_j();//sauvegarde etat led
		for(i=0;i<3;i++){
	
			output_J(0xff);
			delay_ms(500);
			output_J(0x00);
			delay_ms(500);
		}
	output_J(sav_led);
}

	

	