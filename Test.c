#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 1024

void read_command(char * command);
void Gcommand();
void Wcommand(uint8_t dac, uint8_t freq, uint8_t cycles);
void Scommand(uint8_t dac, float voltage);
uint8_t read_wave_form_file(char * file_path);
uint8_t read_wave_form_file(char * file_path){
	FILE* fp; 
	fp = fopen(file_path, "r"); // read from file_path

	if( fp == NULL ) { 		// file path does not exist
		return 1; 
	}

	fseek(fp, 0, SEEK_END);		// go to the end of the file
	uint8_t size = ftell(fp);	// find out the size of the buffer needed. 
	char * buffer = (char * ) malloc((size + 1) * sizeof(char));
	printf("%d\n", size);
	//uint8_t * wave_form = (uint8_t * ) malloc((size + 1) * sizeof(uint8_t));
	uint8_t wave_form[64] = {0};
	fseek(fp, 0, SEEK_SET);	// go back to start of file. 
	uint8_t i = 0; 
	while(!feof(fp) ){
		fgets(buffer, SIZE, fp); 
		char * tokens = strtok(buffer, ",");
		while(tokens != NULL) {
			wave_form[i] = atoi(tokens); 
			printf("Voltage (%d): %d V\n", (i+1), wave_form[i]);
			tokens = strtok(NULL, ",");

			++i; 
		}
	}
	

	//fclose(fp);
	return 0; 
}


int main(void)
{
    if(read_wave_form_file("sin_table.csv")){
		printf("ERR\n");
		return 1; 
	}

    return 0;
}


void read_command(char * command) {
	char delim[] = ",";
	char * token = strtok(command, delim);
	if(strcmp(token, "G") == 0){
		token = strtok(NULL, delim);
		Gcommand();
		printf("G\n");
	}else if(strcmp(token, "W") == 0){
		uint8_t dac = atoi(strtok(NULL, delim));
		uint8_t freq = atoi(strtok(NULL, delim));
		uint8_t cycles = atoi(strtok(NULL, delim));

		Wcommand(dac, freq, cycles);
	}else if(strcmp(token, "S") == 0){
		uint8_t dac = atoi(strtok(NULL, delim));
		float voltage = atof(strtok(NULL, delim));
		Scommand(dac, voltage);
	}
}

void Gcommand(){
	//get_adc_value();
}

void Wcommand(uint8_t dac, uint8_t freq, uint8_t cycles){
	printf("W: ");
	printf("%d ", dac);
	printf(" %d ", freq);
	printf(" %d\n", cycles);
}

void Scommand(uint8_t dac, float voltage){
	printf("S: ");
	printf(" %d ", dac);
	printf(" %f", voltage);
}