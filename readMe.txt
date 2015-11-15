
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


## TODO:
- move code under ISR
- add tune playing
- add analog queue basic logic
- add second blinking mode
- finalize switch mode state machine with tune playing