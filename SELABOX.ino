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
    leds[(int)potentiometerVoltage] = CRGB::Black;
  potentiometerVoltage = analogRead(1);
  delay(1);
  potentiometerVoltage += analogRead(1);
  delay(1);
  potentiometerVoltage += analogRead(1);
  delay(1);
  potentiometerVoltage += analogRead(1);
  delay(1);
  potentiometerVoltage /=4;
  potentiometerVoltage -=320;
  potentiometerVoltage *= NUM_LEDS;
  potentiometerVoltage = round(potentiometerVoltage/350);
  if(potentiometerVoltage<0){
    potentiometerVoltage =0;
  }
  else if(potentiometerVoltage >143){
    potentiometerVoltage =143;
  }
  Serial.println(potentiometerVoltage);
  leds[(int)potentiometerVoltage] = CRGB::White;
  
  
}

