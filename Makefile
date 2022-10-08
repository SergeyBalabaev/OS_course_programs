all:
	gcc color_sense/color_sense.c -o color_sense/color_sense -Wall
	gcc gyro_angle/gyro_angle.c -o gyro_angle/gyro_angle -Wall
	gcc keypad/keypad.c -o keypad/keypad -lpigpio -Wall
	gcc led_blinker/led_blinker.c -o led_blinker/led_blinker -Wall
	g++ light_detect/light_detect.cpp light_detect/Adafruit_ADS1X15_RPi/Adafruit_ADS1015.cpp -o light_detect/light_detect -lwiringPi -Wall
	gcc play_note/play_note.c -o play_note/play_note -Wall 
	g++ rfid_reader/MFRC522.cpp rfid_reader/rfid_reader.cpp -std=c++11 -lbcm2835 -o rfid_reader/rfid_reader
	gcc sound_detect/sound_detect.c  -o sound_detect/sound_detect -Wall
	gcc step_motor/step_motor.c -o step_motor/step_motor -lpigpio -Wall