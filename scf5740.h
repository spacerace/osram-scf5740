#ifndef __SCF_H__
#define __SCF_H__

void init_scf5740(void);
void send_serdata(uint8_t byte);
void send_pattern(uint8_t col, uint8_t pattern[7]);
void test_scf5740(void);

/* display connections */
#define set_rst()	PORTD |= (1<<PD6)
#define set_load()	PORTD |= (1<<PD7)
#define set_clk()	PORTB |= (1<<PB5)
#define set_data()	PORTB |= (1<<PB3)

#define rst_rst()	PORTD &= ~(1<<PD6)
#define rst_load()	PORTD &= ~(1<<PD7)
#define rst_clk()	PORTB &= ~(1<<PB5)
#define rst_data()	PORTB &= ~(1<<PB3)

/* display opcodes and addresses */
#define CHAR_ADDR0	0xA0
#define CHAR_ADDR1	0xA1
#define CHAR_ADDR2	0xA2
#define CHAR_ADDR3	0xA3

#define BRT_100		0xE0
#define BRT_53		0xE1
#define BRT_40		0xE2
#define BRT_27		0xE3
#define BRT_20		0xE4
#define BRT_13		0xE5
#define BRT_6		0xE6
#define BRT_0		0xE7

#define POWER_DOWN	0xFF
#define CLEAR		0xC0

#endif