#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

uint8_t xSign;
float xPosition = 0;

void askGiro(int file)
{
    // Read 6 bytes of data
    // lsb first
    // Read xGyro lsb data from register(0x28)
    char reg[1] = {0x28};
    write(file, reg, 1);
    char data[1] = {0};
    if (read(file, data, 1) != 1)
    {
        printf("Error : Input/Output error \n");
        exit(1);
    }
    char data_0 = data[0];

    // Read xGyro msb data from register(0x29)
    reg[0] = 0x29;
    write(file, reg, 1);
    read(file, data, 1);
    char data_1 = data[0];

    // Read yGyro lsb data from register(0x2A)
    reg[0] = 0x2A;
    write(file, reg, 1);
    read(file, data, 1);
    char data_2 = data[0];

    // Read yGyro msb data from register(0x2B)
    reg[0] = 0x2B;
    write(file, reg, 1);
    read(file, data, 1);
    char data_3 = data[0];

    // Read zGyro lsb data from register(0x2C)
    reg[0] = 0x2C;
    write(file, reg, 1);
    read(file, data, 1);
    char data_4 = data[0];

    // Read zGyro msb data from register(0x2D)
    reg[0] = 0x2D;
    write(file, reg, 1);
    read(file, data, 1);
    char data_5 = data[0];

    // Convert the data
    int16_t xGyro = (data_1 << 8 | data_0);
    if (xGyro > 32767)
    {
        xGyro -= 65536;
    }

    int16_t yGyro = (data_3 << 8 | data_2);
    if (yGyro > 32767)
    {
        yGyro -= 65536;
    }

    int16_t zGyro = (data_5 << 8 | data_4);
    if (zGyro > 32767)
    {
        zGyro -= 65536;
    }
    /*
        if ((xGyro & 0x8000) == 0)
        {
            xSign = 0;
        }
        else
        {
            xSign = 1;
            xGyro &= 0x7FFF;
            xGyro = 0x8000 - xGyro;
        }
        if (xGyro < 0x0A)
        {
            xGyro = 0;
        }
        if (xSign == 0)
        {
            xPosition += 0.07 * xGyro * 0.02;
        }
        else
        {
            xPosition -= 0.07 * xGyro * 0.02;
        }
    */
    // Output data to screen
    double dpsX = xGyro * 0.068;
    double dpsY = yGyro * 0.068;
    double dpsZ = zGyro * 0.068;

    // printf("Rotation in X-Axis : %d \n", xGyro);
    // printf("Rotation in Y-Axis : %d \n", (int)dpsY);
    // printf("Rotation in Z-Axis : %d \n", (int)dpsZ);
    printf("X : %lf\tY : %d\tZ : %d\t \n", dpsX, dpsY, dpsZ);
}

void main()
{
    // Create I2C bus
    int file;
    char *bus = "/dev/i2c-1";
    if ((file = open(bus, O_RDWR)) < 0)
    {
        printf("Failed to open the bus. \n");
        exit(1);
    }
    // Get I2C device, L3G4200D I2C address is 0x68(104)
    ioctl(file, I2C_SLAVE, 0x69);

    // Enable X, Y, Z-Axis and disable Power down mode(0x0F)
    char config[2] = {0};
    config[0] = 0x20;
    config[1] = 0x0F;
    write(file, config, 2);
    // Full scale range, 2000 dps(0x30)
    config[0] = 0x23;
    config[1] = 0x00;
    write(file, config, 2);
    sleep(1);

    system("clear");
    while (1)
    {
        askGiro(file);
        usleep(20000);
    }
    return 0;
}
