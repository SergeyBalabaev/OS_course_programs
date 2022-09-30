#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void help(); 
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
	if (!quiet)
		printf("\nThe Notes application was started\n\n");

	char buf[2];
	while (1) {
		scanf("%s", buf);
		if ((buf[0] == 'A') && (buf[1] != '#'))
			system("aplay ./A4.wav -q");
		if (buf[0] == 'B')
			system("aplay ./B4.wav -q");
		if ((buf[0] == 'C') && (buf[1] != '#'))
			system("aplay ./C4.wav -q");
		if ((buf[0] == 'D') && (buf[1] != '#'))
			system("aplay ./D4.wav -q");
		if (buf[0] == 'E')
			system("aplay ./E4.wav -q");
		if ((buf[0] == 'F') && (buf[1] != '#'))
			system("aplay ./F4.wav -q");
		if ((buf[0] == 'G') && (buf[1] != '#'))
			system("aplay ./G4.wav -q");
		if ((buf[0] == 'A') && (buf[1] == '#'))
			system("aplay ./Ad4.wav -q");
		if ((buf[0] == 'C') && (buf[1] == '#'))
			system("aplay ./Cd4.wav -q");
		if ((buf[0] == 'D') && (buf[1] == '#'))
			system("aplay ./Dd4.wav -q");
		if ((buf[0] == 'F') && (buf[1] == '#'))
			system("aplay ./Fd4.wav -q");
		if ((buf[0] == 'G') && (buf[1] == '#'))
			system("aplay ./Gd4.wav -q");
	}

	return 0;
}

void help()
{
	printf("    Use this application for plaing notes\n");
	printf("    execute format: ./notes\n");
	printf("    -h - help\n");
	printf("    -q - quiet\n");
	printf("    input format (from stdin):\n");
	printf("        NOTE\n");
	printf("    NOTE - note name in scientific pitch notation\n");
	printf("    Example:\n");
	printf("    ./notes -q\n");
	printf("    A\n");
	printf("    playing A\n");
}
