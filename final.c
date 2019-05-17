#include<18F97J60.h>
#DEVICE ADC=10
#use delay(clock=25M)
#include "LCD_PicDemNet.C"
#fuses HS,NOWDT
#use fast_io(B)
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
//declarer les choses dans le bon ordre
float TempBrute=0;
float Temp_volt=0;
float Temp_degre=0;
float PotBrute=0;
float Pot_volt=0;
float Potdegree=0;
int bouton=1;//si 0 alors appui,si 1 alors relaché
int entree=0;
int masque=0b00001111;
float Temp_Consigne=20;
SET_TRIS_B(0xFF);//en entree

SET_TRIS_J(0x00);
setup_adc(ADC_CLOCK_DIV_8);
setup_adc_ports(AN0_TO_AN3);
	

lcd_init();

	while(true){
		bouton=input_B();
		entree=masque&bouton;

			 TempBrute=MesureTemp_Brute();
		     PotBrute=MesurePotentiometreBrute();

			 Temp_volt=TempBrute*(UREF/1023.0);
		   	 Pot_volt=PotBrute*(UREF/1023.0);

			 Temp_degre=(Temp_volt*100)-50;
			 Potdegree=(Pot_volt*100)-50;
		     printf(lcd_putc,"\fTemp Cons : %f \n",Temp_Consigne);
		     printf(lcd_putc,"Temp Mesure : %f",Temp_degre);//temperature consigne
			 
			if((Temp_degre>Temp_Consigne+5.0)||(Temp_degre<Temp_Consigne-5.0)){
			     output_J(0b01000000);
			}
			else{
				output_J(0b10000000);//fonctionne bien
			}
			if(Temp_degre>Temp_Consigne+2.0){
			     output_high(PIN_D0);
			}
			if(Temp_degre<Temp_Consigne-2.0){
			     output_low(PIN_D0);
			}
		switch (entree){
		
			case 0b00001110: Temp_Consigne+=1;delay_ms(100);	
			break;
			case 0b00001101: Temp_Consigne-=1;delay_ms(100);
			break;
		}
	delay_ms(100);
	}
}