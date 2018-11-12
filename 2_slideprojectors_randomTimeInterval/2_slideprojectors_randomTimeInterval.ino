/*
Arduino programma dat je 2 diaprojectoren (kodak carrousels) laat aansturen met random waardes.
Oktober 2017- Hendrik Leper (initially made for Matthijs Vuijk)
*/

#define RP1 9      // Define the relay pin 1 &
#define RP2 10      // relay pin 2
/*
#define RP3 11      // 3
#define RP4 12      // 4
*/
//  - - - deze variabelen zijn te veranderen - - -  //
int minRandomInterval = 2000;      // minimale interval tussen dia's in milliseconden 1000 = 1 seconde
int maxRandomInterval = 20000;      // minimale interval tussen dia's in milliseconden 1000 = 1 seconde
boolean debug = true;    // print



//  - - - deze variabelen zijn NIET te veranderen - - -  //
int randomInterval1;
int relayState1 = LOW;
unsigned long previousMillis1 = 0;        // will store last time Relay was updated
long OnTime1;           // milliseconds of on-time
long OffTime1;          // milliseconds of off-time
int randomInterval2;
int relayState2 = LOW;
unsigned long previousMillis2 = 0;        // will store last time Relay was updated
long OnTime2;           // milliseconds of on-time
long OffTime2;          // milliseconds of off-time
int randomInterval3;
/*
int relayState3 = LOW;
unsigned long previousMillis3 = 0;        // will store last time Relay was updated
long OnTime3;           // milliseconds of on-time
long OffTime3;          // milliseconds of off-time
int randomInterval4;
int relayState4 = LOW;
unsigned long previousMillis4 = 0;        // will store last time Relay was updated
long OnTime4;           // milliseconds of on-time
long OffTime4;          // milliseconds of off-time
*/
int pulseTime = 200;      // duur van de electrische pulse die de projector doet voortgaan


void setup()
{
  pinMode(RP1, OUTPUT); 
  pinMode(RP2, OUTPUT);
  /*
  pinMode(RP3, OUTPUT); 
  pinMode(RP4, OUTPUT);
  */
  OnTime1 = pulseTime;
  OnTime2 = pulseTime;
  /*
  OnTime3 = pulseTime;
  OnTime4 = pulseTime;
  */
  if (debug) {
    Serial.begin(9600);
    delay(1000);
    Serial.println("-- started --");
    delay(500);
  }
}

void loop()
{
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();
 
  if((relayState1 == HIGH) && (currentMillis - previousMillis1 >= OnTime1))
  {
    relayState1 = LOW;  // Turn it off
    previousMillis1 = currentMillis;  // Remember the time
    digitalWrite(RP1, relayState1);  // Update the actual LED
  }
  else if ((relayState1 == LOW) && (currentMillis - previousMillis1 >= OffTime1))
  {
    relayState1 = HIGH;  // turn it on
    previousMillis1 = currentMillis;   // Remember the time
    digitalWrite(RP1, relayState1);    // Update the actual LED
    randomInterval1 = random(minRandomInterval,maxRandomInterval);
    
  }
  
  if((relayState2 == HIGH) && (currentMillis - previousMillis2 >= OnTime2))
  {
    relayState2 = LOW;  // Turn it off
    previousMillis2 = currentMillis;  // Remember the time
    digitalWrite(RP2, relayState2);  // Update the actual LED
  }
  else if ((relayState2 == LOW) && (currentMillis - previousMillis2 >= OffTime2))
  {
    relayState2 = HIGH;  // turn it on
    previousMillis2 = currentMillis;   // Remember the time
    digitalWrite(RP2, relayState2);   // Update the actual LED
    randomInterval2 = random(minRandomInterval,maxRandomInterval);
  }
}

