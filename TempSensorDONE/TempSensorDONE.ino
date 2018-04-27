int tempPin = A0;
//lightpin = 1;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() 
{
lcd.begin(16, 2);
pinMode(tempPin, INPUT);
}
void loop()
{
// Display Temperature in C
int tempReading = analogRead(tempPin);
float tempVolts = tempReading * 5 / 1024.0;
float tempC = (tempVolts - 0.5) * 100.0;
float tempF = tempC * 9.0 / 5.0 + 32.0;
// ----------------
lcd.print("Temp C: ");
lcd.setCursor(7, 0);
lcd.print(tempC, 1);
lcd.setCursor(0, 1);
lcd.print("Temp F: ");
lcd.setCursor(7, 6);
lcd.print(tempF, 1);
delay(2000);
lcd.clear();
}
