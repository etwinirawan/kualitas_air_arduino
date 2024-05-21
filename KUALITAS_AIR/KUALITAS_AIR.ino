#include <OneWire.h>
#include <DallasTemperature.h>

#include <EEPROM.h>
#include "GravityTDS.h"
#define TdsSensorPin 35
GravityTDS gravityTds;

float temperature = 25, tdsValue = 0;
// GPIO where the DS18B20 is connected to
const int oneWireBus = 32;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
float suhuNow;
void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(3.3);       //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();            //initialization
  sensors.begin();
}

void loop() {
  suhu();
  // tds();
  delay(5000);
}

void suhu() {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  // float temperatureF = sensors.getTempFByIndex(0);
  suhuNow = temperatureC;
  Serial.print(suhuNow);
  Serial.println("ºC");
  // Serial.print(temperatureF);
  // Serial.println("ºF");
}
void tds() {
  //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
}
void ph(){
  
}