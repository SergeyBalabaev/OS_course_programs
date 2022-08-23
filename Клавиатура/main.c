#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 3

char pressedKey = '\0';
int rowPins[ROWS] = {7, 6, 14, 10}; // 4, 25, 11, 8; R3, R2, R1, R0
int colPins[COLS] = {11, 22, 21};   // 7 ,6, 5; C2, C1, C0

char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

void init_keypad()
{
    for (int c = 0; c < COLS; c++)
    {
        pinMode(colPins[c], OUTPUT);
        digitalWrite(colPins[c], HIGH);
    }

    for (int r = 0; r < ROWS; r++)
    {
        pinMode(rowPins[r], INPUT);
    }
    system("raspi-gpio set 4 pu");
    system("raspi-gpio set 8 pu");
    system("raspi-gpio set 11 pu");
    system("raspi-gpio set 25 pu");
}

int findLowRow()
{
    for (int r = 0; r < ROWS; r++)
    {
        if (digitalRead(rowPins[r]) == LOW)
            return r;
    }
    return -1;
}

char get_key()
{
    int rowIndex;

    for (int c = 0; c < COLS; c++)
    {
        digitalWrite(colPins[c], LOW);

        rowIndex = findLowRow();
        if (rowIndex > -1)
        {
            if (!pressedKey)
                pressedKey = keys[rowIndex][c];
            return pressedKey;
        }

        digitalWrite(colPins[c], HIGH);
    }

    pressedKey = '\0';
    return pressedKey;
}

void help()
{
    printf("    Use this application for keypad\n");
    printf("    execute format: ./light_detect [-h][-q] \n");
    printf("    return: enter button\n");
    printf("    -h - help\n");
    printf("    -q - quiet\n");
}

int main(int argc, char *argv[])
{
    int quiet = 0;
    if (argc > 1)
    {
        if ((strcmp(argv[1], "-h") == 0))
        {
            help();
            return 0;
        }
        else if ((strcmp(argv[1], "-q") == 0))
        {
            quiet = 1;
        }
        else
        {
            help();
            return 0;
        }
    }
    wiringPiSetup();
    init_keypad();
    system("clear");
    if (!quiet)
    {
        while (1)
        {
            char x = get_key();
            if (x)
                printf("pressed: %c\n", x);
            else
                printf("no key pressed\n");

            delay(250);
            system("clear");
        }
    }
    else
    {
        while (1)
        {
            char x = get_key();
            if (x)
                printf("%c\n", x);
            delay(250);
            system("clear");
        }
    }
    return 0;
}