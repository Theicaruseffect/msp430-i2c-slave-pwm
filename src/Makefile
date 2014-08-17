all:
	msp430-gcc -mmcu=msp430g2553 main.c timerapwm.c i2cslave.c -o firmware
	@echo "Copying to MCU"
	mspdebug rf2500 "prog firmware" "run"
clean:
	rm firmware
