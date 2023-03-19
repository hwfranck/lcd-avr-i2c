#include "lcd.h"
#include "i2c.h"

#include <avr/io.h>
#include <util/delay.h>

void lcd_clear(void) {

	lcd_command_write(DISPLAY_CLEAR, BIT_MODE_4);
	_delay_ms(2); //	more than 1.52ms
}

// The first few calls happen during initialization while the lcd is still in 8-bit mode
void lcd_command_write(uint8_t command, uint8_t mode) {

	if (mode == BIT_MODE_8) {
		lcd_send(command);
	} else if (mode == BIT_MODE_4) {
		uint8_t highnib = (command & 0xF0);
		uint8_t lownib  = ( (command << 4) & 0xF0 );

		lcd_send(highnib);
		lcd_send(lownib);
	}
	// ignore mal-formed calls
}

void lcd_data_write(uint8_t data) {

	uint8_t highnib = (data & 0xF0);
	uint8_t lownib  = ( (data << 4) & 0xF0 );

	lcd_send(highnib | RS_DATA);
	lcd_send(lownib  | RS_DATA);
}

void lcd_enable(uint8_t data) {

	send_over_twi(data | (1 << ENABLE_BIT));
	_delay_us(1);

	send_over_twi(data & ~(1 << ENABLE_BIT));
	_delay_us(50);
}

void lcd_init(void) {

	//	implement page 46 of the datasheet
	_delay_ms(50); // more than 40ms
	lcd_command_write(0x03 << 4, BIT_MODE_8);
	_delay_us(4500); // more than 4.1ms
	lcd_command_write(0x03 << 4, BIT_MODE_8);
	_delay_us(150);	// more than 100us
	lcd_command_write(0x03 << 4, BIT_MODE_8);

	lcd_command_write(0x02 << 4, BIT_MODE_8);

	lcd_command_write(FUNCTION_SET_4B_2L, BIT_MODE_4);
	lcd_command_write(DISPLAY_OFF, BIT_MODE_4);
	lcd_clear();
	lcd_command_write(ENTRY_MODE_SET, BIT_MODE_4);	//
	lcd_command_write(DISPLAY_ON, BIT_MODE_4);

	//	lcd_print("Display ready.");	// can be removed
}

void lcd_load_pattern(uint8_t index_pattern) {

	if (index_pattern > 15) {
		return;
	}

	lcd_data_write(index_pattern);
}

void lcd_move_cursor(uint8_t line, uint8_t col) {

	if ( (line > 1) || (col > 15) ) {
		return;
	}

	// The first line starts at 0x00 and the second one at 0x40
	// The column index is between 0x00 and 0x0F

	uint8_t ddram_addr = DDRAM_ADDRESS_SET | col;
	ddram_addr += line*0x40;

	lcd_command_write(ddram_addr, BIT_MODE_4);
}

void lcd_print(char msg[]){

	while (*msg) {

		lcd_data_write(*msg++);
	}
}

void lcd_print_nl (void) {

	lcd_move_cursor (1, 0);
}

void lcd_save_pattern(char pattern[], size_t size, uint8_t addr_offset) {

	if (size / sizeof(char) != 8) {
		return;
	}

	// Set cgram address and send cgram data
	lcd_command_write(0x40 + addr_offset*8, 0);

	for (uint8_t i = 0; i < 7; ++i) {

		lcd_data_write(pattern[i]);
	}

	//	force empty space for cursor line
	lcd_data_write(0x00);
}

void lcd_send (uint8_t data) {

	send_over_twi(data | BT_DATA);
	lcd_enable(data | BT_DATA);
}
