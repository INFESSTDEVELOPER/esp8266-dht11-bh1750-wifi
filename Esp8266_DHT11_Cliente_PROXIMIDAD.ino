/*  ----------------------------------------------------------------
    jsdevelooper

    Leyendo la temperatura y humedad con un sensor DHT11, leyendo lumenes de un BH1756
    y subir los valores a un serVidor mediante WiFi con el esp8266.
  --------------------------------------------------------------------
*/


#include <DHT.h>
#include <ESP8266WiFi.h>
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 0
//BH1750
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;
DHT dht(dht_dpin, DHTTYPE); 
const char* ssid     = "xxxxxxxx";
const char* password = "xxxxxxxx";
const char* host = "xxxxx.herokuapp.com";

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  dht.begin();
  delay(700);
  WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
        Serial.print(".");
    }

}

void loop()
{


    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Humedad actual = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("Temperatura = ");
    Serial.print(t); 
    Serial.println("C  ");
    uint16_t lux = lightMeter.readLightLevel();
    Serial.print("Lumenes: ");
    Serial.print(lux);
    Serial.println(" lx");
 
 
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("Conexion Fallida");
       return;
     }

//aca crearemos la peticion 
 String url = "/indoor";
//
    String dato1 = "?temp=";
    String dato2 = "&hum=";
    String dato3 = "&lx=";
    Serial.print("peticion URL: ");
    Serial.println(url);

//  // Enviaremos la peticion a nuestro backend en heroku
client.print(String("GET ") + url  + dato1 + t + dato2 + h + dato3 + lux +" HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
 unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
     client.stop();
     return;
   }
}


while (client.available()) {
  String line = client.readStringUntil('\r');
   Serial.print(line);
 }

  Serial.println();
 Serial.println("Cerrando Conexion");

 delay(60000);
}