/*
	Code to exercise Gen2 ARGB for oscilloscope measurements.

	Note that this is not a complete implementation
	of a Gen2 ARGB controller, but rather for reference only.
	cpldcpu 2023
*/

#include <atmel_start.h>
#include <util\delay.h>
#include <stdio.h>
#include "light_ws2812.h"

/*
	Output pin is D8 - PB0

*/

//uint8_t data[]={0x55,0x00,0xAA};
uint8_t data[]={0x40,0x00,0x00};
uint8_t data1[]={0x00,0x40,0x00};
uint8_t data2[]={0x00,0x08,0x0};
uint8_t data3[]={0x00,0x80,0x0};
uint8_t white[]={0xff,0xff,0xff};
uint8_t black[]={0,0,0x00};
uint8_t key[]={0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00,0x00,0x20,0x00};
uint8_t cols[]={0x01,0x00,0x0,0,0x0,0,0,0,0x0,0x0,0,0,0,0x0,0};

uint8_t command[]={0x04};
	

uint8_t config1[]={0x80,0xc0,0x80};
uint8_t config2[]={0x80,0x00,0x20};
	

uint8_t current1[]={0xff,0xff};

void ARGB2_sendcommand(uint8_t cmd) {
	
		uint8_t out1=PORTB|1;
		uint8_t out0=PORTB&~1;
	
		PORTB=out1;
		_delay_us(40);
		PORTB=out0;
		_delay_us(12);

		command[0]=cmd;
		ws2812_sendarray(command,1);
}

uint8_t ARGB2_receivecommandresponse(void) {

		uint8_t out1=PORTB|1;
		uint8_t out0=PORTB&~1;
		uint8_t outon =DDRB|1;
		uint8_t outoff=DDRB&~1;

		DDRB=outoff;
		PORTB=out0;
		_delay_us(300);
		DDRB=outon;
		
		return 0;	
}

void ARGB2_initconfigsend(void) {

	uint8_t out1=PORTB|1;
	uint8_t out0=PORTB&~1;
	uint8_t outon =DDRB|1;
	uint8_t outoff=DDRB&~1;

	PORTB=out1;						// send 20�s pulse + 300�s reset through chain  -> next data is interepreted as key/command and RGB latch is not updated
	_delay_us(20);
	PORTB=out0;
	_delay_us(300);
}

void ARGB2_sendconfig(uint8_t *configword,uint8_t numberofleds) {
	
	ARGB2_initconfigsend();
	
	for (uint8_t i=0; i<numberofleds; i++) {
		ws2812_sendarray(configword,3);		
	}
		_delay_us(300);
}

uint8_t ARGB2_readoutstring(void) {

	uint8_t out1=PORTB|1;
	uint8_t out0=PORTB&~1;
	uint8_t outon =DDRB|1;
	uint8_t outoff=DDRB&~1;

	PORTB=out1;						// Initiate readout
	_delay_us(20);
	PORTB=out0;
	_delay_us(10);
	PORTB=out1;
	_delay_us(50);
	PORTB=out0;
	DDRB=outoff;
	_delay_us(600);
	DDRB=outon;
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
		
	/* Replace with your application code */

	
	while (1) {
//

		//DDRB|=_BV(PB1);
		//PORTB|=_BV(PB1);
		

		_delay_ms(250);

		uint8_t out1=PORTB|1;
		uint8_t out0=PORTB&~1;
		uint8_t outon =DDRB|1;
		uint8_t outoff=DDRB&~1;
/*		
		for (uint8_t i=0; i<12; i++) {
			ws2812_sendarray(black,3);			
		}
		*/


/*
		ws2812_sendarray(data,3);
		ws2812_sendarray(data1,3);
		_delay_ms(50);

		ws2812_sendarray(data1,3);
		ws2812_sendarray(data,3);
		_delay_ms(50);
*/
/*
		ARGB2_sendcommand(0x20);		// Reset all sub-strings
		ARGB2_receive();

		ARGB2_sendcommand(0x11);		// Assign substring address 1 to random free substring
		ARGB2_receive();
		ARGB2_sendcommand(0x31);		// Ping substring 1
		ARGB2_receive();
*/
/*	
		ARGB2_sendcommand(0x13);		// Assign substring address 2 to random free substring
		ARGB2_receive();
		ARGB2_sendcommand(0x33);		// Ping substring 2
		ARGB2_receive();
*/		

/*
		ARGB2_sendcommand(0x41);		// Select substring 1 for data transfer
		ws2812_sendarray(cols,5*3);
		_delay_us(300);

		ARGB2_sendcommand(0x41);		// Select substring 1 for data transfer
*/

		ws2812_sendarray(cols,5*3);
		_delay_us(300);

		ARGB2_readoutstring();
	
		ARGB2_sendconfig(config1,5);	
	
		ARGB2_readoutstring();

			
//		ARGB2_sendcommand(0x41);		// Select substring 1 for data transfer
	
		ARGB2_sendconfig(config2,5);
		
//		ARGB2_sendcommand(0x41);		// Select substring 1 for data transfer

		ARGB2_readoutstring();


//		_delay_ms(50);
		
	}
}
