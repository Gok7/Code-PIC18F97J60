#include<18F97J60.h>
#use delay(clock=25M)
#include "LCD_PicDemNet.C"
#fuses HS,NOWDT
#DEVICE ADC=10
#include<devices.h>

void main(){
long temperature=0;
setup_adc(ADC_CLOCK_DIV_8);
setup_adc_ports(AN0_TO_AN3);
set_adc_channel(3);
temperature = read_adc();
SET_TRIS_B(0xFF);//en entree
lcd_init();

while(1){
			 temperature = read_adc();
             printf(lcd_putc,"\f %l",temperature);
	         delay_ms(100);
}