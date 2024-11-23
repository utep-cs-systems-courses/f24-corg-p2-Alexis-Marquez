# Lab 2: Blinky-Buzzy Toy
## How to compile
To compile simply use the make command inside of the project folder.

## How to run and use

To run and use the toy simply run the command make load with an msp430 microcontroller connected.
The default state is state 4. Here is a description of the 4 different states and how to transition between them:
* State 1: Links blink once per second, speaker plays a note from the C minor scale each second and resets to middle C after 8 notes.
* State 2: Links blink twice per second, speaker plays a note from the C major scale each half second and resets to middle C after 8 notes.
* State 3: Links blink three times per second, speaker plays a random note from the C minor scale at random intervals and resets after a random number of notes between 1 and 4.
* State 4: Links blink fourt times per second, speaker plays a random note from the C major scale at random intervals and resets after a random number of notes.
