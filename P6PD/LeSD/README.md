# Lectura y escritura de memoria SD
## **Introducción** 
funcionamiento del lector de tarjeta SD.
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 
- Módulo de tarjeta SD

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.
```cpp
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");

  SPI.begin(18,19,23,4); //pines de inicialización  

  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
 
  // Se escribe dentro del fichero
  myFile = SD.open("/archivo.txt",FILE_WRITE);
  myFile.println("Hello World!");
  myFile.close();

  myFile = SD.open("archivo.txt");//abrimos  el archivo 
  if (myFile) {
    Serial.println("archivo.txt:");
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo");
  }
}

```
En este ejercicio solo se tiene la parte del setup, se incluyen las nuevas cabeceras que serviran para que el programa pueda interectuar con dispositivos SPI, leer y escribir la SD.

Se muestra un texto por pantalla indicando que se esta inicilizando la SD, en caso de no encontrarlo se mostrará un mensaje indicando que no se puedo inicializar, por otro lado si se encuentra se mostrará un mensaje diciendo *inicializacion existosa*.

Se escribe un fichero de prueba con un mensaje para comprobar que funciona correctamente. Con el fin de poder leer un archivo de formato .txt se indica el nombre del archivo, en este caso *archivo.txt*, si esta disponible . En caso positivo se imprime por pantalla el contenido del fichero, en caso de que no se pueda abrir el fichero saldrá un mensaje de error.

## Codigo completo

```cpp
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");

  SPI.begin(18,19,23,4); //pines de inicialización  

  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
 
  // Se escribe dentro del fichero
  myFile = SD.open("/archivo.txt",FILE_WRITE);
  myFile.println("Hello World!");
  myFile.close();

  myFile = SD.open("archivo.txt");//abrimos  el archivo 
  if (myFile) {
    Serial.println("archivo.txt:");
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo");
  }
}

void loop()
{
  
}

```
