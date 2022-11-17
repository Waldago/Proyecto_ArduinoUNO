#include <DHT.h>
#include <DHT_U.h>


//LED's
#define ledRed 13
#define ledBlue 12
#define ledGreen 11
#define ledEstado 7

//Sensor
#define DHTPIN 10
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledEstado, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    digitalWrite(ledEstado, HIGH);

   if (t>24 | h>50 & t>10) {
      digitalWrite(ledBlue, HIGH);
   } else digitalWrite(ledBlue, LOW);
   if (t<11) {
      digitalWrite(ledRed, HIGH);
   } else digitalWrite(ledRed, LOW);
   if (t>10 & t<25) {
      digitalWrite(ledGreen, HIGH);
   } else digitalWrite(ledGreen, LOW);
}
