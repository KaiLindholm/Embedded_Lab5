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

static uint8_t wave_form[64] = {128,141,153,165,177,188,199,209,219,227,234,241,246,250,254,255,255,255,254,250,246,241,234,227,219,209,199,188,177,165,153,141,128,115,103,91,79,68,57,47,37,29,22,15,10,6,2,1,0,1,2,6,10,15,22,29,37,47,57,68,79,91,103,115};
char * get_adc_value();
void print_adc_value(char * buffer);
void setup();
int main(void);
void read_command(char * command);
void set_dac_output(uint8_t dac, uint8_t voltage);
void gen_wave_form(uint8_t dac, uint8_t freq, uint8_t cycles); 

#endif /* MAIN_H_ */