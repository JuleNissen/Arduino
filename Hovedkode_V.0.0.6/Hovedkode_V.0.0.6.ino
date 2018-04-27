/*
    Controling a zumo-bot using IR-groundsensors, and distance sensors.
    by Markus Randa, Lars Ous, Frode Pedersen, Jahn Willy Nøstdahl, Øyvind Orre.
    Last modified 20.11.2017
*/

#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

// Constans for all the different speedsettings.
const int REVERSE_SPEED =    400; // 0 is stopped, 400 is full speed
const int TURN_SPEED =       400;
const int FORWARD_SPEED =    400;
const int REVERSE_DURATION = 200; // ms

ZumoBuzzer buzzer;
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

// Constansts for all the thresholds we will be using.
const int QTR_THRESHOLD = 1500;
const int IRDISTANCE_THRESHOLD = 40;
const int PROXIMITY_IRDISTANCE_THRESHOLD = 15;

// Constants for all the different states.
const int S_REVERSE =    0;
const int S_TURN_RIGHT = 1;
const int S_TURN_LEFT =  2;
const int S_FORWARD =    3;
const int S_HUNT =       4;
String states[] = {"S_REVERSE", "S_TURN_RIGHT", "S_TURN_LEFT", "S_FORWARD", "S_HUNT"};

unsigned long nextTimeout = 0;
int state;
boolean debug = true;

// Defining the pins for sensorarray.
const int NUM_SENSORS = 6;
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

// Constants different pins.
const int LED = 13;
const int LEFT_SENSOR =  A2;
const int RIGHT_SENSOR = A3;

void setup()
{
  // One time settings.
  Serial.begin(9600);
  reflectanceSensors.init();
  state = S_FORWARD;
  waitForButtonAndCountDown();
}

void loop()
{
  mainDrivingControl();
}

// This function controls all the main functions of the zumobot.
void mainDrivingControl()
{
  switch (state)
  {
    case S_FORWARD:
      // Sets motors to forward driving.
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      // If a track border is reached
      if (isBorderReached() == true)
      {
        // Start timer with the given duration
        startTimer(REVERSE_DURATION);
        // Endre tilstand til revers
        changeState(S_REVERSE);
      }
      // If opponent is detected.
      if (opponentDetected() == true)
      {
        // Change state to S_HUNT
        changeState(S_HUNT);
      }
      break;

    case S_REVERSE:
      // Sets motors to reverse driving.
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      // Hvis timer har utløpt
      if (timerHasExpired() == true)
      {
        // Read sensorarray
        sensors.read(sensor_values);
        // Start timer with the given duration
        startTimer(turnDuration());
        // Change state to Right- or Left driving.
        changeState(checkDirection());
      }
      break;

    case S_TURN_RIGHT:
      // Sets motors to right driving.
      motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      if (timerHasExpired() == true)
      {
        // Change state to forward driving
        changeState(S_FORWARD);
      }
      // If opponent is detected.
      if (opponentDetected() == true)
      {
        // Change state to S_HUNT
        changeState(S_HUNT);
      }
      break;

    case S_TURN_LEFT:
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      if (timerHasExpired() == true)
      {
        // Change state to forward driving.
        changeState(S_FORWARD);
      }
      // If opponent is detected.
      if (opponentDetected() == true)
      {
        // Change state to S_HUNT
        changeState(S_HUNT);
      }
      break;

    case S_HUNT:
      // This function is for following a target.

      // This part is for adjusting the right motor, when the left sensor detects a target.
      if (getDistanceToEnemy(LEFT_SENSOR) > IRDISTANCE_THRESHOLD && getDistanceToEnemy(RIGHT_SENSOR) < IRDISTANCE_THRESHOLD)
      {
        // Here we are using distance as a speed reduction on one belt, to make the robot turn.
        // We've also multiplied the distance with a constant we got after numerous tests, to make it turn better.
        motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED - (getDistanceToEnemy(LEFT_SENSOR) * 0.75));
      }
      // This parts is for adjusting the left motor, when the right sensor detects a target.
      if (getDistanceToEnemy(LEFT_SENSOR) < IRDISTANCE_THRESHOLD && getDistanceToEnemy(RIGHT_SENSOR) > IRDISTANCE_THRESHOLD)
      {
        // Here we are using distance as a speed reduction on one belt, to make the robot turn.
        // We've also multiplied the distance with a constant we got after numerous tests, to make it turn better.
        motors.setSpeeds(FORWARD_SPEED - (getDistanceToEnemy(RIGHT_SENSOR) * 0.75), FORWARD_SPEED);
      }
      // If both sensors detect that target is underneath the set threshold distance, it will drive at full speed right ahead.
      if ((getDistanceToEnemy(LEFT_SENSOR) < PROXIMITY_IRDISTANCE_THRESHOLD) && (getDistanceToEnemy(RIGHT_SENSOR) < PROXIMITY_IRDISTANCE_THRESHOLD))
      {
        changeState(S_FORWARD);
      }
      // Checks if border is reached.
      if (isBorderReached() == true)
      {
        // start the timer with given duration.
        startTimer(REVERSE_DURATION);
        // Change state to reverse.
        changeState(S_REVERSE);
      }
      break;
  }
}

