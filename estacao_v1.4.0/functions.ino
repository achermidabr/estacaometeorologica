void ICACHE_RAM_ATTR ISRoutine ();

void ISRoutine () {
  ++counter;
  Serial.println(counter);
}

double verificaVelocidade(){
  RPMcalc();
  WindSpeedMS();
  WindSpeedKM();
  Serial.print(counter);
  Serial.print(" :: ");
  Serial.print(RPM);
  Serial.print(" :: ");
  Serial.print(windspeedms);
  Serial.print(" :: ");
  Serial.print(windspeedkm);
  Serial.println();
  counter = 0;
  return windspeedkm;
}

void RPMcalc() {
  RPM = ((counter) * 60) / (period / 1000); // Calculate revolutions per minute (RPM)
}

/*
 * Speed formula in km/h based on m/s
 * 
 * v = vms * 3.6;
 * 
 * vms -> speed in m/s
 */
void WindSpeedKM() {
  windspeedkm = windspeedms * 3.6; //Calculate the wind speed in km/h
}

/*
 * Speed formula in m/s based on the RPM
 * 
 * v=(x ∗ 2 * π * r) / 60 
 * 
 * v -> speed in m/s
 * x -> speed in RPM
 * r -> radious in meters
 */
double WindSpeedMS() {
  windspeedms = ((2 * pi * RPM * radius * frictionFactor) / 60) / 1000; //Dividimos por 1000 para deixar em metros ja que o raio estava em mm
} //end WindSpeed

void initDeepSleepBy(unsigned long d){
  Serial.print("Going to sleep for ");
  Serial.print((d / 1000000) / 60);
  Serial.println(" minuts");
  ESP.deepSleep(d);
}

void modemSleepAndWake(unsigned long d){
  Serial.println("Going to modem sleep...");
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
  delay(d);
  WiFi.forceSleepWake();
  Serial.println("Back from modem sleep");
}

void printValues(double temp, double pressure, double alti, double hum, double wSpeed){
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" *C");

  Serial.print("Pressão: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Altitude Aprox.: ");
  Serial.print(alti);
  Serial.println(" m");

  Serial.print("Humidade: ");
  Serial.print(hum);
  Serial.println(" %");

  Serial.print("Velocidade do vento: ");
  Serial.print(windspeedkm);
  Serial.println(" km/h");


  Serial.print(counter);
  Serial.print(" :: ");
  Serial.print(RPM);
  Serial.print(" :: ");
  Serial.print(windspeedms);
  Serial.print(" :: ");
  Serial.print(windspeedkm);
  Serial.println();


  Serial.println();
}
