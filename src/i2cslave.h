/**
        A support library for enabling i2c slave mode on the msp430g2553 (or simular series of devices).
	Please note, if you are using this on the texas launchpad, you must remove the header next to
	P1.6.
*/

#ifndef I2CSLAVE_H
#define I2CSLAVE_H

#include <legacymsp430.h>

/**
	This initializes USCI to operate as an i2c slave device.
	addr - The address associated with this slave
	transmitIsr - Callback handler for transmitting data out from the slave to the master
	receiveIsr - Callback handler for receiving data from the master. 
*/
void init_i2c_slave(unsigned char addr, void (* transmitIsr)(void), void (* receiveIsr)(void));

/**
	Configures the output pins for i2c
*/
void i2c_config_gpio();

#endif /*I2CSLAVE_H*/
