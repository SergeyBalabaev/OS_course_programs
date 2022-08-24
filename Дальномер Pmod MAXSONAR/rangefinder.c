#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define SERIALPORT "/dev/ttyAMA1"

typedef enum
{
	INCH = 0,
	CM,
	MM
} UNIT;

uint16_t getUnits(uint16_t data, UNIT unit)
{
	float output;
	switch (unit)
	{
	case INCH:
		output = data;
		break;
	case CM:
		output = 2.54 * data;
		break;
	case MM:
		output = 2.54 * data * 10;
		break;
	default: // default to inches
		output = data;
		break;
	}

	return output;
}

uint16_t getDistance(int serial_port, UNIT unit)
{
	int i = 0;
	uint16_t data = 0;
	char rgbTemp[3];
	if (serialGetchar(serial_port))
	{
		if (serialGetchar(serial_port) == 'R')
		{
			for (i = 0; i < 3; i++)
			{
				while (!serialDataAvail(serial_port))
					;
				rgbTemp[i] = serialGetchar(serial_port);
			}
			if (serialGetchar(serial_port) == 13)
			{ // check for return character
				data = atoi(rgbTemp);
			}
			else
			{
				data = 0; // packet error
			}
		}
		else
		{
			data = 0; // packet error
		}
	}
	return getUnits(data, unit);
}

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
	int sl = 100;
	if (argc == 2)
	{
		if ((strcmp(argv[1], "-h") == 0))
		{
			help();
			return 0;
		}
		else
			sl = atoi(argv[1]);
	}
	else if (argc == 3)
	{
		if ((strcmp(argv[1], "-q") == 0))
		{
			quiet = 1;
			sl = atoi(argv[2]);
		}
		else
		{
			help();
			return 0;
		}
	}
	else
	{
		help();
		return 0;
	}

	if (!quiet)
		printf("\nThe rangefinder application was started\n\n");
	int serial_port;
	char dat;
	if ((serial_port = serialOpen(SERIALPORT, 9600)) < 0) /* open serial port */
	{
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		return 1;
	}

	if (wiringPiSetup() == -1) /* initializes wiringPi setup */
	{
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		return 1;
	}
	if (!quiet)
		while (1)
		{
			{
				if (serialDataAvail(serial_port))
				{
					dat = getDistance(serial_port, CM); /* receive character serially*/
					if (dat != 0)
						printf("Length = %d cm\n", dat);
				}
			}
			if ((sl > 0) && (sl < 60000))
				usleep(sl * 1000);
			else
				sleep(1);
		}
	else
		while (1)
		{
			{
				if (serialDataAvail(serial_port))
				{
					dat = getDistance(serial_port, CM); /* receive character serially*/
					if (dat != 0)
						printf("%d\n", dat);
				}
			}
			if ((sl > 0) && (sl < 60000))
				usleep(sl * 1000);
			else
				sleep(1);
		}
}