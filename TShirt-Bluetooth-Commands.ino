/*
    Name:     LED_Lights_BLE_App_All_LEDs_Test.ino
    Created:  04/06/2022
    Author:   Pete Januarius

    The Arduino code to test your Thunkable App.
    Lights up ALL LEDs and not just the first one
*/
#include <FastLED.h>
#include <SoftwareSerial.h>

#define DATA_PIN 3
#define RX 13
#define TX 12
#define NUM_LEDS 100

char receivedChar;
boolean isOff = true;
int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 200;

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB windowsColors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow};

SoftwareSerial BTSerial(RX,TX);

// put your setup code here, to run once:
void setup() {
  // Initialise Bluetooth communication
  BTSerial.begin(9600);   
  Serial.begin(9600);   
  delay(100);
  Serial.println("<Arduino is ready>");   
  
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  Serial.println("<LED strip is ready>");
  delay(2000);

  windowsThree(5);
}

void loop() {
 recvOneChar();
 processCommand();

 delay(50);
}

void recvOneChar() {
  if (BTSerial.available() > 0) {
    receivedChar = BTSerial.read();
  }
}

void processCommand() {
  if(receivedChar == 'A') {
    Serial.println("blink...");
    blink();

    isOff = false;
  }
  else if(receivedChar == 'B' || receivedChar == 'b') {
    red();

    isOff = false;
  }
  else if(receivedChar == 'C' || receivedChar == 'c') {
    green();

    isOff = false;
  }
  else if(receivedChar == 'D' || receivedChar == 'd') {
    blue();

    isOff = false;
  }
  else if(receivedChar == 'E' || receivedChar == 'e') {
    yellow();

    isOff = false;
  }
  else if(receivedChar == 'F' || receivedChar == 'f') {
    fade();

    isOff = false;
  }
  else if(receivedChar == 'W' || receivedChar == 'w') {
    windowsThree(5);

    isOff = false;
  }
  else if(receivedChar == 'T' || receivedChar == 't') {
    travel();

    isOff = false;
  }  
  else if(receivedChar == 'R' || receivedChar == 'r') {
    travelAlternate();

    isOff = false;
  }  
  else if(receivedChar == 'S' || receivedChar == 's') {
    randomStrobe();

    isOff = false;
  }  
  else if(receivedChar == 'Z' || receivedChar == 'z') {
    incBrightness();

    isOff = false;
  }    
  else if(receivedChar == 'Y' || receivedChar == 'y') {
    decBrightness();

    isOff = false;
  }    
  else if (receivedChar == 'O' || receivedChar == 'o') {
    // turn lights off
    if(isOff == false){
      off();
      isOff = true;
    }
  }

  delay(15);
}

void off() {
  for(int i=0; i < NUM_LEDS; i++) {
    // Turn the LED on, then pause
    leds[i] = CRGB::Black;       
  }
  FastLED.show();   
}

void blink() {
  for(int i=0; i < NUM_LEDS; i++) {
    // Turn the LED on, then pause
    leds[i] = CRGB::Red;       
  }
  FastLED.show(); 
  delay(500);
  for(int i=0; i < NUM_LEDS; i++) {
      // Turn the LED on, then pause
      leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(500); 
}

void red() {
   for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].setRGB(255,0,0);  // Set Color HERE!!!     
   }  
   FastLED.show();
}

void green() {
   for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].setRGB(0,255,0);  // Set Color HERE!!!     
   }    
   FastLED.show();
}

void blue() {
   for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].setRGB(0,0,255);  // Set Color HERE!!!     
   }  
   FastLED.show();
}

void yellow() {
   for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].setRGB(255,255,0);  // Set Color HERE!!!     
   }  
   FastLED.show();
}

void fade() {
   for(int i = 0; i < NUM_LEDS; i++ ) {
     leds[i].setRGB(0,255,250);  // Set Color HERE!!!
     leds[i].fadeLightBy(brightness);
   }
   FastLED.show();
   brightness = brightness + fadeAmount;
   // reverse the direction of the fading at the ends of the fade: 
   if(brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
   }    
   delay(4);  // This delay sets speed  
 }

 void windowsThree(int numLEDsInRow) {
  for(int i=0; i<25; i++) {
     leds[i] = CRGB::Red;
  }
  for(int i=25; i<50; i++) {
     leds[i] = CRGB::Blue;
  }
  for(int i=50; i<75; i++) {
     leds[i] = CRGB::Green;
  }
  for(int i=75; i<100; i++) {
     leds[i] = CRGB::Yellow;
  }
  FastLED.show();
 }

 void travel() {
   for (int i = 0; i < NUM_LEDS; i++) {
     leds[i] = CRGB::DeepPink;  //set the led to Pink
     FastLED.show();       //start the leds
     leds[i] = CRGB::Black;  //clear the led
     delay(50);          //Wait before moving to next let 
   } 
 }

 void travelAlternate() {
   for (int i = 0; i < NUM_LEDS; i++) {
     leds[i] = CRGB::DeepPink;  //set the led to Pink
     FastLED.show();       //start the leds
     leds[i] = CRGB::Black;  //clear the led
     delay(50);          //Wait before moving to next led
   } 
   for (int j = NUM_LEDS-1; j >= 0; j--) {
     leds[j] = CRGB::DeepPink;  //set the led to Pink
     FastLED.show();       //start the leds
     leds[j] = CRGB::Black;  //clear the led
     delay(50);          //Wait before moving to next led
   } 
 }

 void randomStrobe() {
  uint8_t color = random8();
  uint8_t num = random8(NUM_LEDS);
  leds[num] = CHSV(color, 255, 255);  //set random led to random color
  FastLED.show();       //start the leds
  leds[num] = CRGB::Black;  //clear the led
  delay(5);          //Wait before moving to next led 
 }

 void incBrightness() {
  brightness += 10;
  if(brightness >= 255) {
    brightness = 200;
  }
  FastLED.setBrightness(brightness); 
 }

 void decBrightness() {
  brightness -= 10;
  if(brightness <= 150) {
    brightness = 200;
  }
  FastLED.setBrightness(brightness); 
 } 
