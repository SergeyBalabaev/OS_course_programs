#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include "rotary_encoder.h"

#define GPIO_PIN_A 27
#define GPIO_PIN_B 26
int quiet = 0;
void help()
{
	printf("    Use this application for reading from encoder\n");
	printf("    execute format: ./light_detect [-h][-q] \n");
	printf("    return: increment value, when rotate right\n");
	printf("            decrement value, when rotate left\n");
	printf("    -h - help\n");
	printf("    -q - quiet\n");
}

void callback(int way)
{
	static int pos = 0;
	pos += way;
	if (!quiet)
		printf("angle increment:=%d\n", pos);
	if (quiet)
		printf("%d\n", pos);
}

int main(int argc, char *argv[])
{
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
	if (!quiet)
		printf("\nThe encoder application was started\n\n");

	Pi_Renc_t *renc;
	if (gpioInitialise() < 0)
		return 1;
	renc = Pi_Renc(GPIO_PIN_A, GPIO_PIN_B, callback);
	sleep(300);
	Pi_Renc_cancel(renc);
	gpioTerminate();
}
