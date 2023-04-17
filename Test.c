#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void read_command(char * command);
void Gcommand();
void Wcommand(char * x, char * y, char * z);
void Scommand(char * x, char * y);

int main(void)
{
    char * c = "G";
	char * w = "W,1,2,3";
	char * s = "S,1,2";
    read_command(c);
	printf("\n");
	read_command(w);
	printf("\n");
	read_command(s);
    return 0;
}


void read_command(char * command) {
	char * buffer = (char*)malloc(strlen(command) + 1);
	strcpy(buffer, command);
	char delim[] = ",";
	char * token = strtok(buffer, delim);
	char * temp[4];
	int num = 0;
	if(strcmp(token, "G") == 0){
		token = strtok(NULL, delim);
		Gcommand();
		printf("G");
	}else if(strcmp(token, "W") == 0){
		token = strtok(NULL, delim);
		while(token != NULL && num < 4){
			temp[num] = (char *)malloc(strlen(token)+1);
			strcpy(temp[num], token);
			num++;
			token = strtok(NULL, delim);
		}
		num = 0;
		Wcommand(temp[0], temp[1], temp[2]);
		for(int i = 0; i < 3; i++){
			free(temp[i]);
		}
	}else if(strcmp(token, "S") == 0){
		token = strtok(NULL, delim);
		while(token != NULL){
			temp[num] = (char *)malloc(strlen(token)+1);
			strcpy(temp[num], token);
			num++;
			token = strtok(NULL, delim);
		}
		num = 0;
		Scommand(temp[0], temp[1]);
		for(int i = 0; i < 2; i++){
			free(temp[i]);
		}
	}
	free(command);
}

void Gcommand(){
	//get_adc_value();
}

void Wcommand(char * c, char * f, char * r){
	printf("W");
	printf("\n");
	int DAC = atoi(c);
	int FREQ = atoi(f);
	int WAVE = atoi(r);
	printf("%d\n", DAC);
	printf("%d\n", FREQ);
	printf("%d\n", WAVE);
}

void Scommand(char * c, char * v){
	printf("S");
	printf("\n");
	int DAC = atoi(c);
	float VOLT = atof(v);
	printf("%d\n", DAC);
	printf("%f\n", VOLT);
}