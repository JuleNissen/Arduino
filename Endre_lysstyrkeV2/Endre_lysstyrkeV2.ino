const int button1Pin = 5;  // pushbutton 1 pin
const int button2Pin = 3;  // pushbutton 2 pin
int ledPin =  10;    // LED pin
int button1State, button2State;  // variables to hold the pushbutton states

int ledIntens = 0; //ledIntensitet brukes videre

void setup()
{
  // Set up the pushbutton pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
ledIntens = constrain(ledIntens, 0, 255);
  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);

  
}

void loop()
{
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // if button1 or button 2 are pressed (but not both)
  if (((button1State == LOW) && (button2State == HIGH)))
  {
    ledIntens++;
    delay(50);
  }
  if ((button1State == HIGH) && (button2State == LOW))
  {
    ledIntens--;
   delay(50);
   
  }
  analogWrite(ledPin, ledIntens);
  delay(50);
}
