/**
 * Blinking ligt using only method calls in loop
 * @auhtor Jahn-Willy Nøstdahl
 */
int I = (2, 6);
const int LED_PIN(I);
const int WAIT_ONE_SEC = 1000;

void setup() 
{
    pinMode(LED_PIN, OUTPUT);
}
    
void loop()
{
    turnLedOn();
    waitOneSec();
    turnLedOff();
    waitOneSec();
}

void turnLedOn()
{
digitalWrite(LED_PIN, HIGH);
}

void turnLedOff()
{
  digitalWrite(LED_PIN, LOW);
}

void waitOneSec()
{
  delay(WAIT_ONE_SEC);
}

