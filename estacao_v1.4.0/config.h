/************************ General Configs *******************************/
#define SEALEVELPRESSURE_HPA (1025.0)
#define VERSION ("1.4.0")

int period = 10000;               //Tempo entre medidas (miliseconds)
//unsigned long delayTime = 60e6;
//unsigned long delayTimeuS = 600e6;

double temp = 0.0;
double pressure = 0.0;
double alti = 0.0;
double hum = 0.0;
double velocidade = 0.0;
/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "Adafruit IO Username"
#define IO_KEY       "Adafruit IO Key"

/******************************* WIFI **************************************/
#include "AdafruitIO_WiFi.h"

#define WIFI_SSID   "SSID"
#define WIFI_PASS   "SSID password"
int restartCounter = 0;
const int restartTimeout = 50;

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/**************************** ANENOMETER ************************************/
const byte pinAnenometerSensor = 13; //D7
const float pi = 3.14159265;     //pi
int radius = 50;              //raio - deveria ser em metros, mas como nao temos precisao, fazemos em mm e depois transformamos
unsigned int counter = 0;        //Contador para o sensor
unsigned int RPM = 0;            //Rotações por minuto
float windspeedms = 0;             //Velocidade do vento (m/s)
float windspeedkm = 0;             //Velocidade do vento (km/h)
