/**
        A simple example that routes Timer_A to particular (supported) output pin.
        to generate a PWM signal. Compiled on the msp430g2553.
*/

#ifndef TIMERAPWM_H
#define TIMERAPWM_H

#include <legacymsp430.h>

/**
	PWM config for timer A. By default, this uses ACLK as an input clock source.
	period - The period of the pulse
	duty_cycle - The duty_cycle of the pulse
	output_bits - Where to route timer A to.
*/
void init_pwm(unsigned char period, unsigned char duty_cycle, unsigned char output_bit);

#endif /*TIMERAPWM_H*/
