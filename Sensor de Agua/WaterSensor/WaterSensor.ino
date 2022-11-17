const int waterSensorImput = A2;
const int rociador = 13;
int entrada;
const int threshold = 600;


void setup() {
  // put your setup code here, to run once:
  pinMode(rociador, OUTPUT);
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  entrada = analogRead(waterSensorImput);

  Serial.println(entrada);

  digitalWrite(rociador, HIGH);

  if(entrada >= threshold) {
      digitalWrite(rociador, LOW);
  }
  

}
