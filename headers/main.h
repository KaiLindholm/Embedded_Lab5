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
#endif /* MAIN_H_ */