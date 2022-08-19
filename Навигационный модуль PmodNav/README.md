# Программа для работы с навигационным модулем PmodNav

Установка библиотеки "SparkFun LSM9DS1 RaspberryPI Library"  
```
git clone https://github.com/akimach/LSM9DS1_RaspberryPi_Library.git  
cd LSM9DS1_RaspberryPi_Library  
make  
sudo make install  
sudo -s  
LD_LIBRARY_PATH=lib ./LSM9DS1_Basic_I2C  
```

Сборка:  
```
gcc -Wall -O2 example/main.c -o PmodNav -llsm9ds1 -lm  
```

Запуск:  
./PmodNav [-h][-b][-g][-a][-m]  
-h - описание работы  
-b - вывод показаний барометра  [мм.рт.ст.]  
-g - вывод показаний гироскопа  [градусы]  
-a - вывод показаний акселерометра  [м/с^2]  
-m - вывод показаний магнитометра [Гс]  