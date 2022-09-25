#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <string.h>
#define STEP_DELAY 2000

/*
2000  7 RPM
1500  9 RPM
1000 13 RPM
 900 15 RPM
*/

//***************************//
#define PIN1 14
#define PIN2 15
#define PIN3 17
#define PIN4 18
//***************************//

int step = 0;

void loop()
{
	switch (step) {
	case 0:
		gpioWrite(PIN1, PI_LOW);
		gpioWrite(PIN2, PI_LOW);
		gpioWrite(PIN3, PI_LOW);
		gpioWrite(PIN4, PI_HIGH);
		break;
	case 1:
		gpioWrite(PIN1, PI_LOW);
		gpioWrite(PIN2, PI_LOW);
		gpioWrite(PIN3, PI_HIGH);
		gpioWrite(PIN4, PI_HIGH);
		break;
	case 2:
		gpioWrite(PIN1, PI_LOW);
		gpioWrite(PIN2, PI_LOW);
		gpioWrite(PIN3, PI_HIGH);
		gpioWrite(PIN4, PI_LOW);
		break;
	case 3:
		gpioWrite(PIN1, PI_LOW);
		gpioWrite(PIN2, PI_HIGH);
		gpioWrite(PIN3, PI_HIGH);
		gpioWrite(PIN4, PI_LOW);
		break;
	case 4:
		gpioWrite(PIN1, PI_LOW);
		gpioWrite(PIN2, PI_HIGH);
		gpioWrite(PIN3, PI_LOW);
		gpioWrite(PIN4, PI_LOW);
		break;
	case 5:
		gpioWrite(PIN1, PI_HIGH);
		gpioWrite(PIN2, PI_HIGH);
		gpioWrite(PIN3, PI_LOW);
		gpioWrite(PIN4, PI_LOW);
		break;
	case 6:
		gpioWrite(PIN1, PI_HIGH);
		gpioWrite(PIN2, PI_LOW);
		gpioWrite(PIN3, PI_LOW);
		gpioWrite(PIN4, PI_LOW);
		break;
	case 7:
		gpioWrite(PIN1, PI_HIGH);
		gpioWrite(PIN2, PI_LOW);
		gpioWrite(PIN3, PI_LOW);
		gpioWrite(PIN4, PI_HIGH);
		break;
	default:
		gpioWrite(PIN1, PI_LOW);
		gpioWrite(PIN2, PI_LOW);
		gpioWrite(PIN3, PI_LOW);
		gpioWrite(PIN4, PI_LOW);
		break;
	}
}

void help()
{
	printf("    Use this application for reading from Stepper Motor\n");
	printf("    execute format: sudo ./motor [-h][-q] step_delay angle \n");
	printf("    -h - help\n");
	printf("    -q - quiet\n");
}

int main(int argc, char *argv[])
{
	int arg_N = 1;
	int quiet = 0;
	if (argc > 1) {
		if ((strcmp(argv[1], "-h") == 0)) {
			help();
			return 0;
		} else {
			if ((strcmp(argv[1], "-q") == 0)) {
				if (argc < 4) {
					help();
					return (-1);
				}
				quiet = 1;
				arg_N++;
			}
		}
	}
	if (argc < 3) {
		help();
		return (-1);
	}

	if (!quiet)
		printf("\nThe Stepper Motor application was started\n\n");
	int i, rotate_dir, angle;
	int step_delay = STEP_DELAY;

	step_delay = atoi(argv[arg_N]);
	arg_N++;
	angle = atoi(argv[arg_N]);
	if (angle < 0)
		rotate_dir = 0;
	else
		rotate_dir = 1;
	if ((step_delay < 800) || (step_delay > 1000000))
		step_delay = STEP_DELAY;

	if (gpioInitialise() < 0)
		return 1;

	gpioSetMode(PIN1, PI_OUTPUT);
	gpioSetMode(PIN2, PI_OUTPUT);
	gpioSetMode(PIN3, PI_OUTPUT);
	gpioSetMode(PIN4, PI_OUTPUT);

	int intang = abs(angle) * 11.377;
	if (rotate_dir)
		step = 7;
	for (i = 0; i < intang; i++)
		if (rotate_dir) {
			loop();
			step--;
			if (step < 0)
				step = 7;
			gpioDelay(step_delay);
		} else {
			loop();
			step++;
			if (step > 7)
				step = 0;
			gpioDelay(step_delay);
		}
	gpioTerminate();
}