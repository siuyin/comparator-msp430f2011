// comparator-msp430f2011 exercises the comparator

#include <msp430f2011.h>

void setup_ports(void);
void setup_comparator(void);
void sense_comparator_output(void);

void main(void){
	setup_ports();
	setup_comparator();
			
	while(1) {
		sense_comparator_output();
	}
}

void setup_ports(void){
	P1OUT = 0;
	P1DIR = (0xff & ~BIT5);	// P1.5/CA5 is an input
	P2OUT = 0;
	P2DIR = 0xff;
}

void setup_comparator(void){
	CACTL2 |= (P2CA3 + P2CA1 + CAF);	// select comparator CA5 input, turn on output filter
	CAPD |= CAPD5;			// disable digital input buffer for CA5
	CACTL1 |= (CAREF_2 +	// comparator+ connected to 0.5 Vcc
		CAON);				// turn on the comparator
}

void sense_comparator_output(void){
	if (CACTL2 & CAOUT) {	// if comparator output is high
		P1OUT |= BIT0;	// turn on P1.0; red LED
	} else {
		P1OUT &= ~BIT0;	// turn off red LED
	}
}
