# ��������� ��� ������ � ����������� gp2yo

������:  
```
gcc rangefinder_gp2y.c -o rangefinder_gp2y -lwiringPi -lm -Wall
```

� ������, ���� ������������ "cannot find -lwiringPi", ���������� ���������� ���� WiringPi: https://github.com/WiringPi/WiringPi
���������:
```
./build
```

������:  
sudo ./rangefinder_gp2y [-h][-q] N  
-h - �������� ������  
-q - ����� �����, ��������� ������ ���������� �� �������  
N - ������ ������ �������� � ��  

������:  
```
sudo ./rangefinder_gp2y -q 1000 //����� �������� ���� ��� � ������� � "����� ������"