/**
	A simple example that routes Timer_A to pin 1.6.
	to generate a PWM signal. Compiled on the msp430g2553.
*/

#include "timerapwm.h"

void init_pwm(unsigned char period, unsigned char duty_cycle, unsigned char output_bit)
{
	P1DIR |= output_bit; // Pin 1.6 output
	P1SEL |= output_bit; // Route Timer_A to P1.6
	//ACLK, Up mode
	TACTL = TASSEL_1 | MC_1;
	TACCR0 = period;
	TACCTL1 = OUTMOD_7; //Reset / Set (see page 364 of the user guide)
	TACCR1 = duty_cycle;
}
