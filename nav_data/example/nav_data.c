#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "LSM9DS1_Types.h"
#include "LSM9DS1.h"

double posX = 0, posY = 0, posZ = 0;
double posXtemp, posYtemp, posZtemp;

void pressure()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) {
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, LPS25HB I2C address is 0x5D(72)
	ioctl(file, I2C_SLAVE, 0x5D);

	// Select control register(0x20)
	// Active mode, Continuous Update(0x90)
	char config[2] = { 0 };
	config[0] = 0x20;
	config[1] = 0x90;
	write(file, config, 2);
	sleep(1);

	// Read 3 bytes of data from register(0x28)
	// Pressure lsb first
	char reg[1] = { 0x28 | 0x80 };
	while (1) {
		write(file, reg, 1);
		char data[3] = { 0 };

		system("clear");
		if (read(file, data, 3) != 3) {
			printf("Error : Input/Output error \n");
		} else {
			// Convert the data
			float pressure = ((data[2] * 65536) +
					  ((data[1] * 256) + data[0])) /
					 4096.0 * 0.750062;
			// Output data to screen
			printf("Pressure is : %.2f mm Hg \n", pressure);
		}
		sleep(1);
	}
}

void help()
{
	printf("    Use this application for reading from Pmod Nav\n");
	printf("    execute format: ./PmodNav [-h][-b][-g][-a][-m] \n");
	printf("    [-h] return: help\n");
	printf("    [-b] return: barometer value in mm Hg \n");
	printf("    [-g] return: gyroscope deflection angle in X,Y,Z\n");
	printf("    [-a] return: accelerometer value\n");
	printf("    [-m] return: magnetometer value\n");
}

int main(int argc, char *argv[])
{
	int state = 0;
	if (argc > 1) {
		if ((strcmp(argv[1], "-h") == 0)) {
			help();
			return 0;
		} else if ((strcmp(argv[1], "-b") == 0)) {
			state = 1;
		} else if ((strcmp(argv[1], "-g") == 0)) {
			state = 2;
		} else if ((strcmp(argv[1], "-a") == 0)) {
			state = 3;
		} else if ((strcmp(argv[1], "-m") == 0)) {
			state = 4;
		} else {
			help();
			return 0;
		}
	} else {
		help();
		return 0;
	}
	if (state == 1)
		while (1) {
			pressure();
		}
	else {
		LSM9DS1 imu(IMU_MODE_I2C, 0x6b, 0x1e); // IMU_MODE_I2C
		imu.begin();
		if (!imu.begin()) {
			fprintf(stderr,
				"Failed to communicate with LSM9DS1.\n");
			exit(EXIT_FAILURE);
		}
		imu.calibrate();

		if (state == 2)
			while (1) {
				system("clear");
				while (!imu.gyroAvailable())
					;
				imu.readGyro();
				posXtemp = imu.calcGyro(imu.gx);
				posYtemp = imu.calcGyro(imu.gy);
				posZtemp = imu.calcGyro(imu.gz);
				if (abs(posXtemp) < 0xA)
					posXtemp = 0;
				posX += posXtemp * 0.04;
				if (abs(posYtemp) < 0xA)
					posYtemp = 0;
				posY += posYtemp * 0.04;
				if (abs(posZtemp) < 0xA)
					posZtemp = 0;
				posZ += posZtemp * 0.04;

				printf("Gyro: %f, %f, %f [deg]\n", posX, posY,
				       posZ);
				usleep(20000);
			}

		if (state == 3)
			while (1) {
				system("clear");
				while (!imu.accelAvailable())
					;
				imu.readAccel();
				printf("Accel: %f, %f, %f [m/s^2]\n",
				       imu.calcAccel(imu.ax),
				       imu.calcAccel(imu.ay),
				       imu.calcAccel(imu.az));
				sleep(1.0);
			}

		if (state == 4)
			while (1) {
				system("clear");
				while (!imu.magAvailable())
					;
				imu.readMag();
				printf("Mag: %f, %f, %f [Gs]\n",
				       imu.calcMag(imu.mx), imu.calcMag(imu.my),
				       imu.calcMag(imu.mz));
				sleep(1.0);
			}
	}
	exit(EXIT_SUCCESS);
}
