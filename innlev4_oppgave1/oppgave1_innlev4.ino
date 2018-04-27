void setup()
{
    Serial.begin(9600);
}
  
void loop()
{
     int currentDayNo = 8;
     printNameOfDay(currentDayNo);
}
  
void printNameOfDay(int dayNumber)
{
    switch (dayNumber)
    { 
     case 1: (dayNumber == 1);
        Serial.println("Monday");
        break;
     case 2: (dayNumber == 2);
        Serial.println("Tuesday");
        break;
        
     case 3: (dayNumber == 3);
        Serial.println("Wednesday");
        break;
        
     case 4: (dayNumber == 4);
        Serial.println("Thursday");
        break;
        
     case 5: (dayNumber == 5);
        Serial.println("Friday");
        break;
        
     case 6: (dayNumber == 6);
       Serial.println("Saturday");
       break;
       
     case 7: (dayNumber == 7);
        Serial.println("Sunday");
        break;
    }
}
