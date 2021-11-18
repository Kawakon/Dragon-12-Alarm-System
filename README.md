# Dragon-12-Alarm-System
## Emulation of Alarm System of Dragon-12 HCS12 Board with Assembly and C Programming

In this project, the Dragon-12 HCS12 Development Board is used to design an alarm system implemented within a home with assembly code and C programming. The alarm system enables a 
user to set an alarm that can be triggered upon a button press and deactivated with a keypad entry. A LCD display prints the state of the alarm system (ARMED, ARMING, or DISARMED). 
The main modules of the system include the Switches, Siren, Delay, Segment Display, Keypad, and LCD Display modules. 

### Switches Module

This modules emulates the opening of a door or window within the home, thus triggering the alarm when the system has been SET. The triggering is caused by pressing button switches 
on the HCS12 board. Within the module, the a data register is initialized and the state of the switches are monitored as they are written to the register.

### Siren Module

This module controls the speaker connected to development board. When the alarm is triggered, the speaker produces a sounds. The speaker does not produce a sound when the alarm is 
being disarmed or set. The Timer Channels of the HCS12 microprocessor were used to produce a waveform for the alarm sound (or to turn off the speaker).

### Delay Module

This module handles all delay operations during the execution of the alarm system. For instance, a user may provide a keypad entry to arm/disarm the alarm system. During each key 
press, the key pressed is displayed on the seven segment LED display, where there is a display between displayed digits. 

### Segment Display Module

This module receives the ASCII codes of the keypad presses and displays the value to one of the four seven-segment LED displays on the HCS12 development board. The module also clears
the LED displays when they are not needed.

### Keypad Module

This module monitors the keypad to determine if a key has been pressed and returns the value of the key pressed, if necessary. A key press is determined by using the Timer channels 
of the microprocessor to compare the keypress register value(s) before and after a 15 ms debouncing period. If a key press has been detected, the register value is matched to its 
corresponding ASCII character. 

### LCD Display Module

This module prints characters to one of the two lines on the Dragon-12 board's LCD display. This module is used when printing the state of the alarm system for the user. 

## Diagrams

The following images depict the hardware components used to implement the alarm system modules:

![image](https://user-images.githubusercontent.com/43174428/142348657-34340c01-1d94-407c-8eee-e3b271cd80d0.png)

This image shows the Timer Module of the Dragon-12 HCS12 board, in which it specifies the registers used for the output-compare system. In this module, timer compare registers TCX (where X is a number from 0 to 7) are set with a value and compared to the timer counter (TCNT register) of the board. When the values of the register are equal, a timer interrupt is serviced, in which an action can be performed. This feature is used to implement the function in the above modules. 

![image](https://user-images.githubusercontent.com/43174428/142348697-0f029cbf-08ee-4fe3-9fc6-c8fc9de6d393.png)

This image shows the keypad matrix as it is connected to the pull up resistors and daa register Port A of the HCS12. The combination of bits in Port A is used to determine which key has been pressed. When a key is pressed, the appropriate input pin is set according to the column in which the key is found. If the key ‘2’ is pressed, the PA1 pin, which is in column 1, will be set to logic 0 and the PA0, PA2, and PA3 will be set to logic 1. The switch will be connected to the output pin of the corresponding row and set to logic 0. The rest of the output pins are set to logic 1. Following from the previous example, the output pin PA4 will be set to logic 0, while PA5, PA6, and PA7 are set to logic 1.
