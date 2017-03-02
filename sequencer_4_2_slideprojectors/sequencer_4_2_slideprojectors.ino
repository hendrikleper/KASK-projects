/*
Arduino programma dat je 2 diaprojectoren (kodak carrousels) laat sequencen.
Arduino pogramm that lets you sequence 2 kadak Carrousel Slide projectors.

Maart 2017- Hendrik Leper (initially made for Chantal van Rijt
*/

#include <Metro.h>  // Include Metro library
#define LED 13      // Define the led's pin 
#define RP1 11      // Define the relay pin 1 &
#define RP2 12      // relay pin 2

//  - - - deze variabelen zijn te veranderen - - -  //
int maxSteps = 80;        // 80 slides in een carrousel,
// maar het kan ook minder of meer zijn afhankelijk van het ritme
int interVal = 3000;      // interval tussen dia's in milliseconden 1000 = 1 seconde
// mag niet minder dan 800 zijn
int pulseTime = 300;      // duur van de electrische pulse die de projector doet voortgaan
boolean debug = false;    // print

int RStepState1[] = {     // bepaal hier je steps voor projector 1
  1, 1, 1, 0, 1, 1, 1, 0, // 1 = aan 0 = uit
  1, 0, 0, 0, 1, 0, 0, 0, // 10 rijden van 8 stappen
  1, 0, 0, 0, 1, 0, 0, 0,
  1, 0, 0, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 1, 0, 1, 0, 1, 0
};
int RStepState2[] = {     // bepaal hier je steps voor projector 2
  0, 1, 0, 1, 0, 1, 0, 1, // 1 = aan 0 = uit
  0, 1, 0, 1, 0, 1, 0, 1, // 10 rijden van 8 stappen
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1,
  0, 1, 0, 1, 0, 1, 0, 1
};

//  - - - deze variabelen zijn NIET te veranderen - - -  //
int ledState = LOW;  // houdt de staat van de leds en relays bij
int RState1 = LOW;
int RState2 = LOW;
int counter = 0;      // houdt de stappen bij
Metro ledMetro = Metro(interVal); // Instanciate a metro object and set the interval to ....

void setup()
{
  pinMode(LED, OUTPUT); pinMode(RP1, OUTPUT); pinMode(RP2, OUTPUT);
  digitalWrite(LED, ledState); digitalWrite(RP1, RState1); digitalWrite(RP2, RState2);
  Serial.begin(9600);
  delay(1000);
  if (debug) {
    Serial.println("-- metronoom started --");
    delay(1000);
  }
}

void loop()
{ // - - - counter reset - - - - - - - - -
  if (counter >= maxSteps) {
    counter = 0;
  }
  if (ledMetro.check() == 1) {        // check if the metro has passed its interval .
    if (RStepState1[counter] == 1) {  // checks the steps 
      if (RState1 == LOW)  {
        RState1 = HIGH;
        if (debug) {
          Serial.print("[R1]");
        }
      } 
    }
    if (RStepState2[counter] == 1) {
      if (RState2 == LOW)  {
        RState2 = HIGH;
        if (debug) {
          Serial.print("[R2]");
        }
      } else {
        //
      }
    }
    if (ledState == HIGH)  {
      ledState = LOW;
      RState1 = LOW;
      RState2 = LOW;
      ledMetro.interval(interVal - pulseTime); // if the pin is HIGH, set the interval to ... seconds.
    }
    else {
      if (debug) {
        Serial.println(counter);
      }
      ledMetro.interval(pulseTime); // if the pin is LOW, set the interval to ... seconds.
      ledState = HIGH;
      counter++;
    }
    digitalWrite(LED, ledState);
    digitalWrite(RP1, RState1);
    digitalWrite(RP2, RState2);
  }
}


