#include "i2c.h"

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

const uint8_t MAX_RETRIES = 5;

void i2c_init(void) {

	// Only configure the clock
	TWBR = 72;	// TWBR = ( (cpu_freq / scl_freq) - 16 ) / 2 / 4^twps
}

void i2c_send(uint8_t data) {

	uint8_t retry_count = 0;

	while ( retry_count < MAX_RETRIES ) {

		TWDR = data;
		TWCR = (1 << TWINT) | (1 << TWEN);
		i2c_wait();

		if ( TW_MT_DATA_ACK == TW_STATUS ){
			break;
		}

		++retry_count;
	}
}

void i2c_start(void) {

	for (uint8_t i = 0; i < MAX_RETRIES; ++i) {

		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
		i2c_wait();

		if ( TW_START == TW_STATUS ){
			break;
		}
	}

	for (uint8_t i = 0; i < MAX_RETRIES; ++i) {

		TWDR = ADDRESS_W;
		TWCR = (1 << TWINT) | (1 << TWEN);
		i2c_wait();

		if ( TW_MT_SLA_ACK == TW_STATUS ){
			break;
		}
	}

	return;
}

void i2c_stop(void) {

	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

void i2c_wait (void ) {

	loop_until_bit_is_set(TWCR, TWINT);
}

void send_over_twi(uint8_t data) {

	i2c_start();
	i2c_send(data);
	i2c_stop();
}
