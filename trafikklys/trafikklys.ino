/**
 * Trafficlight system using switch cases
 * Keeps track of time using timeout method.
 */

const int RedPin (6);
//const int RED_PIN = 6;
const int BluePin (5);
const int GreenPin(8);
const int GreenPedPin(3);
const int RedPedPin(4);
unsigned long nextTimeout = 0;
const int S_CARS_STOP(0);
const int S_PREPARE_TO_DRIVE(1);
const int S_CARS_DRIVE(2);
const int S_PREPARE_TO_STOP(3);
int state = S_CARS_STOP;
int currentState = S_PREPARE_TO_STOP;
const int L1 (9);
const int L0 (10);

int buttonState1, buttonState2;

void setup()
{
  pinMode(RedPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(GreenPedPin, OUTPUT);
  pinMode(RedPedPin, OUTPUT);
  pinMode(L0, INPUT);
  pinMode(L1, INPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:
}
void loop()
{
  setTrafficLights();
  printState(state);
  changeStateTo(state);

}

void setTrafficLights()
{
  buttonState1 = digitalRead(L1);
  buttonState2 = digitalRead(L0);
  switch (state)
  {
      if (buttonState1 == HIGH && buttonState2 == LOW)
      {
      case S_CARS_STOP: //Stop Red light
        if (timerHasExpired() == true)
        {
          digitalWrite(BluePin, LOW);
          digitalWrite(GreenPin, LOW);
          digitalWrite(RedPin, HIGH);
          digitalWrite(GreenPedPin, HIGH);
          digitalWrite(RedPedPin, LOW);
          //startTimer(5000);
          state = S_PREPARE_TO_DRIVE;
        }
      }
      break;


      if (buttonState1 == HIGH && buttonState2 == HIGH)
      {
      case S_PREPARE_TO_DRIVE: //Prepare to drive Red and Blue lights
        if (timerHasExpired() == true)
        {
          digitalWrite(GreenPedPin, LOW);
          digitalWrite(GreenPin, LOW);
          digitalWrite(RedPin, HIGH);
          digitalWrite(BluePin, HIGH);
          digitalWrite(RedPedPin, HIGH);
          startTimer(1000);
          state = S_CARS_DRIVE;
        }
      }
      break;


      if (buttonState1 == LOW && buttonState2 == LOW);
      { case S_CARS_DRIVE: //Drive Green light
        if (timerHasExpired() == true)
        {
          digitalWrite(BluePin, LOW);
          digitalWrite(RedPin, LOW);
          digitalWrite(GreenPin, HIGH);
          digitalWrite(GreenPedPin, LOW);
          digitalWrite(RedPedPin, HIGH);
          startTimer(2000);
          state = S_PREPARE_TO_STOP;
        }
      }
      break;


      if (buttonState1 == LOW && buttonState2 == HIGH)
      { case S_PREPARE_TO_STOP: //Prepare to Stop Blue light
        if (timerHasExpired() == true)
        {
          digitalWrite(RedPin, LOW);
          digitalWrite(GreenPin, LOW);
          digitalWrite(BluePin, HIGH);
          digitalWrite(RedPedPin, HIGH);
          digitalWrite(GreenPedPin, LOW);
          startTimer(2000);
          state = S_CARS_STOP;
        }
      }
      break;

    default: //Something is wrong blink Blue light
      digitalWrite(BluePin, HIGH);
      startTimer(1000);

      digitalWrite(BluePin, LOW);
      startTimer(1000);
  }
}

void changeStateTo(int newState)
{
  Serial.print("State change from ");
  printState(currentState);
  Serial.print (" to ");
  printState(newState);
  Serial.println(); //add a new line to feed to
  currentState = newState;
}

void printState(int state)
{
  switch (state)
  {
    case S_PREPARE_TO_STOP:
      Serial.print("S_PREPARE_TO_STOP");
      break;

    case S_CARS_STOP:
      Serial.print("S_CARS_STOP");
      break;

    case S_PREPARE_TO_DRIVE:
      Serial.print("S_PREPARE_TO_DRIVE");
      break;

    case S_CARS_DRIVE:
      Serial.print("S_CARS_DRIVE");
      break;

    default:
      Serial.print("ERROR!");
      break;
  }
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
