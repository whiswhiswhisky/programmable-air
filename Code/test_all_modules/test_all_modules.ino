// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// Simple pick and place
// IO board 1 connected to channel 4
// Valve board 1 connected to SMD pick and place syringe
//

#include <Adafruit_NeoPixel.h>

const int pump[2] = {10, 11};

#define OPEN 1
#define CLOSE 0
// vacuum, atmosphere, pressure
const int valve[9] = {  9,  8,  7, \
                        5,  4,  A4, \
                        A0, A1, A2
                      };

const int sense[3] = {6, A5, A3};

#define SCK 13

#define neopixelPin 12
#define btn1 2
#define btn2 3

Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(3, neopixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  while(!Serial);

  // Initiate with all valve and pumps off
  initializePins();

  //switch on pumps
  digitalWrite(pump[0], HIGH);
  digitalWrite(pump[1], HIGH);
}

void loop() {
    Serial.println("loop");
    if(millis() < 30000){
      setValve(1, OPEN);
      setValve(2, CLOSE);
    }
    else{
      setValve(1, CLOSE);
      setValve(2, OPEN);
    }
    delay(1000);
}

void setAllValves(int position) {
  if (position == OPEN) {
    for (int i = 0; i < 12; i++) {
      digitalWrite(valve[i], HIGH);
    }
  }

  if (position == CLOSE) {
    for (int i = 0; i < 12; i++) {
      digitalWrite(valve[i], LOW);
    }
  }
}

void setValve(int number, int position) {
  if (position == OPEN) {
    digitalWrite(valve[number], HIGH);
  }

  if (position == CLOSE) {
    digitalWrite(valve[number], LOW);
  }
}

void initializePins(){
  for (int i = 0; i < 12; i++) {
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i], LOW);
  }
  for (int i = 0; i < 4; i++) {
    pinMode(sense[i], INPUT);
  }
  pinMode(SCK, OUTPUT);

  for (int i = 0; i < 2; i++) {
    pinMode(pump[i], OUTPUT);
    digitalWrite(pump[i], LOW);
  }
}
