/* We start by including the library */
#include "LedControl.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

#define buttonUp 9
#define buttonDown 8
#define cookerPin 7
LedControl lc1=LedControl(12,11,10,1); 


void setup() {
    //wake up the MAX72XX from power-saving mode 
   lc1.shutdown(0,false);
   //set a medium brightness for the Leds
     lc1.setIntensity(0,0);
   
   lc1.clearDisplay(0);
   
   pinMode(buttonUp, INPUT_PULLUP);
   pinMode(buttonDown, INPUT_PULLUP);
   pinMode(cookerPin, OUTPUT);
}

float desiredTemperature = 65.0;
int tempUp;
int tempDown;
float temp = 0.0;
void loop() {
//  delay(10000);
  printNumber(desiredTemperature);
  getAndPrintTemperature();
  tempUp = digitalRead(buttonUp);
  tempDown = digitalRead(buttonDown);
  
  if (tempUp == LOW)
    desiredTemperature += 0.5;
  else if (tempDown == LOW)
    desiredTemperature -= 0.5;
    
  if (temp < desiredTemperature)
    digitalWrite(cookerPin, LOW);
  else
    digitalWrite(cookerPin, HIGH);
    
  delay(100);
}

void printNumber(float number) {
  lc1.setDigit(0, 7, (byte) number / 10, false);
  lc1.setDigit(0, 6, (byte) number % 10, true);
  lc1.setDigit(0, 5, (byte) ((int) (number * 10) % 10), false);
  lc1.setDigit(0, 4, (byte) ((int) (number * 100) % 10), false);
}

void printNumber2(float number) {
  lc1.setDigit(0, 3, (byte) number / 10, false);
  lc1.setDigit(0, 2, (byte) number % 10, true);
  lc1.setDigit(0, 1, (byte) ((int) (number * 10) % 10), false);
  lc1.setDigit(0, 0, (byte) ((int) (number * 100) % 10), false);
}

void getAndPrintTemperature() {
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  if (temp < 0)
    temp = -1 * temp;
  
  printNumber2(temp);
}
