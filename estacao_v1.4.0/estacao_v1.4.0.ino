#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include "config.h"

/*
 * By: achermida@gmail.com
 * Version 1.0.0
 *  - Reading data from BME
 * Version 1.1.0
 *  - Introduced DeepSleep
 * Version 1.2.0
 *  - Connection to Adafruit
 * Version 1.3.0
 *  - TCRT5000 sensor para anemômetro
 * Version 1.3.1
 *  - Removido o TCRT5000
 *  - A3144 
 * Version 1.4.0
 *  - Removed DeepSleep
 *  - Added Modem Sleep
 */
//
const boolean useBME = true;
const boolean useWIFI = true;
const boolean useADAF = true;
const boolean useANEN = true;

Adafruit_BME280 bme;

AdafruitIO_Feed *temperatura = io.feed("temperatura");
AdafruitIO_Feed *humidade = io.feed("humidade");
AdafruitIO_Feed *velocidadevento = io.feed("velocidadevento");

void setup() {
 initData(useBME, useWIFI, useADAF, useANEN);
}

void loop() {
  Serial.println("Inicia Leitura...");
  Serial.println("");
  if(useANEN){
    velocidade = verificaVelocidade();
  }
  if(useBME){
    temp = bme.readTemperature();
    pressure = bme.readPressure();
    alti = bme.readAltitude(SEALEVELPRESSURE_HPA);
    hum = bme.readHumidity();
  }
  if(useADAF){
    io.run();
    temperatura->save(temp);
    humidade->save(hum);
    velocidadevento->save(velocidade);
  }
//  delay(2000);
  printValues(temp,pressure,alti,hum,velocidade);

counter = 0;
//  delay(period);
  modemSleepAndWake(period);
//  initDeepSleepBy(delayTimeuS);  
}
