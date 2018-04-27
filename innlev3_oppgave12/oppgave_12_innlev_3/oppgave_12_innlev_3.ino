// We'll use analog input 0 to measure the temperature sensor's
// signal pin.

const int temperaturePin = A0;
const int LED_PIN = 13; 

void setup()
{
  pinMode(13, OUTPUT); //skrevet selv
	Serial.begin(9600); //Initialize serial port & set baud rate to 9600 bits per second (bps)
}


void loop()
{


	float voltage, degreesC, degreesF; //Declare 3 floating point variables

	voltage = getVoltage(temperaturePin); //Measure the voltage at the analog pin

	degreesC = (voltage - 0.5) * 100.0; // Convert the voltage to degrees Celsius

	
	//Now print to the Serial monitor. Remember the baud must be 9600 on your monitor!
	// These statements will print lines of data like this:
	// "voltage: 0.73 deg C: 22.75 deg F: 72.96"
	
	Serial.print("voltage: ");
	Serial.print(voltage);
	Serial.print("  deg C: ");
	Serial.print(degreesC);
  
  if (degreesC > 22)
  {
    digitalWrite(LED_PIN, HIGH);
    
  }
  else digitalWrite(LED_PIN, LOW); //if og else skrevet selv, ellers er koden tatt fra circuit 7
	
	delay(1000); // repeat once per second (change as you wish!)
}


float getVoltage(int pin) 	//Function to read and return
							//floating-point value (true voltage)
							//on analog pin 
{

	return (analogRead(pin) * 0.004882814);	
	// This equation converts the 0 to 1023 value that analogRead()
	// returns, into a 0.0 to 5.0 value that is the true voltage
	// being read at that pin.
}

// Other things to try with this code:

//   Turn on an LED if the temperature is above or below a value.

//   Read that threshold value from a potentiometer - now you've
//   created a thermostat!

