# Lectura de etiqueta RFID
## **Introducción** 
Funcionamiento módulo de lectura RFID.
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 
- Módulo de lectura RFID

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.
```cpp
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 //Pin 9 para el reset del RC522
#define SS_PIN 10 //Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
```
Se definen las cabeceras que serviran para interactuar con los dispositivos SPI y el lector RFID concretamente.

Se definen los pines de reset en el pin 9 y 10 para el SDA. Se define un objeto para el dispositivo.
```cpp
void setup() {
  Serial.begin(9600); //Iniciamos la comunicación serial
  SPI.begin(); //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Lectura del UID");
}
```
Se inicializa la comunicación y el bus SPI, *mfrc522.PCD_Init()* iniciliza el dispositivo . Se imprime por pantalla que se está haciendo una lectura.

```cpp
void loop() {
// Revisamos si hay nuevas tarjetas presentes
  if ( mfrc522.PICC_IsNewCardPresent()){
//Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()){
    // Enviamos serialemente su UID
      Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);    
      }
  Serial.println();
  // Terminamos la lectura de la tarjeta actual
  mfrc522.PICC_HaltA();
  }
  }
}
```
Se comprueba si hay alguna tarjeta presente, en dicho caso se busca de forma serial su UID com una iteracion for y se imprime por pantalla. Finalmente se termina la lectura de la tarjeta.
## Codigo completo

```cpp
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 //Pin 9 para el reset del RC522
#define SS_PIN 10 //Pin 10 para el SS (SDA) del RC522

MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
void setup() {
  Serial.begin(9600); //Iniciamos la comunicación serial
  SPI.begin(); //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Lectura del UID");
}
void loop() {
// Revisamos si hay nuevas tarjetas presentes
  if ( mfrc522.PICC_IsNewCardPresent()){
//Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()){
    // Enviamos serialemente su UID
      Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);    
      }
  Serial.println();
  // Terminamos la lectura de la tarjeta actual
  mfrc522.PICC_HaltA();
  }
  }
}
```
## Referencia

https://naylampmechatronics.com/blog/22_tutorial-modulo-lector-rfid-rc522.html
