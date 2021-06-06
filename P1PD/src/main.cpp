#include <Arduino.h>
int led = 13;


void setup() {         

  pinMode(led, OUTPUT);    //se inicialia el pin como una salida
}

void loop() {
  digitalWrite(led, HIGH); //Se abre el led
  Serial.println("ON"); //Se muestra mensaje on
  delay(500);               // se espera medio segundo
  digitalWrite(led, LOW);    //Se cierra el led
  Serial.println("OFF");  //Se muestra mensaje off
  delay(500);        // se espera medio segundo  
}