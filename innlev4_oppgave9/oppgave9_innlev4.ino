unsigned long nextTimeout = 0;
const int LedPin (10);
int ButtonPin (4);

void setup() {
pinMode(LedPin, OUTPUT);
pinMode(ButtonPin, INPUT);
nextTimeout = millis();

}

void loop() 
{
 turnLedPinOn();
 turnLedPinOff();
}

void turnLedPinOn()
{
switch (digitalRead(ButtonPin))
{
  case HIGH:
  digitalWrite(LedPin, HIGH);
  delay(2000);
}
}

void turnLedPinOff()
{
switch (digitalRead(ButtonPin))
{
  case LOW:
  digitalWrite(LedPin,LOW);
  break;
}
}
