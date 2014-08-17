#include <legacymsp430.h>
#include "timerapwm.h"
#include "i2cslave.h"

#define PWM_PERIOD 128
#define PWM_PERIOD_STEPS 10
#define PWM_PERIOD_STEP (PWM_PERIOD / PWM_PERIOD_STEPS)

void transmitIsr(void)
{
	//Send the status of port one out
	UCB0TXBUF = P1OUT;
}

void receiveIsr(void)
{
	//Set port A, based on what's being received from the master
	P1OUT = UCB0RXBUF;
	TACCR1 = PWM_PERIOD_STEP * UCB0RXBUF;
}

int main(void)
{
	//Stop watchdog timer
	WDTCTL = WDTHOLD + WDTPW;
	P1DIR = BIT2 | BIT0;
	init_i2c_slave(0x32,transmitIsr, receiveIsr);
	init_pwm(PWM_PERIOD, 0, BIT2); //Pin 2, port of port A. Initially off
	__bis_SR_register(GIE + CPUOFF);
	return 0;
}
