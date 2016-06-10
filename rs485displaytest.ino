/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver  
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent

 
 */
 
#include <SPI.h>
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


 byte lijst[] = { 
   0b11101110, //0
   0b00101000, //1
   0b11001101, //2
   0b01101101, //3
   0b00101011, //4
   0b01100111, //5
   0b11100111, //6
   0b00101100, //7
   0b11101111, //8
   0b01101111, //9
};
/*
byte lijst[] = { 
0,
32,
40,
8,
0,
64,
97,
205,
7,
4,
64,
97,
109,
13,
4,
0,
224,
43,
12,
0,
64,
193,
103,
13,
4,
64,
193,
231,
15,
4,
64,
33,
44,
8,
0,
64,
225,
239,
15,
4,
64,
225,
111,
13,
4,
64,
161,
238,
11,
4
};
*/
const int chipSelectPin = 10;
const int enablePin = A1;
const int PowerPin = 9;

byte da=0b10101111;
byte db=0b11100011;
byte dc=0b11000110;
byte dd=0b11101001;
byte de=0b11000111;


byte PUNT  = 0b00010000;
byte BLANK = 0b00000000;
byte c2[15];
int i;
byte a, b;

int writeSpi(byte M, byte L);


void setup() {
  // initialize serial:
  Serial.begin(9600);
  SPI.begin();

  // initalize the  data ready and chip select pins:
  pinMode(enablePin, OUTPUT);
  pinMode(chipSelectPin, OUTPUT);   
  pinMode(PowerPin, OUTPUT); 
  digitalWrite(PowerPin, HIGH);  
  digitalWrite(enablePin, LOW);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  i=0;
  

}

void loop() {

  // print the string when a newline arrives:
    if(stringComplete) {
    
      a= inputString[0];
      b= inputString[1];
      writeSpi(lijst[i%10], lijst[b]);
      i+=1;
      stringComplete = false;
      inputString = "";
    }

 
}



/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:

    if (inChar == '\n') {
      stringComplete = true;
      inputString += '\0';
    } 
    
  }
}



int writeSpi(byte M, byte L){
    digitalWrite(chipSelectPin, LOW);
      SPI.transfer(L);
      SPI.transfer(M);
    digitalWrite(chipSelectPin, HIGH);       
}

