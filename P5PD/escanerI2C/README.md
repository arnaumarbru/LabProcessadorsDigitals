# Escaner I2C
## **Introducción** 
Identificar el puerto de comunicación I2C de cualquier dispositivo.
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 
- Dispositivos I2C

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.
```cpp
#include <Arduino.h>
#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(115200);
    while (!Serial); // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
```
Se incluyen las cabeceras necesarias y en el setup con el *wire.begin()* permitirá leer datos des de un dispositivo externo. 
```cpp
 void loop(){
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
    Serial.print("I2C device found at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");
      nDevices++;
}
    else if (error==4){
    Serial.print("Unknown error at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
  Serial.println("No I2C devices found\n");
    else
    Serial.println("done\n");
    delay(5000); // wait 5 seconds for next scan
}
```
El programa loop principal en primer lugar escaneará si hay dispositivos para cada dirección, en caso de no haber error el programa imprimirá que ha encontrado un dispositivo con su dirección y se sumará en el contador *nDevices*. En caso de haber error también saldrá por pantalla con su dirección. En caso de no haver dispositivos encontrados el proceso lo indicará mediante la variable *nDevices*

## Codigo completo

```cpp
#include <Arduino.h>
#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(115200);
    while (!Serial); // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
void loop(){
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
    Serial.print("I2C device found at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");
      nDevices++;
}
    else if (error==4){
    Serial.print("Unknown error at address 0x");
      if (address<16)
      Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0)
  Serial.println("No I2C devices found\n");
    else
    Serial.println("done\n");
    delay(5000); // wait 5 seconds for next scan
}
```
