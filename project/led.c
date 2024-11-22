#include <msp430.h>

#include "led.h"

#include "switches.h"

#include "buzzer.h"

#include <stdlib.h>

void led_init()

{

  P1DIR |= LEDS;// bits attached to leds are output
  switch_state_changed = 1;  // Force an update 
}
int secondCount = 0;
int tempo = 0;
int initialTone = 3817;
int step = 250/2;
int semitone = 0;
int currentTone = 3817;
int random_number = 0;
int random_tone = 0;
void play_scale(int secondCount){
  semitone =(int)( currentTone * 1.0595);
  if(secondCount < step){
    currentTone = initialTone;
  }
  else if(secondCount == step || secondCount == step *6 || secondCount==step*2 || secondCount == step*4 || secondCount== step*5){
    currentTone += 2*semitone;
  }
  else if(secondCount == step*3 || secondCount==step*7){
    currentTone += semitone;
  }
  buzzer_set_period(currentTone);
}
void play_scale_min(int secondCount){
  semitone= (int)(currentTone * 1.0595);
  if(secondCount<step){
    currentTone = initialTone;
  }
  else if(secondCount == step || secondCount == step*3 || secondCount == step*4 || secondCount == step*6 || secondCount == step *7){
    currentTone += 2*semitone;
  }
  else if(secondCount == step *2|| secondCount == step*5){
    currentTone += semitone;
  }
  buzzer_set_period(currentTone);
}
void control_lights_with_speed(int speed, int secondCount){
  if(secondCount <= 250/speed){
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
  }
    else{
      P1OUT &= ~LED_GREEN;
      P1OUT |= LED_RED;
    }
}

void __interrupt_vec(WDT_VECTOR) WDT() /* 250 interrupts/sec */
{
  tempo++;
  secondCount++;
  step = 250/CURRSTATE;
  control_lights_with_speed(CURRSTATE, secondCount);
  if(CURRSTATE == 3){ play_scale_min(tempo*random_tone);}
  else if(CURRSTATE == 1){ play_scale_min(tempo);random_number = 8;}
  else if(CURRSTATE == 4){ play_scale(tempo*random_tone);}
  else if(CURRSTATE == 2){ play_scale(tempo);random_number = 4;}
  random_tone = 1+(rand()%4);
  if(secondCount >= 500/CURRSTATE){
    secondCount = 0;
  }
  if(tempo > 250*random_number){
    tempo = 0;
    random_number = 1+(rand()%3);
  }
}
