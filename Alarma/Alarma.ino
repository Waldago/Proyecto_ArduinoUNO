// *************************************************************************
// Autores: Pablo Hernan Rechimon, Walter Gomez, Maximiliano Franco
// Materia: Inteligencia Artificial
// Profesores: Marcela Toba, Jose Luis Cabrera
// Año: Segundo Cuatrimestre 2022
// *************************************************************************

#include <Wire.h> 
// Libreria LiquidCrystal utilizada para controlar el panel de la clave
#include <LiquidCrystal_I2C.h>
// Configuración de Pines en uso
const int buttonPinOK = 6;     
const int buttonPinUP = 4;     
const int buttonPinDOWN = 5;     
const int buttonPinRIGHT = 3;    
const int buttonPinLEFT = 2;     
const int alarmOutputPin =  13; 

// Estado reposo inicial de botones
int buttonStateOK = 0;         
int buttonStateUP = 0;
int buttonStateDOWN = 0;
int buttonStateRIGHT = 0;
int buttonStateLEFT = 0;

// Variables globales para manejar Valor y Posicion de los enteros que conforman la clave
int pos_numbers = 0;
int current_position = 0;

// Arrays Globales para almacenar el valor en cada posición, y la clave.
int numbers_array[4] = {0,0,0,0};
int password_array[4] = {0,0,0,0};


//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x3F,16,2);  //

void setup() {
  // Configuración Inicial del Led. El cursor se maneja (Fila, Columna)
  lcd.init();
  lcd.backlight();
  lcd.print("Clave");
  lcd.setCursor(0, 1);
  lcd.print("0000");
  lcd.setCursor(0, 1);

  // Configuración de Pines de Entrada y salida.
  pinMode(alarmOutputPin, OUTPUT);
  pinMode(buttonPinOK, INPUT);
  pinMode(buttonPinUP, INPUT);
  pinMode(buttonPinDOWN, INPUT);
  pinMode(buttonPinRIGHT, INPUT);
  pinMode(buttonPinLEFT, INPUT);
}

void loop() {
  // Cursor siempre debajo de la posición actual para facilidad de lectura al poner contraseña.
  lcd.cursor();

  delay(100);
  buttonStateOK = digitalRead(buttonPinOK);
  buttonStateUP = digitalRead(buttonPinUP);
  buttonStateDOWN = digitalRead(buttonPinDOWN);
  buttonStateRIGHT = digitalRead(buttonPinRIGHT);
  buttonStateLEFT = digitalRead(buttonPinLEFT);
  
  if (buttonStateUP == HIGH) {
    increaseNumber();
  }
  if (buttonStateDOWN == HIGH) {
    decreaseNumber();
  }
  if (buttonStateRIGHT == HIGH){
    moveCursorRight();
  }
  if (buttonStateLEFT == HIGH){
    moveCursorLeft();
  }
  if (buttonStateOK == HIGH){
    ingressPasswordEvent();
    resetNumberArray();
    resetPasswordArray();
  }
}

void ingressPasswordEvent(){
  lcd.setCursor(0,0);
  lcd.clear();
  
  if (checkPassword()){

    lcd.print("Correcto!");
    unlockAlarm();
    resetLCDPanel();

   } else {
    
    lcd.print("Incorrecto");
    triggerAlarm();
    resetLCDPanel();

    }
}

bool checkPassword(){
  if (password_array[0] == 1 && password_array[1] == 1 && password_array[2] == 1 && password_array[3] == 1){
    return true;
  } else {
    return false;
  }
}

void triggerAlarm(){
    digitalWrite(alarmOutputPin, HIGH);
    delay(10000);
    digitalWrite(alarmOutputPin, LOW);
}

void unlockAlarm(){
    digitalWrite(alarmOutputPin, HIGH);
    delay(500);
    digitalWrite(alarmOutputPin, LOW);
    delay(100);
    digitalWrite(alarmOutputPin, HIGH);
    delay(250);
    digitalWrite(alarmOutputPin, LOW);
    delay(300);
}

void resetLCDPanel(){
    lcd.setCursor(0, 0);
    lcd.print("Clave     ");
    lcd.setCursor(0, 1);
    lcd.print("0000");
    lcd.setCursor(0, 1);
}

void resetPasswordArray(){
  for (int i = 0; i < sizeof(password_array) ; i ++){
    password_array[i] = 0;
  }
}

void resetNumberArray(){
  for (int i = 0; i < sizeof(numbers_array) ; i ++){
    numbers_array[i] = 0;
  }
}

void moveCursorRight(){
  pos_numbers = 0;
  current_position += 1;
  if (current_position == 4){
    current_position = 0;
  }
  lcd.setCursor(current_position,1); 
}

void moveCursorLeft(){
  pos_numbers = 0;
  current_position -= 1;
  if (current_position == -1){
    current_position = 3;
  }
  lcd.setCursor(current_position,1); 
}

void increaseNumber(){
  numbers_array[current_position] += 1;
  if (numbers_array[current_position] == 10) {
    numbers_array[current_position] = 0;
  } 
  applyNumber(current_position);
  printLedPosition(current_position);
}

void decreaseNumber(){
  numbers_array[current_position] -= 1;
  if (numbers_array[current_position] == -1) {
    numbers_array[current_position] = 9;
  } 
  applyNumber(current_position);
  printLedPosition(current_position);
}

void applyNumber(int position){
  if (position == 0){
    password_array[0] = numbers_array[position];
  }
  if (position == 1){
    password_array[1] = numbers_array[position];
  }
  if (position == 2){
    password_array[2] = numbers_array[position];
  }
  if (position == 3){
    password_array[3] = numbers_array[position];
  }
}

void printLedPosition(int position){
  lcd.setCursor(position,1);
  lcd.print(numbers_array[position]);
  lcd.setCursor(position,1);
}