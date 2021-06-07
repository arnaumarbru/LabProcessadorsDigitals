# Comunicación UART2
## **Introducción** 
Generar un bucle que envie datos del terminal rxd0 a la UART2 txd2 y que la recepción de datos se reenvien a la salida txd0
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

Se definen los pines que para poder realizar una comunicación UART2.

Se conecta el puerto RXD0 con el TXD2 y a su vez del TXD2 al TXD0.

Finalmente se lee el contenido de dichas conexiones hasta llegar a la salida TXD0.

## Codigo completo

```cpp
#include <Arduino.h>

#define RXD0 34
#define TXD0 35
#define TXD2 28
 
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXD0, TXD2);
  Serial2.begin(115200, SERIAL_8N1, TXD2, TXD0);
}
 
void loop() { 
 
  if(Serial.available()){
     Serial1.write(Serial.read());  
   }
   if(Serial1.available()){
     Serial2.write(Serial1.read());
     Serial.printf("Datos");  
   }
     }
```

