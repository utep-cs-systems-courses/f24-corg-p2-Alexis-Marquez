#include <msp430.h>

#include "led.h"

#include "switches.h"

#include "buzzer.h"

void led_init()

{

  P1DIR |= LEDS;// bits attached to leds are output
  switch_state_changed = 1;  // Force an update
  led_update(); 
}

void led_state_1(){
  P1OUT ^= LED_RED;
}

void led_state_2(){
  P1OUT ^= LED_GREEN;
}

void led_state_3(){
  P1OUT &= ~LED_GREEN;
}

void led_state_4(){
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
}

void led_update(){
  if (switch_state_changed) {
    P1OUT &= ~LEDS;
    if(CURRSTATE == 1)
      led_state_1();
    else if(CURRSTATE == 2)
      led_state_2();
    else if(CURRSTATE == 3)
      led_state_3();
    else if(CURRSTATE == 4)
      led_state_4();
  }
  switch_state_changed = 0;
}
int secondCount = 0;

void control_lights_with_speed(int speed, int secondCount){
    if(secondCount <= 250/speed){
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
      buzzer_set_period(3817);
    }
    else{
      P1OUT &= ~LED_GREEN;
      P1OUT |= LED_RED;
      buzzer_set_period(3396);
    }
 }

void __interrupt_vec(WDT_VECTOR) WDT() /* 250 interrupts/sec */
{
  secondCount++;
  control_lights_with_speed(CURRSTATE, secondCount);
  if(secondCount >= 500/CURRSTATE)
	secondCount = 0;
}
