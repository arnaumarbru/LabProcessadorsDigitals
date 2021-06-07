# Generación de una página web
## **Introducción** 
Se generará un web server mediante la esp32.   
## **Material**
- esp32-Wroom-32D
- Software anteriormente mencionado 

## **Setup y funcionamiento**
Al igual que en la primera práctica se prepara el entorno de trabajo con VS studio y la extensión de PlatformIO.

A continuación implementamos el código dado en el enunciado de la práctica.
```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>
```
Se definen las cabeceras necesarias para la práctica.
```cpp
// SSID & Password
const char* ssid = "Mi11lite5g"; // Enter your SSID here
const char* password = "123456789"; //Enter your Password here

WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)
```
En las variables se completan con los datos del wifi y su contraseña que servirá para conectar la esp32 a la red. Se utilizará el puerto HTTP por defecto.

```cpp
void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);
// Connect to your wi-fi modem
  WiFi.begin(ssid, password);
// Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
  server.on("/", handle_root);
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
} 
```
En el setup se comprovará por mensajes que la placa se conecta al modem, cuando se haya conectado aparecerá el mensaje que se ha connectado y a continuación también se mostrará si se ha podido generar el servidor http.


```cpp
void loop() {
server.handleClient();} 
  ```
Con la función *handleClient()* servirá para recibir peticiones del servidor.

```cpp
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";
// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
```
Finalmente se envia en formato html lo que se quiere enviar en el servidor. La función *handle_root()* servirá para enviar el contenido del código html creado.
## Código completo

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>

// SSID & Password
const char* ssid = "Mi11lite5g"; // Enter your SSID here
const char* password = "123456789"; //Enter your Password here

void handle_root(void);

WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);
// Connect to your wi-fi modem
  WiFi.begin(ssid, password);
// Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
  server.on("/", handle_root);
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient();
}
// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My Primera Pagina con ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";
// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
```
## Referencias
[https://www.luisllamas.es/esp8266-servidor-parmetros/](https://www.luisllamas.es/esp8266-servidor-parmetros/)