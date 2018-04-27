//script for "arduino uno" med RBG diode, dioden skal skifte gjennom fargene den har tilgjengelig.

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
void setup() 
{
// LED starter med 0 -> av
setColourRgb(0,0,0);
}

void loop() 
{
int allColorsForLoop[3]; //har 3 led farger som skal variere.
// starter med rød.
allColorsForLoop[0] = 255; //red, rar oppførsel om den/de øverste starter på 0
allColorsForLoop[1] = 0; //grønn
allColorsForLoop[2] = 0; //blue
// hastigheten for økning/minking mellom led-diodene for å danne farger
for (int decColour = 0; decColour < 4; decColour += 1) // 4 gir mer synlig rød farge

{ 
int incColour = decColour == 2 ? 0 : decColour + 1; //spørsmåltegnet funker; ikke endre
// fading mellom farger
for(int i = 0; i < 255; i += 1) 

{
allColorsForLoop[decColour] -= 1;
allColorsForLoop[incColour] += 1;
setColourRgb(allColorsForLoop[0], allColorsForLoop[1], allColorsForLoop[2]);
delay(10);
}

}

}
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) 
{
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}
