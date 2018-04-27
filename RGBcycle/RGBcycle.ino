int redLEDPin = 1;
int greenLEDPin = 2;
int blueLEDPin = 3;


void setup() {
  // put your setup code here, to run once:
pinMode(redLEDPin, OUTPUT);
pinMode(greenLEDPin, OUTPUT);
pinMode(blueLEDPin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  
analogWrite(redLEDPin, 1);
delay(500);
analogWrite(greenLEDPin, 1);
delay(500);
analogWrite(blueLEDPin, 1);
delay(500);
}