void changeState(int newState)
{
  if (debug == true)
  {
    Serial.print("State changed from ");
    Serial.print(states[newState]);
    Serial.print(" to ");
    Serial.println(states[state]);
    state = newState;
  }
}

// Checks if the border is reached, and returns true or false.
boolean isBorderReached()
{
  sensors.read(sensor_values);
  boolean isDetected;
  if ((sensor_values[0] < QTR_THRESHOLD) || (sensor_values[5] < QTR_THRESHOLD))
  {
    isDetected = true;
  }
  else
  {
    isDetected = false;
  }
  return isDetected;
}


// Checks if opponent is detected, using the IR distance sensors.
boolean opponentDetected()
{
  boolean opponentIsDetected;
  if ((getDistanceToEnemy(LEFT_SENSOR) < IRDISTANCE_THRESHOLD) || (getDistanceToEnemy(RIGHT_SENSOR) < IRDISTANCE_THRESHOLD))
  {
    if (isBorderReached() == false)
    {
      opponentIsDetected = true;
    }
  }
  else
  {
    opponentIsDetected = false;
  }
  return opponentIsDetected;
}


// Checks what direction the zumo-bot should use, and returns the appropiate state.
int checkDirection()
{
  int newState;
  // Høyre
  if (sensor_values[0] < QTR_THRESHOLD)
  {
    newState = S_TURN_RIGHT;
  }
  // Venstre
  if (sensor_values[5] < QTR_THRESHOLD)
  {
    newState = S_TURN_LEFT;
  }
  return newState;
}

// This function gives off a random turning duration.
unsigned long turnDuration()
{
  unsigned long duration = 0;
  duration = random(300, 500);
  return duration;
}


// This function checks the distance of target using the IR distance sensors, and returns a value in cm.
float getDistanceToEnemy(int sensorpin)
{
  //Serial.print(sensorpin);
  int sensorValue = analogRead(sensorpin);
  double IRdistance = 187754 * pow(sensorValue, -1.51);
  //Serial.print(" - ");
  //Serial.println(IRdistance);
  return IRdistance;
}


// Counts down from 5 with sounds indicating the counting.
// And does a quick reverse
void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  digitalWrite(LED, LOW);

  // play audible countdown
  for (int i = 0; i < 3; i++)
  {
    delay(1000);
    buzzer.playNote(NOTE_G(3), 200, 15);
  }
  delay(1000);
  buzzer.playNote(NOTE_G(4), 500, 15);
  delay(1000);
  motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
  delay(99);
}

// Starts a timer.
void startTimer(unsigned long duration)
{
  nextTimeout = millis() + duration;
}


// Checks is timer is expired.
boolean timerHasExpired()
{
  boolean hasExpired;
  if (millis() > nextTimeout) {
    hasExpired = true;
  }
  else
  {
    hasExpired = false;
  }
  return hasExpired;
}
