#include<18F97J60.h>
#use delay(clock=25M)
#include "LCD_PicDemNet.C"
#fuses HS,NOWDT
#use fast_io(B)


void main(){
	int bouton=1;//si 0 alors appui,si 1 alors relaché
	int entree=0;
	int masque=0b00001111;
	SET_TRIS_B(0xFF);//en entree
	lcd_init();

	while(true){//a modifier
		bouton=input_B();
		entree=masque&bouton;
		switch (entree){
		
			case 0b00001110: printf(lcd_putc,"\f bouton 1");
					
			break;
			case 0b00001101: printf(lcd_putc,"\f bouton 2 ");
			break;
			case 0b00001011: printf(lcd_putc,"\f bouton 3");
				
			break;
			case 0b00000111: printf(lcd_putc,"\f bouton 4");
					
			break;
			default :printf(lcd_putc,"\fVeuillez appuyez\n");
					
			break;
		}	
	delay_ms(100);
	}
}