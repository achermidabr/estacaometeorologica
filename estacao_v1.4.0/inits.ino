void initData(boolean bme, boolean wifi, boolean adafruit, boolean anenometer){
  Serial.begin(115200);
  Serial.setTimeout(2000);
  Serial.println("Acordando ...");
  while(!Serial) {delay(500);}

  if(bme){ initBME();}
  if(wifi){ initWifi();}
  if(adafruit){ initAdafruit();}
  if(anenometer){ initAnenometer();}
  
  Serial.println("--------- Iniciando Medições ----------");
  Serial.println("");
}

void initBME(){
  Serial.println(F("Iniciando estação metereológica..."));
  if(!bme.begin(0x76)){
    Serial.println("Nada do BME");
    while(1);
  }
  Serial.println("Estação iniciada");
  Serial.println();
}

void initWifi(){
  Serial.print(F("Iniciando WiFi "));
  restartCounter = 0;
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print("."); 
      if(restartCounter >= restartTimeout){
        Serial.print("Could not connect to Wifi. Restarting ESP."); 
        ESP.restart();
      }
      restartCounter+=1;      
  }
  Serial.println("");
  Serial.print("Wifi conectado na rede ");
  Serial.print( WIFI_SSID );
  Serial.print(", com o IP ");
  Serial.println(WiFi.localIP() );
  Serial.println("");
}

void initAdafruit(){
  Serial.print(F("Iniciando Adafruit IO "));
  restartCounter = 0;
  io.connect();
  while( io.status() < AIO_CONNECTED ){
      delay(500);
      Serial.print(".");  
      if(restartCounter >= restartTimeout){
        Serial.print("Could not connect to Adafruit IO. Restarting ESP."); 
        ESP.restart();
      }
      restartCounter+=1;       
  }
  Serial.println("");
  Serial.print("Adafruit IO conectado ");
  Serial.print( io.statusText());
  Serial.println("");
}

void initAnenometer(){
  pinMode(pinAnenometerSensor,INPUT);
  attachInterrupt(digitalPinToInterrupt(pinAnenometerSensor),ISRoutine,FALLING);
  Serial.print("Anemômetro inicializado");
}
