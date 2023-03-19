#pragma once

#include <stdint.h> // uint8_t
#include <stddef.h> // size_t

//	D7 D6 D5 D4 BT  E RW RS	:= lcd pins
//	P7 P6 P5 P4 P3 P2 P1 P0	:= pcf8574 pins

// These are DB7-DB0 values
#define DDRAM_ADDRESS_SET	0x80	// 1000 0000 := set ddram address
#define DISPLAY_CLEAR		0x01	// 0000 0001
#define DISPLAY_OFF			0x08 	// 0000 1000
#define DISPLAY_ON			0x0F 	// 0000 1111 := display on, cursor ON, blinking ON
#define ENTRY_MODE_SET		0x06 	// 0000 0110 := increment, shift off
#define FUNCTION_SET_4B_2L	0x28	// 0010 1000 := 4-bit, 2 lines, 5x8 dot character font
#define RETURN_HOME			0x02	// 0000 0010

#define BIT_MODE_4 0
#define BIT_MODE_8 1

#define ENABLE_BIT 2

#define RS_DATA (1 << 0)
#define BT_DATA (1 << 3)

void lcd_clear(void);
void lcd_command_write(uint8_t command, uint8_t bitmode);
void lcd_data_write(uint8_t data);
void lcd_enable(uint8_t data);
void lcd_init(void);
void lcd_load_pattern(uint8_t index_pattern);
void lcd_move_cursor(uint8_t line, uint8_t col);
void lcd_print(char msg[]);
void lcd_print_nl(void);
void lcd_save_pattern(char pattern[], size_t size, uint8_t addr_offset);
void lcd_send(uint8_t data);
