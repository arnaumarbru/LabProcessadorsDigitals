# Comunicación bluetooth con el movil
## **Introducción** 
Se tratará de conectar el móvil y la esp32 mediante el bluetooth  
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.
```cpp
#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
```
Se incluyen las cabeceras para poder habilitar el bluetooth
Se hace una definición para ver si el bluetooth esta encendido sino sale un mensaje de error. Se llama una variable *SerialBT*.

```cpp
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
```
Se inicia el bluetooth con el nombre del dispositivo y aparece un mensaje cuando se pueda emparejar con otro dispositivo.

```cpp
void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
  Serial.write(SerialBT.read());
  }
delay(20);
}
```
Se comprueba si esta disponible el bluetooth y si es así envia información al dispositivo mediante el bluetooh.
## Código completo


```cpp
#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
  Serial.write(SerialBT.read());
  }
delay(20);
}
```

