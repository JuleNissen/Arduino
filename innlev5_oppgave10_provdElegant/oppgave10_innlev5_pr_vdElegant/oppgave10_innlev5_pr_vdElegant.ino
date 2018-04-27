/*Lager en temperaturmåler som printer  temp. i C og F
 * Ledpin som lyser når temp går over en gitt grenseverdi.
 * To knapper som skal øke/senke den gitte grenseverdien.
 * prøvd å skrive 'elegant'
 */
 #include <LiquidCrystal.h>
 LiquidCrystal lcd(12,11,5,4,3,2);
const int LED_PIN = 13;
const int TEMP_PIN = A0;
const int BUTTON0 = 7;
const int BUTTON1 = 8;
const int LIMIT = 20; //Grenseverdi for LED dioden
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
getTemps();
printTemps();
checkLimitValue();
}

float getTemps()
{
int tempReading = analogRead(TEMP_PIN);
float tempVolts = tempReading * 5 / 1024.0;
float tempC = (tempVolts - 0.5) * 100.0;
float tempF = tempC * 9.0 / 5.0 + 32.0;
}

float printTemps()
{
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

void checkLimitValue()
{
  if (LIMIT <= tempC)
{
digitalWrite(LED_PIN, HIGH);  
}
}
