#include <util/delay.h>

#include "i2c.h"
#include "lcd.h"

int main (void) {

	i2c_init();
	lcd_init();

	//	Battery components
	char bat_neg_full[] = {0x1F, 0x10, 0x17, 0x17, 0x17, 0x10, 0x1F, 0x00};

	char bat_mid_empty[] = {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00};
	char bat_mid_full[] = {0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x00};

	char bat_pos_empty[] = {0x1E, 0x02, 0x03, 0x03, 0x03, 0x02, 0x1E, 0x00};

	lcd_save_pattern(bat_neg_full, 0);
	lcd_save_pattern(bat_mid_empty, 1);
	lcd_save_pattern(bat_mid_full, 2);
	lcd_save_pattern(bat_pos_empty, 3);

	//	Clear display and reset cursor position
	lcd_clear();

	lcd_print("Battery Level :");

	lcd_print_nl();

	lcd_load_pattern(0);
	lcd_load_pattern(2);
	lcd_load_pattern(2);
	lcd_load_pattern(1);
	lcd_load_pattern(3);

	lcd_print("  62% Full");

	while (1) {
		// This can be empty
	}

	return 0;
}
