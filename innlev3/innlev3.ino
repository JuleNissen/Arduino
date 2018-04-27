int LED_PIN = 11;
const int WAIT_ONE_SEC = 1000;

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
}
    
void loop()
{
    fadeLedIn(LED_PIN);
    //SetLightIntensity(LED_PIN, 20);
    //turnLedOn(ledPin);
    waitOneSec();
    fadeLedOut(LED_PIN);
    //SetLightIntensity(LED_PIN, 200);
    //turnLedOff(ledPin);
    waitOneSec();
}

void fadeLedIn(int ledPin)
{
  for (int brightness = 0; brightness <= 255; brightness++)
  {
  analogWrite(ledPin, brightness);
  delay(20);
  }
}

void fadeLedOut(int ledPin)
{
  for (int brightness = 255; brightness >= 0; brightness--)
  {
  analogWrite(ledPin, brightness);
  delay(20);
  }
}

void SetLightIntensity(int ledPin, int intensity)
{
  analogWrite(ledPin, intensity);
}
 

void turnLedOn(int LED_PIN)
{
  digitalWrite(LED_PIN, HIGH);
}

void turnLedOff(int LED_PIN)
{
  digitalWrite(LED_PIN, LOW);
}

void waitOneSec()
{
  delay(WAIT_ONE_SEC);
}
