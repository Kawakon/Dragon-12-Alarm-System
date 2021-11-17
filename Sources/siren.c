/*----------------
File: siren.c
Description: Siren Module
------------------*/

#include "mc9s12dg256.h"

#define HIGH 	1
#define LOW  	0
#define HIGH_MS 600   //0.8 ms
#define LOW_MS 	150   //0.2 ms

int level;

void interrupt VectorNumber_Vtimch5 tc5_isr(void);

/*----------------------------------------------------
Function: initSiren
Description: initializes the hardware for implementing
the siren.
------------------------------------------------------*/

void initSiren(void)
{
	TIOS_IOS5 = 0x01;  // use channel 5 for output/compare
	TIE_C5I = 0x01;
}

/*----------------------------------------------------
Function: turnOnSiren
Description: turns on alarm siren, that is,
the PC speaker.
------------------------------------------------------*/

void turnOnSiren(void)
{
   TCTL1 |= 0b00000100;  // Timer Control Register 1 : Sets on pin 5 to toggle
   level = HIGH;      
   TC5 = TCNT + HIGH_MS; 
}

/*----------------------------------------------------
Function: turnOffSiren
Description: turns off alarm siren, that is,
the PC speaker.
------------------------------------------------------*/
void turnOffSiren()
{
   TIE_C5I = 0x00;    // Disable Interrupt for channel 5
   TCTL1 |= 0b00001000; 
   TCTL1 &= 0b11111011; 
}

/*----------------------------------------------------
Interrupt: tc5_isr
Description: siren ISR.
------------------------------------------------------*/
void interrupt VectorNumber_Vtimch5 tc5_isr(void)
{
	if(level == HIGH) // siren is turned on
	{
		level = LOW; 
		TC5 += LOW_MS;
	}
	else // siren is turned off
	{
		level = HIGH; 
		TC5 += HIGH_MS;
	}
}