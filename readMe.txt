
## Project: prototype for the Mantrable

HardWare:
Recycle Textile with 5 soft buttons using conductive textile and 1 'analog queue'.
1 RGB led for visual effect
1 speaker to play tone via PWM

SoftWare:
2 led ui mode:
- single blink one soft button touch playing one note; five colour displayed and five notes played
- leds pattern changing brigthness and interval based on touch; playing 5 notes
- switch between mode is pressing the analog queue; play analog beep like teremin on this case.


## Release:
0.1: first implementation of only led displayed on 3 soft button press
0.2: five soft button press supporting single blink mode. use ledDisplay class
0.3: add tune playing: five tones for each soft button playing pentatonic
0.4: fix Blue Led issue due to pin 11 used: re-map pins


## TODO:
- structured code for softButton
- move code under ISR
- fine tune: 
  - step to increase led brightness to compensate difference output scale per color and 
  - sample refresh (delay(50);)
- add analog queue basic logic
- add second blinking mode
- finalize switch mode state machine with tune playing

## BUG and FIX
0001 -  adding tone function lead to have blue led (pin 11) to fill value immediately
        reason seems https://www.arduino.cc/en/Reference/Tone
        Use of the tone() function will interfere with PWM output on pins 3 and 11 (on boards other than the Mega).
        