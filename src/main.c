/*
 * EmbeddedLab5.c
 *
 * Created: 4/11/2023 12:12:04 PM
 * Author : Kai Lindholm & James Ostrowski
 */ 
#include "config.h"
#define F_CPU 16000000UL

#define __DELAY_BACKWARD_COMPATIBLE__
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "i2cmaster.h"
#include "my_uart.h"
#include "main.h"

#define MAX518_ADDR 0b01011000
#define DAC0 0x00
#define DAC1 0x01

void setup(uint32_t scl_clock, uint32_t baud){
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)| (1<<ADEN);
	ADMUX = 0b00000000;		// clear ADMUX for ADC0 pin 
	ADMUX |= (1<<REFS0);	
	i2c_init();

}

int main(void) {
	char str[] = "Started!";
	setup(100000, 9600);
	uart_init(9600);
	sei();

	//get_adc_value();  // initialize adc for faster future computations. 

	uart_send_string(str);
	uart_send_byte('\n');

	while (1) {	
		if(uart_string_complete()){
			read_command(uart_get_command());
		}
	}
}

char * get_adc_value(){
	ADCSRA |= (1<<ADSC);      // enable a single conversion
	
	while (!(ADCSRA & (1<<ADIF))); // wait for the conversion to be completed		
	
	float result = (ADC * 5.0)/1024;	// convert to float 
		
	char * buffer = (char* ) malloc(6 * sizeof(char));	
	dtostrf(result, 3, 2, buffer); // convert float to string 

	ADCSRA |= (1<<ADIF);		// reset AD complete flag for next conversion. 
	
	return buffer; 
}

void print_adc_value(char * buffer){
	uart_send_string("V = ");
	uart_send_string(buffer);
	uart_send_byte('\n');
	
	free(buffer); 
}
void read_command(char * command) {
	char delim[] = ",";  // set delimiter

	char * token = strtok(command, delim);
	if(token[1] == 'G'){ //check commands
		print_adc_value(get_adc_value());
	} else if(token[1] == 'W') { // get W parameters
		uint8_t dac = atoi(strtok(NULL, delim));
		uint8_t freq = atoi(strtok(NULL, delim));
		uint8_t cycles = atoi(strtok(NULL, delim));
	
		gen_wave_form(dac, freq, cycles);
	} else if(token[1] == 'S') { // get S parameters
		uint8_t dac = atoi(strtok(NULL, delim));
		float voltage = atof(strtok(NULL, delim));
		set_dac_output(dac, 51*voltage);
	} else {
		uart_send_byte('X'); //if no correct commands entered
	}
	
	free(command);
}

void set_dac_output(uint8_t dac, uint8_t voltage){
	if(dac != 1 && dac != 0){
		uart_send_string("DAC must either be 0 or 1");
	}
	
	i2c_start(MAX518_ADDR | I2C_WRITE);     // send start signal to MAX518
	i2c_write(dac);                        // write to DAC0
	i2c_write(voltage);                      // write voltage to dac0
	i2c_stop();
}

void gen_wave_form(uint8_t dac, uint8_t freq, uint8_t cycles){
	uart_send_byte('W');
	int i = 0; 
	double dt = 1000000.0 / freq / 64 - 300; //delay computation

	while( i < cycles){ //iterate through cycles
		for(int i = 0; i < 64; ++i){ //move through waveform
			uint8_t voltage = wave_form[i];
			set_dac_output(dac,voltage); //set voltage
			_delay_us(dt);

		}
		++i;
	}
}