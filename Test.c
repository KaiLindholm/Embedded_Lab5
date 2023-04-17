#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void read_command(char * command);
void Gcommand();
void Wcommand(uint8_t dac, uint8_t freq, uint8_t cycles);
void Scommand(uint8_t dac, float voltage);

int main(void)
{
    char c[2] = "G\0";
	char w[8] = "W,1,2,3\0";
	char s[6] = "S,1,2\0";
    read_command(c);
	printf("\n");
	read_command(w);
	printf("\n");
	read_command(s);
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