# Interacciones por GPIO
## **Introducción** 
Mediante un pulsador se enviará una señal al pin GPIO el cual interrupirá el proceso.   
## **Material**
- esp32-Wroom-32D
- pulsador
- Software anteriormente mencionado 

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.

```cpp
struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {18, 0, false};
```
En esta parte se define una estructura correspondiente al pulsador que contiene si está pulsado en una variable bool, una variable que actua como contador y el numero de pin. Y se define un constructor por defecto que sera el pin 18 con la variable contable 0 y sin pulsar.

```ruby
void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}
```
Una vez ya definidas la estructura se crea una acción que irá contando las veces que se pulsa el pulsador y que servirá para ver si se ha pulsado o no.

```ruby
void setup() {  
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
}
```
Se inicializan los pines de como entrada y con la función *attachInterrupt(button1.PIN, isr, FALLING);* se hará la interrupción en base a un pin por pin. ***button1.PIN***  será el pin GPIO, ***isr*** es la función anterior y ***Falling*** se refiere a la acción de pasar de estado *HIGH* a *LOW*.

```ruby
void loop() {
  if (button1.pressed) {
  Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
  button1.pressed = false;
}


static uint32_t lastMillis = 0;

if (millis() - lastMillis > 60000) {
  lastMillis = millis();
  detachInterrupt(button1.PIN);
  Serial.println("Interrupt Detached!");
}
}
```
Finalmente en esta iteración se indica que cada vez que se pulse se muestre que el boton ha sido pulsado y el número de veces que ha sido pulsado.

A partir de aqui se establece que cada 60000ms se interrumpira el programa.

## Codigo completo

```ruby
#include <Arduino.h>

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {18, 0, false};

void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}

void setup() {  
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {
  if (button1.pressed) {
  Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
  button1.pressed = false;
}


static uint32_t lastMillis = 0;

if (millis() - lastMillis > 60000) {
  lastMillis = millis();
  detachInterrupt(button1.PIN);
  Serial.println("Interrupt Detached!");
}
}
```
