# Программа для работы с дисплеем

Сборка:
```  
gcc -o lcd main.c lcd.c -lgd -lfreetype -lm  
```

Запуск:  
```
sudo ./lcd test_input  
```
test_input - текстовый файл для вывода  

Выходные данные: 
Печать заданного текста на дисплее  

Для корректной сборки программы необходимо установить приложенную библиотеку libgd-2.3.3  
Для этого требуется выполнить следующие действия:  
```
cd libgd-2.3.3  
chmod +x configure  
./configure  
make  
make install  
```

