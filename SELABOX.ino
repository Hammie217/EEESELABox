/* Libraries:
 *  FastLed - Daniel Garcia
 *  Adafruit GFX
 *  led backapack library
 * Pins:
 * A1 - middle of potential divider  
 * D5 - LED Strip data
 * 7 Segment - (IO - 5v) (+ - 5V) (D - A4) (C - A5) 
 */

#include "FastLED.h"
#include <math.h>
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

 //LED strip parameters
#define LED_PIN     5
#define NUM_LEDS    144
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
#define averagingConstant 20 //caution this increases accuracy but slows the system down
#define greenTolerance 2
#define orangeTolerance 15
#define countdownSpeed 0.05
CRGB leds[NUM_LEDS];
//Global variable init
double potentiometerVoltage=0;
float countdown =100;
//matrix define
Adafruit_7segment matrix = Adafruit_7segment();
//


void setup() {
  Serial.begin(9600);
  //Define pins
  //setup led strip
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    //7 seg matrix
    matrix.begin(0x70);
    
    //
}

void loop() {
    //display leds
    LEDStrip();
    FastLED.show();
    //
    //display 7 seg
    if((int)countdown<=0){
     matrix.writeDigitNum(0, 0xF,false);
     matrix.writeDigitNum(1, 0xA,false);
     matrix.writeDigitRaw(3,6);
     matrix.writeDigitRaw(4,56);
    }
    else{
    matrix.print((int)countdown, DEC);
    countdown-=countdownSpeed;
    }
  matrix.writeDisplay();
    
}

void LEDStrip(){
    leds[(int)potentiometerVoltage] = CRGB::Black; //turn old led off
    // get average value to remove jumping
    potentiometerVoltage =0;
    for(int i =0;i<averagingConstant;i++)
    {
        potentiometerVoltage += analogRead(1);
        delay(1);
    }
  //number fiddling to change input into led numbers
  potentiometerVoltage /=averagingConstant;
  potentiometerVoltage -=320;
  potentiometerVoltage *= NUM_LEDS;
  potentiometerVoltage = round(potentiometerVoltage/350);
  //if negative make it led 0
  if(potentiometerVoltage<0){
    potentiometerVoltage =0;
  }
  else if(potentiometerVoltage >NUM_LEDS-1){ //if above end of strip make it the end of the strip
    potentiometerVoltage =NUM_LEDS-1;
  }
  //Serial.println(potentiometerVoltage); //debug line
  if((potentiometerVoltage>(NUM_LEDS/2)-greenTolerance)&&(potentiometerVoltage<(NUM_LEDS/2)+greenTolerance)){ // if centeral plus or minus 1 display green

      leds[(int)potentiometerVoltage] = CRGB::Green;
  }
  else if((potentiometerVoltage>(NUM_LEDS/2)-orangeTolerance)&&(potentiometerVoltage<(NUM_LEDS/2)+orangeTolerance)){ //if centeral plus or minus 9 display orange
      leds[(int)potentiometerVoltage] = CRGB::Orange;
  }
  else{ //else show red led
    leds[(int)potentiometerVoltage] = CRGB::Red;
  }

  
  
}

void countdownFunc(){

  
}

