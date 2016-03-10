#include <avr/io.h>
#include <util/delay.h>

#include "scf5740.h"

/* connection: PD6 = RST, PD7 = LOAD, PB5 = CLK, PB3 = DATA */
void init_scf5740() {
	DDRD |= (1<<PD6);	// RESET as output
	DDRD |= (1<<PD7);	// LOAD as output
	DDRB |= (1<<PB5);	// CLK as output
	DDRB |= (1<<PB3);	// DATA as output
	
	rst_rst();	// put chip in reset state
	
	set_load();	// defaults, LOAD=1  CLK=1  DATA=0
	set_clk();
	rst_data();
	
	set_rst();	// release reset state
	
	return;
}

void send_pattern(uint8_t col, uint8_t pattern[7]) {
	uint8_t i;
	switch(col) {
		case 3:
			send_serdata(CHAR_ADDR3);
			break;
		case 2:
			send_serdata(CHAR_ADDR2);
			break;
		case 1:
			send_serdata(CHAR_ADDR1);
			break;
		case 0:
		default:
			send_serdata(CHAR_ADDR0);
			break;
	}
	
	for(i = 0; i < 7; i++) {
		send_serdata(pattern[i]);
	}
}

void send_serdata(uint8_t byte) {
	uint8_t i;
	
	set_clk();	// data is read on falling edge, so we need H in waiting state
	rst_load();	// selects the chip
	
	for(i = 0; i < 8; i++) {
		if(byte & (1<<i)) {	// if bit number i is set,
			set_data();	// set data line ...
		} else {
			rst_data();	// ... or not
		}
		rst_clk();		// we have set data
		set_clk();		// so do one clock cycle
	}
	
	set_load();	// deselects the chip

}
