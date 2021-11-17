/*------------------------------------------------------------------------------- 
   File: keyPad.c
   Description:  Keypad Module
------------------------------------------------------------------------------*/

#include <stdtypes.h>
#include "mc9s12dg256.h"
#include "keyPad.h"

// Some definitions
#define FIFTEEN_MS 		11250 // = 15 ms
#define MONITORING_KEY 0
#define FIRST_DEBOUNCE	1
#define KEY_RELEASE	2
#define SECOND_DEBOUNCE	3


// Global variables
volatile byte code;

// Function prototypes not included in header file
void interrupt VectorNumber_Vtimch4 tc4_isr(void);
byte getKeyCode(void);
char getASCII(byte);

byte byteCodes[16] = {0b01111101, 0b11101110, 0b11101101, 0b11101011, 0b11011110, 0b11011101, 0b11011011, 0b10111110, 0b10111101, 0b10111011, 0b11100111, 0b11010111, 0b10110111, 0b01110111, 0b01111110, 0b01111011};
byte asciiCodes[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd','*','#'};

/*----------------------------------------------------
Function: initKeyPad
Description: initializes the hardware (i.e. PortA)
connected to the keypad and a timer channel used to
generate interrupts at regular intervals.
------------------------------------------------------*/
void initKeyPad(void)
{
	DDRA   = 0xF0; 
	PORTA  = 0x00;
	PUCR |= 0x01;
	TIOS_IOS4 = 0x01;
	TIE_C4I = 0x01;
	TC4 = TCNT + FIFTEEN_MS; 
	code = 0;
}

/*----------------------------------------------------
Function: readKey
Description: read a key from the keypad (returns the
ASCII code of the key pressed). The value of the key is
returned once the key is released.
------------------------------------------------------*/
char readKey(void)
{
	char ch;

	while(!code); // do nothing 
	ch = getASCII(code); 
	code = 0;

	return ch;
}

/*----------------------------------------------------
Function: pollReadKey
Description: read a key from the keypad (returns the
ASCII code of the key pressed). The value of the key is
returned once the key is released.
------------------------------------------------------*/
char pollReadKey(void)
{
	char ch;

	if (!code){
		ch = 0;
	}
	else
	{
		ch = getASCII(code); 
		code = 0; 
	}

	return ch;
}

/*----------------------------------------------------
Function: getKeyCode
------------------------------------------------------*/

byte getKeyCode(void)
{
	byte aa = 0x0F;
	aa &= PORTA;
	aa |= 0xD0;
	if (aa != 0xDF){
		code = aa;
		return code;
	}
	byte aa = 0x0F;
	aa &= PORTA;
	aa |= 0xE0;
	if (aa != 0xEF){
		code = aa;
		return code;
	}
	byte aa = 0x0F;
	aa &= PORTA;
	aa |= 0xB0;
	if (aa != 0xBF){
		code = aa;
		return code;
	}
	byte aa = 0x0F;
	aa &= PORTA;
	aa |= 0x70;
	if (aa != 0x7F){
		code = aa;
		return code;
	} code = 0x0F;
	return code;
}

/*----------------------------------------------------
Function: getASCII
------------------------------------------------------*/

char getASCII(byte value)
{
	char ascii = 0;

	for (int i = 0; i < 16; i++)
	{
		if (byteCodes[i] == value)
		{
			ascii = asciiCodes[i];
			break;
		}
	}

	return ascii;
}

/*----------------------------------------------------
Interrupt: tc4_isr
Description: key ISR checks this function every 10 ms.
------------------------------------------------------*/

void interrupt VectorNumber_Vtimch4 tc4_isr(void)
{
	static byte state = MONITORING_KEY;
	static byte keyCode;

	switch(state)
	{
		case MONITORING_KEY:
			keyCode = PORTA;
			if(keyCode != 0x0F) state = FIRST_DEB;
			break;
		case FIRST_DEB:
			if(PORTA != keyCode) state = WAITING_FOR_KEY;
			else
			{
				keyCode = getKeyCode(); 
				state = KEY_RELEASE; 
			}
			break;
		case KEY_RELEASE:
			if(PORTA == 0x0F) state = SECOND_DEBOUNCE;
			break;
		case SECOND_DEBOUNCE:
			if(PORTA != 0x0F) state = KEY_RELEASE;
			else
			{
				code = keyCode;
				state = WAITING_FOR_KEY;
			}
			break;
	}

	TC4 = TC4 + FIFTEEN_MS; 
}

