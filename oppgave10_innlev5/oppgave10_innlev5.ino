/*Lager en temperaturmåler som printer  temp. i C og F
  Ledpin som lyser når temp går over en gitt grenseverdi.
  To knapper som skal øke/senke den gitte grenseverdien.
  prøvd å skrive 'basic' og dokumenterende
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int LED_PIN = 13;
const int TEMP_PIN = A0;
const int BUTTON0 = 7;
const int BUTTON1 = 8;
float limit = 25; //Grenseverdi for LED dioden
unsigned long nextTimeout = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(BUTTON0, INPUT);
  pinMode(BUTTON1, INPUT);
  lcd.begin(16, 2);
}

void loop()
{
  getTempReadsAndPrintOnLCD();
  changeTempLimit();
  startTimer(1000);
 
}
/*
   Her skal vi lese om input fra temp sensor og konvertere til C og F
*/
void getTempReadsAndPrintOnLCD()
{
  int tempReading = analogRead(TEMP_PIN);
  float tempVolts = tempReading * 5 / 1024.0;
  float tempC = (tempVolts - 0.5) * 100.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  /*
     Print den konverterte temp på LCD skjermen, Både C og F
  */
  lcd.print("C: ");
  lcd.setCursor(3, 0);
  lcd.print(tempC, 1);
  lcd.setCursor(9, 0);
  lcd.print("Limit");
  lcd.setCursor(0, 1);
  lcd.print("F: ");
  lcd.setCursor(3, 6);
  lcd.print(tempF, 1);
  lcd.setCursor(9, 6);
  lcd.print(limit);
  

  /*
     skrur på LED om temp er høyere enn limit
  */
  if (limit <= tempC)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else if (limit >= tempC)
  {
    digitalWrite(LED_PIN, LOW);
  }
}
/* skjekker om en av knappene er trykt eller ikke for å justere grenseverdien
*/
void changeTempLimit()
{
  if (digitalRead(BUTTON0) == LOW)
  {
    limit = limit - 0.5;
  }
  if (digitalRead(BUTTON1) == LOW)
  {
    limit = limit + 0.5;
  }
delay(100);

}
//Setter en timer-skjekker, om tiden har gått ut = 1 hvis ikke = 0
boolean timerHasExpired()
{
  boolean hasExpired = false;
  if (millis() >= nextTimeout)
  {
    hasExpired = true;
  }
  else
  {
    hasExpired = false;
  }
  return hasExpired;
}

void startTimer(unsigned long duration)
{
  nextTimeout = millis() + duration;
}
