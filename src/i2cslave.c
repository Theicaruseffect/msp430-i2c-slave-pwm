#include <legacymsp430.h>
#include "timerapwm.h"

#define I2C_SCL_PIN BIT6
#define I2C_SDA_PIN BIT7

static void (* transmit_isr) (void);
static void (* receive_isr) (void);

void init_i2c_slave(unsigned char addr, void (* transmitIsr) (void), void (* receiveIsr) (void))
{
	transmit_isr = transmitIsr;
	receive_isr = receiveIsr;
	//Stop USCI's logic (state machine)
	UCB0CTL1 = UCSWRST;
	UCB0CTL1 = UCSSEL_2; //SMCLK
	UCB0CTL0 = UCMODE_3 | UCSYNC; //I2c Mode, Sync mode
	UCB0I2COA = addr; //Address of this slave
	//Configure ports for i2c
	P1SEL |= I2C_SCL_PIN | I2C_SDA_PIN;
	P1SEL2 |= I2C_SDA_PIN | I2C_SCL_PIN;
	//Start USCI's logic (state machine)
	UCB0CTL1 &= ~UCSWRST;
	//Set receive and transmit interrupt vectors
	IE2 |= UCB0TXIE | UCB0RXIE; // Enable TX interrupt
	UCB0I2CIE |= UCSTTIE;
}

interrupt(USCIAB0TX_VECTOR) usci_i2c_data_isr(void)
{
	if (IFG2 & UCB0RXIFG) { //Receiving data
//		P1OUT = UCB0RXBUF;
		receive_isr();
	} else {//Sending data
//		UCB0TXBUF = P1OUT;
		transmit_isr();
	}
}


// USCI_B0 Start ISR
interrupt(USCIAB0RX_VECTOR) usci_i2c_start_isr(void)
{
    UCB0STAT &= ~UCSTTIFG; // Clear start condition int flag
}
