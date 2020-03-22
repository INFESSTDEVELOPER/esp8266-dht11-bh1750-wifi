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
const char* ssid     = "VTR-0009770";
const char* password = "ssYpknrT8zfq";
const char* host = "api-XXXX.herokuapp.com";

void setup()
{
  Serial.begin(9600);
  Wire.begin( );
  lightMeter.begin();
  dht.begin();
  delay(700);
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
    Serial.println(" C  ");
    uint16_t lux = lightMeter.readLightLevel();
    Serial.print("Lumenes: ");
    Serial.print(lux);
    Serial.println(" lx");
     delay(6000);
}
