#include <msp430.h>

#include "switches.h"

#include "led.h"



char switch_state_down, switch_state_changed; /* effectively boolean */



static char

switch_update_interrupt_sense()
{

  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */

  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */

  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}



void

switch_init()/* setup switch */

{

  P2REN |= SWITCHES;/* enables resistors for switches */

  P2IE |= SWITCHES;/* enable interrupts from switches */

  P2OUT |= SWITCHES;/* pull-ups for switches */

  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  switch_update_interrupt_sense();
}



void

switch_interrupt_handler()

{  
  char p2val = switch_update_interrupt_sense();
  
  if (!(p2val & SW1)) {  // Check if Switch 1 is pressed
    CURRSTATE = 1;
  } else if (!(p2val & SW2)) {  // Check if Switch 2 is pressed
    CURRSTATE = 2;
  } else if (!(p2val & SW3)) {  // Check if Switch 3 is pressed
    CURRSTATE = 3;
  } else if (!(p2val & SW4)) {  // Check if Switch 4 is pressed
    CURRSTATE = 4;
  }
  switch_state_changed = 1; 
}
