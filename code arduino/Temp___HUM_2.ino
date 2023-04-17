#define BLYNK_TEMPLATE_ID "TMPL2tG-Vspz1"
#define BLYNK_TEMPLATE_NAME "abd ali"
#define BLYNK_AUTH_TOKEN "VlKNsH9dnVizaTcRPTEAb9Uy7gJzveMO"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#define BLYNK_PRINT Serial
char auth[] =BLYNK_AUTH_TOKEN;//Paste auth token you copied
char ssid[] = "Bekkari";///Enter your wifi name
char pass[] = "1999@bekkari";// Enter wifi password
#define DHTPIN 32         // What digital pin we're connected to select yours accordingly
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#define VPIN_BUTTON_1    V3 
#define VPIN_BUTTON_2    V4
#define RelayPin1 12  
int isconnected1  ;
int isconnected ;
int value ;
BlynkTimer timer;
void manuel(){
  if (isconnected1 == 1) {
  digitalWrite(RelayPin1,isconnected1);
  WidgetLED LED(V5); 
  LED.on();
  }
  if (isconnected1 == 0) {
  digitalWrite(RelayPin1,isconnected1); // turn on relay 1
  WidgetLED LED(V5);
  LED.off();
  }
  }
void autom(){
     if (value<=40){
        digitalWrite(RelayPin1, HIGH);
        WidgetLED LED(V5);
        LED.on();
      }
      else{
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        WidgetLED LED(V5);
        LED.off(); 
        } 
  }
BLYNK_WRITE(VPIN_BUTTON_2) {
   isconnected = param.asInt();
}
BLYNK_WRITE(VPIN_BUTTON_1) {
   isconnected1 = param.asInt();
   }
void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V1, h); // select your virtual pins accordingly
  Blynk.virtualWrite(V0, t); // select your virtual pins accordingly
}
void soilMoistureSensor() {
  value = analogRead(34);
  value = map(value, 0, 4096, 0, 100);
  value = (value - 100) * -1;
  Serial.printf("ADC analog value = %d\n",value);
  Blynk.virtualWrite(V13, value);
}
void setup(){  
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, soilMoistureSensor);
  timer.setInterval(100L,sendSensor);
}
void loop(){
  Blynk.run();
  timer.run();
  digitalWrite(RelayPin1,isconnected);
    if (isconnected == 1){
      
      autom();
    }
    else {
      manuel();
      }
}
