# Reproducción des de memoria interna
## **Introducción** 
Escuchar el sonido alamacenada en la ram interna de la esp32 descodificando la señal digital en una señal analógica.
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 
- Placa de conexión de audio MAX98357 I2S
- altavoz

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.

```cpp
#include "Arduino.h"
#include "FS.h"
#include "SPIFFS.h"
#include "SD.h"
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

```
Se añaden las cabeceras correspondientes que son básicamente librerias de audio. 
También se definen 3 punteros, uno que servira par leer el archivo de audio, el segundo servira para descodificar el archivo y el último servirá para enviar de forma analógica el audio.

```cpp
void setup(){
  Serial.begin(115200);

  in = new AudioFileSourcePROGMEM(sampleaac, sizeofsampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(26,25,22);
  aac->begin(in, out);
}

```
En el apartado de setup se inicializa un puntero *in* con los parametros de la muestra del archivo de audio aac y el tamaño.
Otro puntero aac que será el audio codificado en aac y el out que será el áudio de salida.
Se le inicializa con una ganancia de 0.125 y se inicilizan los pines.



```cpp
void loop(){
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac -> stop();
    Serial.printf("Sound Generator\n");
    delay(1000);
  }
}
```
En el loop se comprobará que si el aac se ejecute hasta estar descodificada. Cuando termine el proceso se parará y se generará el sonido con el mensaje que *"Sound Generator"*
## Codigo completo

```cpp
#include "Arduino.h"
#include "FS.h"
#include "SPIFFS.h"
#include "SD.h"
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;


void setup(){
  Serial.begin(115200);

  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(26,25,22);
  aac->begin(in, out);
}

void loop(){
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac -> stop();
    Serial.printf("Sound Generator\n");
    delay(1000);
  }
}
```
## Referencia

https://github.com/earlephilhower/ESP8266Audio
