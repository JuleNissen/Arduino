 
const int TEMP_PIN = A0;
  const int POT_PIN = A1;
  const int LED_PIN = 13;
  
  void setup() {
    pinMode( LED_PIN, OUTPUT );
    Serial.begin( 9600 );
  }
  
  void loop() {
    // Read temperature from sensor, return as degrees C
    float tempInC = getTemperatureInC( TEMP_PIN ); 
    // Convert from Celsius to Fahrenheit
    float tempInF = celsiusToFahrenheit( tempInC );
  
    // Read from potmeter, and return in degrees C
    float tempLimitInC = getTempLimit( POT_PIN );
  
    if ( tempInC > tempLimitInC )
    {
      turnLedOn( LED_PIN );
    }
    else
    {
      turnLedOff( LED_PIN );
    }
    showInformation( tempLimitInC, tempInC, tempInF ); // Prints info to Serial Monitor
  }
  
  /**
   * Prints information about the temperature to the
   * serial monitor
   */
  void showInformation( float tempLimit, float tempC, float tempF )
  {
    Serial.print("Temp limit: ");
    Serial.print( tempLimit );
    Serial.print(" Temp in C: ");
    Serial.print( tempC );
    Serial.print(" Temp in F: ");
    Serial.println( tempF );
    delay(500);
  }
  
  /**
   * Returns the temperature from the temperature sensor
   * as degrees Celsius.
   */
  float getTemperatureInC( int sensorPin )
  {
    float measuredTempInC = 0;
    float measuredVoltage = 0;
    int sensorInput = analogRead( sensorPin );
    measuredVoltage = 5.0/1023 * sensorInput;
    measuredTempInC = 25 + (measuredVoltage - 0.750)*100;
    return measuredTempInC;
  }
  
  /**
   * Converts the temperature from Celsius to Fahrenheit
   */
  float celsiusToFahrenheit( float tempC )
  {
    return tempC*9.0/5.0 + 32; //Note that we use float, i.e. 9.0 not 9
  }
  
  /**
   * Returns the temperature limit based on the
   * input from the potmeter.
   * The range is set to 20 to 30.
   */
  int getTempLimit( int potPin )
  {
    int tempLimit;
    tempLimit = map( analogRead( potPin ), 0, 1023, 20, 30 );
    return tempLimit;
  }
  
  /**
   * Turns on the LED-pin given by the format
   */
  void turnLedOn( int ledPin )
  {
    digitalWrite( ledPin, HIGH );
  }
  
  /**
   * Turns off the LED-pin given by the parameter
   */
  void turnLedOff( int ledPin )
  {
    digitalWrite( ledPin, LOW );
  }
    
