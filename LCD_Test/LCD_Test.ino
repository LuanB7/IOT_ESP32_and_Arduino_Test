// Libs
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Defs

#define address 0x27
#define columns 16
#define rows 2

// Var

int sec = 0;
bool timesUp = false;
int buzzerPin = 8;



// Start I2C Lib Object
LiquidCrystal_I2C lcd(address, columns, rows);

void setup() {
  // put your setup code here, to run once:

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

  if (sec <= 10) {

    lcd.setCursor(0, 0);
    lcd.print("Tempo de Ciclo:");

    updateCicleTime();
    lcd.setCursor(0, 1);
    lcd.print(String(sec) + "s");

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
  sec++;
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
