unsigned long nextTimeout = 0;
const int LedPin = 10;
int ButtonPin = 4;
const int Idle = 0;
const int LedOn = 1;
int LedState = Idle;

void setup() {
  pinMode(LedPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
}
void loop() 
{
  switch (LedState) 
  { case LedOn:
   digitalWrite(LedPin, HIGH);
   if (timerHasExpired() == true)
   {
   startTimer(2000);
   LedState = Idle;
   }
   
  case Idle:
  digitalWrite(LedPin, LOW);
  if (digitalRead (ButtonPin) == HIGH)
  {
    LedState = LedOn;
  }
  break;
  }
}
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
