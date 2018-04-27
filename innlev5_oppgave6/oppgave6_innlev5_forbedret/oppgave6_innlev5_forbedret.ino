/*Innlevring 5 oppgave 6
 * Rediger knob eksempel kode.
 * 
 */
#include <Servo.h>

Servo mainServo;  // create servo object to control a servo

const int POT_PIN = 0;  // analog pin used to connect the potentiometer

void setup() 
{
  mainServo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() 
{
int servoPosition getServoPos(POT_PIN);
setServoPos(servoPostition);
}
/*
 * 
 */
void setServoPos(int pos) //Setter hvilken vinkel servoen skal settes i, constrain holder servoen mellom 0-180 grader.
  {
    servoPos = constrain(pos, 0,180);
    mainServo.write(pos);
    if (pos >= 180) //ifølge oppgave skal servoen flyttes til 0 om vinkelen er <0 og 180 >180.
  {
    mainServo.write(180);
  }
  if (pos <= 0)
  {
    mainServo.write(0);
  }
    delay(150); //Delay brukes til å gi servoen tid til å komme til posisjon.
  }

  /*
   * 
   */
int getServoPos(int pin) //Leser analog input fra potensiometer, map gjør signalene fra 0-1023 til grader for servoen.
{
  int servoPos = analogRead(pin);
  servoPos = map(servoPos, 0, 1023, 0, 180);
  return servoPos;
  
}

