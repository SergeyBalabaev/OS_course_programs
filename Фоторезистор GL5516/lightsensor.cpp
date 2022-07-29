#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./Adafruit_ADS1X15_RPi/Adafruit_ADS1015.h"

#define err(mess) { fprintf(stderr,"Error: %s.", mess); exit(1); }

//***************************//
#define ADC_PIN 0         //GPIO PIN TRIG
//***************************//
#define THRESHOLD 5000

Adafruit_ADS1115 ads;

void help() {

	printf("    Use this application for reading from light sensor\n");
	printf("    execute format: ./light_detect [-h][-q] TIME \n");
	printf("    return: ADC value, where 0 - minimum light, 65535 - maximum light\n");
	printf("    TIME - pause between writing in ms\n");
	printf("    -h - help\n");
	printf("    -q - quiet\n");
}


int main(int argc, char* argv[])
{
	int quiet = 0;
	if (argc <= 1) {
		help();
		return -1;
	}
	else {
		if ((strcmp(argv[1], "-h") == 0)) {
			help();
			return 0;
		}
		else {
			if ((strcmp(argv[1], "-q") == 0)) {
				quiet = 1;
			}
		}
	}
	if (!quiet) printf("\nThe lightsensor application was started\n\n");
	ads.setGain(GAIN_TWO);
	ads.begin();
	uint16_t adc0;
	int argument = 1;
	if (quiet) argument++;
	uint16_t pause_time = atoi(argv[argument]);
	while (true) {
		adc0 = ads.readADC_SingleEnded(ADC_PIN);
		if (quiet) printf("%d\n", adc0);
		else printf("ADC: %d\n", adc0);
		usleep(pause_time * 1000);
	}
}