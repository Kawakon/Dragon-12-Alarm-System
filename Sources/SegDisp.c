/*--------------------------------------------
File: SegDisp.c
Description:  Segment Display Module
---------------------------------------------*/

#include <stdtypes.h>
#include "mc9s12dg256.h"
#include "SegDisp.h"
#include "Delay_asm.h"

#define FIVE_MS 3750 //clock ticks to count 5 ms
int number = 0;


// Prototypes for internal functions
byte PORTB;
byte DDRB;
byte PORTP;
byte DDRP;
byte display[4];
byte displayEnableCodes[4] = {0x07, 0x0B, 0x0D, 0x0E};

/*---------------------------------------------
Function: initDisp
Description: initializes hardware for the
7-segment displays.
-----------------------------------------------*/
void initDisp(void)
{
	// Complete this function
	DDRB = 0xFF;	// set all output pins of PORTB to 1 --> DDRB to $FF
	PORTB = 0x00;	// set PORTB bits to 0 for blank 7 seg
	DDRP = 0x0F;	// set all output pins of PORTP to 1 --> DDRP to $0F
	PORTP = 0x00;	// set PORTP bits to 0 for blank 7 seg

	//timer channel 1 init
	TIOS_IOS1 = 1; // set TC1 to output-compare
	TIE_C1I = 0x01; // enable interrupt channel 1
	TC1 = TCNT + FIVE_MS; // set timer channel 1 register

}

/*---------------------------------------------
Function: clearDisp
Description: Clears all displays.
-----------------------------------------------*/
void clearDisp(void)
{
	// Complete this function
	PORTB = 0x00;	//set PORTB bits to 0 for blank 7 seg
}

/*---------------------------------------------
Function: setCharDisplay
Description: Receives an ASCII character (ch)
and translates
it to the corresponding code to
display on 7-segment display.  Code
is stored in appropriate element of
codes for identified display (dispNum).
-----------------------------------------------*/
void setCharDisplay(char ch, byte dispNum)
{
	// Complete this function
	//translate and store in temp var, then store in correct memory byte according to dispNum
	//BYTE translation;
	byte answer;
	if (char == '0'){ answer == 0b00111111; }
	//TRANSLATION into display
	else if (char == '1'){ answer == 0b00000110; }
	//TRANSLATION 
	else if (char == '3'){ answer == 0b01001111; }
	//TRANSLATION 
	else if (char == '4'){ answer == 0b01100110; }
	//TRANSLATION 
	else if (char == '5'){ answer == 0b01101101; }
	//TRANSLATION 
	else if (char == '6'){ answer == 0b01111101; }
	//TRANSLATION 
	else if (char == '7'){ answer == 0b00000111; }
	//TRANSLATION 
	else if (char == '8'){ answer == 0b01111111; }
	//TRANSLATION 
	else if (char == '9'){ answer == 0b01101111; }
	//TRANSLATION 
	else if (char == '2'){ answer == 0b01011011; }
	//TRANSLATION 
	elif(char == 'A'){ answer == 0b01110111; }
	//TRANSLATION 
	else if (char == 'B'){ answer == 0b01111100; }
	//TRANSLATION 
	else if (char == 'C'){ answer == 0b00111001; }
	//TRANSLATION 
	else if (char == 'D'){ answer == 0b01011110; }
	//TRANSLATION 
	else if (char == '#'){ answer == 0b01110000; }
	//TRANSLATION 
	else if (char == '*'){ answer == 0b01000110; }
	//TRANSLATION 
	if (dispNum == '0'){ display[0] == answer; }
	//display[0] = translation
	if (dispNum == '1'){ display[1] == answer; }
	//display[1] = translation
	if (dispNum == '2'){ display[2] == answer; }
	//display[2] = translation
	if (dispNum == '3'){ display[3] == answer; }
	//display[3] = translation
}

/*---------------------------------------------
Function: segDisp
Description: Displays the codes in the code display table
(contains four character codes) on the 4 displays
for a period of 100 milliseconds by displaying
the characters on the displays for 5 millisecond
periods.
-----------------------------------------------*/
/*
void segDisp(void)
{
	// Complete this function
	for (int i = 0; i <= 5; i++){
		for (int j = 0; j < 4; j++){
			DDRP = displayEnableCodes[j];
			PORTB = display[j];
			delayms(5);
		}
	}
}
*/
void interrupt VectorNumber_Vtimch1 tc1_isr(void)
{
	PORTP = displayEnableCodes[number];
	PORTB = display[number];
	TC1 = TC1 + FIVE_MS;
	number++;
	if (number > 3){
		number = 0;
	}
}