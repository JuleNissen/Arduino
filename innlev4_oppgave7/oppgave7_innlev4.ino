const int ButtonPin (4);

void setup() {
  pinMode(ButtonPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  isButtonPressed();
  delay(100);
}
boolean isButtonPressed()
 {
  boolean ButtonPressed = false;
  if (digitalRead(ButtonPin) > 0)
  {
    ButtonPressed = true;
      Serial.println(true);
  }
  else
  {
    ButtonPressed = false;
      Serial.println(false);
  }
  return ButtonPressed;

 }

