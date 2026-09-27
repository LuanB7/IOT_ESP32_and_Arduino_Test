// Libs
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>

// Defs

#define address 0x27
#define columns 16
#define rows 2

// Var

int currentTime = 0;
int targetTime = 10;
bool timesUp = false;
int buzzerPin = 8;



// Start I2C Lib Object
LiquidCrystal_I2C lcd(address, columns, rows);

// Configura os pinos para ouvir o ESP32 (RX = 10, TX = 11)
SoftwareSerial esp32Serial(10, 11);

void setup() {

  Serial.begin(115200);
  esp32Serial.begin(9600);

  lcd.init(); // Inicia a comunicação com o display
  lcd.backlight(); // Liga a iluminação do display
  lcd.clear(); // Limpa Display

  /*
  lcd.setCursor(0, 0);
  lcd.print("Tempo Agua");
  lcd.setCursor(0, 1);
  lcd.print("2s");
  */

  // Buzzer Pin Setup
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  ESPListener();

  if (currentTime <= targetTime) {

    lcd.setCursor(0, 0);
    lcd.print("Tempo de Ciclo:");

    updateCicleTime();
    lcd.setCursor(0, 1);
    lcd.print(String(currentTime) + "s");

  } else {

    if (!timesUp) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tempo Esgotado!");

      timesUp = true;
    }

  }

  if (timesUp) {
    somDecente();
    delay(500);
  }

}

void updateCicleTime() {
  delay(1000);
  currentTime++;
}


void playBuzzer(int duration, int frequence) {
  tone(buzzerPin, frequence);
  delay(duration);
  noTone(buzzerPin);
}

void somDecente() {
  /*
  tone(buzzerPin, 659, 100); // Note Mi5 (E5) por 100ms
  delay(120);                 // Pausa rápida entre as notas
  tone(buzzerPin, 784, 150); // Note Sol5 (G5) por 150ms
  delay(150);
  noTone(buzzerPin);
  */

  tone(buzzerPin, 784, 150); // Note Sol5 (G5) por 150ms
  delay(150);
  tone(buzzerPin, 659, 100); // Note Mi5 (E5) por 100ms
  delay(120);                 // Pausa rápida entre as notas
  noTone(buzzerPin);
}

void ESPListener() {
  if (esp32Serial.available() > 0) {
    String input = esp32Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("setTime(")) {
      int startPos = input.indexOf("(");
      int endPos = input.indexOf(")");

      if (startPos != -1 &&  endPos > startPos) {
        int timeReceived = input.substring(startPos + 1, endPos).toInt();

        targetTime = timeReceived;
        currentTime = 0;
        timesUp = false;
        lcd.clear();

        Serial.print("Novo tempo até alarme definido:");
        Serial.print(timeReceived);
      }
    }
  }
}
