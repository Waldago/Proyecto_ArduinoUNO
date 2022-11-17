#include <Servo.h>

const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
const int LDRPin = A3;   //Pin del LDR
const int LedPin = 13;
const int threshold = 500;
const int PULSOMAX = 500;
const int PULSOMIN = 1000;

int V;
int ilum;

void setup() 
{
  pinMode(LedPin, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
   V = analogRead(LDRPin);         

   //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A0 
  ilum = ((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)

   Serial.println(ilum);
   if(ilum <= threshold) {
     digitalWrite(LedPin, HIGH);      
   } digitalWrite(LedPin, LOW);
   
}