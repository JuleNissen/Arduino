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
const int LIMIT = 25; //Grenseverdi for LED dioden
float tempC;
float tempF;

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
  /*
     Her skal vi lese om input fra temp sensor og konvertere til C og F
  */
  int tempReading = analogRead(TEMP_PIN);
  float tempVolts = tempReading * 5 / 1024.0;
  float tempC = (tempVolts - 0.5) * 100.0;
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  /*
     Print den konverterte temp på LCD skjermen, Både C og F
  */
  lcd.print("Temp C: ");
  lcd.setCursor(7, 0);
  lcd.print(tempC, 1);
  lcd.setCursor(0, 1);
  lcd.print("Temp F: ");
  lcd.setCursor(7, 6);
  lcd.print(tempF, 1);

  /*skjekker om temperaturen er høyere enn den gitte grenseverdien
     hvis temp > LIMIT skru PÅ lys ellers skal den være AV
  */
  if (LIMIT <= tempC)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else if (LIMIT >= tempC)
  {
    digitalWrite(LED_PIN, LOW);
  }
  /*unngå den konstante oppdateringen til skjermen og gjøre det lettere å lese
     tømmer skjermen når tiden har gått for å hindre uønskede elementer på skjermen
  */
  delay(2000); //Kanskje bytte til timer funkjon??
  lcd.clear();
}

