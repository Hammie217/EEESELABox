/* Libraries:
 *  FastLed - Daniel Garcia
 * Pins:
 * A1 - middle of potential divider  
 * 
 */
 //LED strip parameters
#include "FastLED.h"
#include <math.h>

#define LED_PIN     5
#define NUM_LEDS    144
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
#define averagingConstant 20
#define greenTolerance 2
#define orangeTolerance 15
CRGB leds[NUM_LEDS];
//Global variable init
double potentiometerVoltage=0;
//

void setup() {
  Serial.begin(9600);
  //Define pins
  //setup led strip
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    //
}

void loop() {
    //display leds
    LEDStrip();
    FastLED.show();
    //
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
  if((potentiometerVoltage>(NUM_LEDS/2)-greenTolerance)&&(potentiometerVoltage<(NUM_LEDS/2)+greenTolerance)){

      leds[(int)potentiometerVoltage] = CRGB::Green;
  }
  else if((potentiometerVoltage>(NUM_LEDS/2)-orangeTolerance)&&(potentiometerVoltage<(NUM_LEDS/2)+orangeTolerance)){
      leds[(int)potentiometerVoltage] = CRGB::Orange;
  }
  else{
    leds[(int)potentiometerVoltage] = CRGB::Red;
  }

  
  
}

