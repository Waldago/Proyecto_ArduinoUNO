const int soundSensor = A1;
const int LedPin = 13;

void setup() {
  pinMode(LedPin, OUTPUT);
  pinMode(soundSensor, INPUT);
  Serial.begin(115200);
}

void loop() {
  int statusSensor = digitalRead(soundSensor);
  Serial.println(statusSensor);
  if (statusSensor == HIGH){
    digitalWrite(LedPin, HIGH);
  }else{
    digitalWrite(LedPin, LOW);
  }
}
