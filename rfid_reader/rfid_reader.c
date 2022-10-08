#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include "MFRC522.h"

int debug = 0;

void help()
{
	printf("    Use this application for reading from rangefinder\n");
	printf("    execute format: ./range TIME \n");
	printf("    return: length in cm\n");
	printf("    TIME - pause between writing in ms\n");
	printf("    -h - help\n");
	printf("    -q - quiet\n");
}

int main(int argc, char *argv[])
{
	int quiet = 0;
	if (argc > 1) {
		if ((strcmp(argv[1], "-h") == 0)) {
			help();
			return 0;
		} else {
			if ((strcmp(argv[1], "-q") == 0)) {
				quiet = 1;
			}
		}
	}

	uint8_t mode, bits;
	int status;
	unsigned char backBits;
	unsigned char *uid;
	unsigned char blockno;
	char *next;


	MFRC522_Init(0);

	while ((status = MFRC522_Request(PICC_REQIDL, &backBits)) != MI_OK)
		usleep(500);

	if (status == MI_OK)
		if (!quiet)
			printf("Card detected\n");

	status = MFRC522_Anticoll(&uid);

	if (status == MI_OK) {
		// print UID
		printf("%02x %02x %02x %02x\n", uid[0], uid[1], uid[2], uid[3]);
	}
}
