#include<18F97J60.h>
#DEVICE ADC=10

#use delay(clock=25M)
#include "LCD_PicDemNet.C"
#fuses HS,NOWDT
#define UREF 3.307

float MesureTemp_Brute(void)
{
	float Mesure;
	set_adc_channel(3);
	delay_us(10);
	Mesure = read_adc();
	return Mesure;
}

float MesurePotentiometreBrute(void)
{
	float Mesure;
	set_adc_channel(2);
	delay_us(10);
	Mesure = read_adc();
	return Mesure;
}

void main(){
float TempBrute=0;
float Temp_volt=0;
float Temp_degre=0;
float PotBrute=0;
float Pot_volt=0;
float Potdegree=0;
setup_adc(ADC_CLOCK_DIV_8);
setup_adc_ports(AN0_TO_AN3);
SET_TRIS_B(0xFF);//en entree
int bouton=1;//si 0 alors appui,si 1 alors relaché
int entree=0;
int masque=0b00001111;
lcd_init();

while(1){
			 bouton=input_B();
	     	 entree=masque&bouton;
		     TempBrute=MesureTemp_Brute();
		     PotBrute=MesurePotentiometreBrute();

			 Temp_volt=TempBrute*(UREF/1023.0);
		   	 Pot_volt=PotBrute*(UREF/1023.0);

			 Temp_degre=(Temp_volt*100)-50;

             printf(lcd_putc,"\f %f C\n",Temp_degre);
	
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