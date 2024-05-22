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
//PH
const int ph_Pin = 25;
float Po = 0;
float PH_step;
int nilai_analog_PH;
double TeganganPh;

//untuk kalibrasi
float PH4 = 3.226;
float PH7 = 2.691;
//END PH

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  pinMode(ph_Pin, INPUT);
  // Start the DS18B20 sensor
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(3.3);       //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(4096);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();            //initialization
  sensors.begin();
}

void loop() {
  suhu();
  tds();
  ph();
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
  gravityTds.update();                     //sample and calculate
  tdsValue = gravityTds.getTdsValue();     // then get the value
  Serial.print(tdsValue, 0);
  Serial.println("ppm");
}
void ph() {
  nilai_analog_PH = analogRead(ph_Pin);
  Serial.print("Nilai ADC Ph: ");
  Serial.println(nilai_analog_PH);
  TeganganPh = 3.3 / 4095.0 * nilai_analog_PH;
  Serial.print("TeganganPh: ");
  Serial.println(TeganganPh, 3);

  PH_step = (PH4 - PH7) / 3;
  Po = 7.00 + ((PH7 - TeganganPh) / PH_step);  //Po = 7.00 + ((teganganPh7 - TeganganPh) / PhStep);
  Serial.print("Nilai PH cairan: ");
  Serial.println(Po, 2);
}