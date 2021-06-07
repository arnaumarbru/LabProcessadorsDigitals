# Sistemas operativos en tiempo real 
## **Introducción** 
Comprobar la multitarea de la esp32.
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.

```cpp
#include <Arduino.h>
void anotherTask( void * parameter );
void setup(){
  Serial.begin(112500);

  /* we create a new task here */
  xTaskCreate(anotherTask,"another Task",10000,NULL,1, ULL); 
}
```
En el setup se crea una tarea con en la que primero se tendrá su nombre, después la dimensión del stack, el parámetro, la prioridad, y el seguimiento de la tarea.

```cpp
void loop(){
  Serial.println("this is ESP32 Task");
  delay(1000);
}
/* this function will be invoked when additionalTask was created */
void anotherTask( void * parameter ){
  /* loop forever */
  for(;;)
  {
  Serial.println("this is another Task");
  delay(1000);
  }
/* delete a task when finish,
this will never happen because this is infinity loop */
  vTaskDelete( NULL );
  }
  ```
Dentro del loop se crea un loop que va repitiendo *this is ESP32 Task* cada segundo. Se llama la función **anotherTask()** que lo que hará es repetir en bucle *this is another Task* cada segundo. 

La última instrucción debería terminar la tarea pero no es posible ya que hay un bucle infinito.
## **Resultado**
Se va repitiendo en bucle *this is ESP32 Task* y
*this is another Task*

## Codigo completo

```cpp
#include <Arduino.h>
void anotherTask( void * parameter );
void setup(){
  Serial.begin(112500);

  /* we create a new task here */
  xTaskCreate(
  anotherTask, /* Task function. */
  "another Task", /* name of task. */
  10000, /* Stack size of task */
  NULL, /* parameter of the task */
  1, /* priority of the task */
  NULL); /* Task handle to keep track of created task */
}
    /* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop(){
  Serial.println("this is ESP32 Task");
  delay(1000);
}
/* this function will be invoked when additionalTask was created */
void anotherTask( void * parameter ){
  /* loop forever */
  for(;;)
  {
  Serial.println("this is another Task");
  delay(1000);
  }
/* delete a task when finish,
this will never happen because this is infinity loop */
  vTaskDelete( NULL );
  }
```