#include <Servo.h>

Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 
int button = 2;  // The button will be on Pin 7 


void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
pinMode(pos, OUTPUT);
pinMode(button, INPUT); 
digitalWrite (button, LOW);
} 

void loop() 
{ 
  
    if (digitalRead(button) == LOW)

  for(pos = 0; pos < 90; pos += 90)  // goes from 0 degrees to 90 degrees 
  {                                  // in steps of  degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
                          // waits 1s for the servo to reach the position 
  } 
  if (digitalRead(button) == HIGH) 
  
  for(pos = 90; pos>=90; pos-=90)     // goes from 90 degrees to 0 degrees 
  {                                
     myservo.write(pos);              // tell servo to go to position in variable 'pos' 
  delay(50);                             // waits 50ms for the servo to reach the position 
  }
  
}
