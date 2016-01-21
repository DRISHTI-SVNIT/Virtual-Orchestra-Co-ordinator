/*
 * VOC_1.cpp
 *
 * Created: 21-01-2016 15:19:48
 *  Author: Harsimar
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "notes.h"
#include "USART_128.h"
#include "EEPROM.h"
int flag = 0, current_song_node = 0, k = 0, max = 0,song_no=0,tempo=0;
int temp_array[10];


void pwm_init()
{
	DDRD |= _BV(PD4);						//Setting output
	TCCR1A |= _BV(COM1A1) | _BV(COM1B1);	//16 bit T/C
	TCCR1B |= _BV(WGM13) | _BV(CS11);		//Phase and Frequency correct mode, prescaler 8
	
}


void startMusic()							//start data trans. with Z
{
	flag = 1;
}


void playMusic()					//8-bit tempo value
{
				
				int song[][62] = {	{Fis4, E4, G4, E4, Fis4, D4,E4,D4,
								Fis4, E4, G4, E4, Fis4, D4, E4,p,
								Fis4, E4, G4, E4, Fis4, D4, E4, D4,
								Fis4, E4, G4, E4, Fis4, D4, E4, p,		//32 till here
								Fis4, G4, B5, p, c5, p, B5, p,  C5, p, B5, p, C5, p, B5,		//15
								Fis4, G4, A5, p, B5, p, A5, p, B5,p, A5,p,G4, Fis4, E4,p},	//16
				
								{
									E3,Fis3,Fis3,Fis3,p,E3,E3,E3,p,	//9
									E3,G3,G3,G3,p,Fis3,Fis3,Fis3,p,
									E3,Fis3,Fis3,Fis3,p,E3,E3,E3,p,
									E3,G3,G3,G3,p,Gis3,Fis3,Fis3,p,
									E3,Fis3,Fis3,Fis3,p,E3,E3,E3,p,
									E3,G3,G3,G3,p,Fis3,F3,E3,p,
									Dis3,D3,p,B3,A3,B3,p,p,p
								}								
								
								};
										
				
	ICR1 = song[song_no][current_song_node];
	current_song_node++;
}

void stopMusic()					//stop data trans. with Z
{
		flag = 0;
		ICR1 = 0;
		current_song_node = 0;
}

ISR(USART_RXC_vect)
{
	tempo = (int)USART_Receive(0);
	if(k<8)
	{
		temp_array[k] = tempo;
		k++;
	}
	else
	{
		max=0;
		for(k=7;k>=0;k--)
		{
			if(temp_array[k]>max)
			{
				max = temp_array[k];
			}
		}
		k=0;
	}
	if(tempo == 201)
		startMusic();
	else if(tempo == 200)
		stopMusic();
	if(flag)
	{
		if(current_song_node==62)
			{current_song_node=0;
			song_no++;
			}			
		playMusic();
		for(int j=130;j>max;j--)
		{
			_delay_ms(10);
			
		}
		while(UCSRA & (1<<RXC))
		{
			unsigned char dummy;
			if(UDR!=200)
			dummy = UDR;
		}
		//USART_Transmitchar('202',0);
		//ICR1 = 0;
	}
	//USART_TransmitNumber(max);
	//USART_Transmitchar(0x0d);
}

int main()
{
	sei();
	pwm_init();
	USART_Init(12,0);
	USART_InterruptEnable(0);
	OCR1B = 80;
	
	TCCR1B |=1<<CS10|1<<WGM12;
	TIMSK|=1<<OCIE1A;
	OCR1A=32000;
	
	while(1)
	{		
	}
return 0;
}
   
ISR(TIMER1_COMPA_vect)
{EEPROM_write(0x0A,tempo);
}	
