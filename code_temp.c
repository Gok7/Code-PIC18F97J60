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
lcd_init();

while(1){
		     TempBrute=MesureTemp_Brute();
		     PotBrute=MesurePotentiometreBrute();

			 Temp_volt=TempBrute*(UREF/1023.0);
		   	 Pot_volt=PotBrute*(UREF/1023.0);

			 Temp_degre=(Temp_volt*100)-50;
			 Potdegree=(Pot_volt*100)-50;

             printf(lcd_putc,"\fT: %fV %f C\n",Temp_volt,Temp_degre);
             printf(lcd_putc,"P: %fV %f C",Pot_volt,Potdegree);

	         delay_ms(100);
        }
}
