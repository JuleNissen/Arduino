void setup() {
    Serial.begin(9600);
  }
  
  void loop() {
    int choice = 1;
  
    switch (choice)
    {
      case 1:
        Serial.println("I like banana");
        break;
      case 2:
        Serial.println("I like apple");
        break;
    }
  }
