/*
 * main.h
 *
 * Created: 4/13/2023 9:13:17 PM
 *  Author: kaili
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum Commands {
	NONE = 0,
	ADCREAD = 1,
	DACOUTPUT = 2,
	GENERATE = 3
} Commands;


char * get_adc_value();
void print_adc_value(char * buffer);
void setup();
int main(void);
void read_command(char * command);
void set_dac_output(uint8_t dac, float voltage);
void gen_wave_form(uint8_t dac, uint8_t freq, uint8_t cycles); 

#endif /* MAIN_H_ */