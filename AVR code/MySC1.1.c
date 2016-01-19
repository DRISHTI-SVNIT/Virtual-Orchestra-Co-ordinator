#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "notes.h"
#include "USART_32.h"
int flag = 0, i = 0, k = 0, max = 0;
int temp_array[10];
/*learning github starting project*/
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
				/*{c4,d4,e4,e4,e4,e4,e4,e4,e4,p,e4,e4,d4,e4,f4,e4,p,e4,e4,d4,p,d4,d4,b3,d4,c4,c4,g4
				,g4,g4,g4,g4,g4,g4,g4,g4,g4,a4,f4,f4,f4,f4,f4,f4,e4,d4,d4,f4,e4,e4,e4,d4,e4,e4,d4
				,e4,g4,g4,a4,f4,f4,e4,e4,e4,e4,e4,d4,d4,b3,d4,c4,c4,d4,e4,e4,e4,e4,d4,f4,e4,f4,g4
				,g4,g4,f4,e4,d4,f4,e4,f4,e4,e4,e4,d4,d4,b3,d4,c4,c4,c4,g4,g4,g4,g4,e4,g4,g4,g4,g4
				,g4,a4,f4,f4,f4,f4,f4,e4,d4,f4,e4,e4,g4,c4,b4,a4,b4,a4,g4,a4,c4,c4,d4,d4,e4,e4,d4,e4,f4}; */
	
	
				/*{E4,E4,Fis4,A4,A4,Gis4,Fis4,E4,

				E4,E4,Fis4,A4,A4,Gis4,Fis4,E4,

				F# G F# E F# G F# EF#

				F# E D C#

				E F# F# G F# E EEE




				*/int song[] = 			{Fis4, E4, G4, E4, Fis4, D4,E4,D4,
								Fis4, E4, G4, E4, Fis4, D4, E4,p,
								Fis4, E4, G4, E4, Fis4, D4, E4, D4,
								Fis4, E4, G4, E4, Fis4, D4, E4, p,		//32 till here
								Fis4, G4, B5, p, c5, p, B5, p,  C5, p, B5, p, C5, p, B5,		//15
								Fis4, G4, A5, p, B5, p, A5, p, B5,p, A5,p,G4, Fis4, E4,p	//16
				};		

				/* F# E G E F# D E

				F# E G E F# D E D

				F# E G E F# D E}; */
				
	//int song[] = {c4,d4,e4,f4,g4,a4,b4,c5,p};
		/*{
			B3, C3, Cis3, C3,
			B3, C3, Cis3, C3,

			E3,Fis3,Fis3,Fis3,p,E3,E3,E3,p,	//9
			E3,G3,G3,G3,p,Fis3,Fis3,Fis3,p,
			E3,Fis3,Fis3,Fis3,p,E3,E3,E3,p,
			E3,G3,G3,G3,p,Gis3,Fis3,Fis3,p,
			E3,Fis3,Fis3,Fis3,p,E3,E3,E3,p,
			E3,G3,G3,G3,p,Fis3,F3,E3,p,
			Dis3,D3,p,B3,A3,B3,p,
			
			{B3,C3,Cis3,C3,					//8
			B3,C3,Cis3,C3,

			E4, G4, Dis4, D4,p, G4, A4, B4,p,
			G4,A4,Fis4,p,Fis4,E4,Fis4,Dis4,p,
			E4, G4, Dis4, D4,p, G4, A4, B4,p,
			G4,A4,Fis4,p,C4,Dis4,E4,p};

			EE E F#EF#
			GG G F#EF#
			EE E F#EF#
			GG G F#EF#
			BB
			BB
			BBABB
		};*/
	ICR1 = song[i];
	i++;
}

void stopMusic()					//stop data trans. with Z
{
		flag = 0;
		ICR1 = 0;
		i = 0;
}

ISR(USART_RXC_vect)
{
	int tempo = (int)USART_Receive();
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
		if(i==62)
			i=0;
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
		//USART_Transmitchar('202');
		//ICR1 = 0;
	}
	//USART_TransmitNumber(max);
	//USART_Transmitchar(0x0d);
}

void main(void)
{
	sei();
	pwm_init();
	USART_Init(12);
	USART_InterruptEnable();
	OCR1B = 80;
	while(1)
	{		
	}
}