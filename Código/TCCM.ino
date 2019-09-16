/* Código para cámara de maduración */

#include <DHT.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

/*Pines Físicos*/
#define Aceptar 4
#define Abajo 5
#define Arriba 6
#define Cancelar 7
#define pinDHT 17
#define releTemp 15
#define releHume 16

/*Banderas*/
bool E_Cancelar = false;
bool E_Aceptar = false;
bool E_Arriba = false;
bool E_Abajo = false;
bool desborde = false;
bool E_Sistema;

byte iArriba = 0;
byte iAbajo = 0;
byte iAceptar = 0;
byte iCancelar = 0;
byte iForm = 0;
byte iMenu = 0;
byte iValor = 0;
byte inactivo = 0;

/*EEPROM*/
int eeadress1 = 0;
int eeadress2 = eeadress1 + sizeof(float);
int eeadress3 = eeadress2 + sizeof(float);

unsigned long lastTime;
int interval = 3000;

/*Configuraciones de fases*/
int Fases;
float Temp1,Temp2,Temp3;
float Hume1,Hume2,Hume3;


DateTime Date1, Date2, Date3;
String String_D1, String_D2, String_D3;


/*Sensor DHT*/
float TempD;
float HumeD;
float hysteresis = .5;

DHT dht(pinDHT, DHT11); //Sensor de humedad
LiquidCrystal_I2C lcd(0x27,20,4); //Pantalla LCD
RTC_DS3231 rtc;
DateTime FH;

int year, mes, dia, hora, minuto;

void setup() {
  pinMode(Cancelar, INPUT_PULLUP);
  pinMode(Aceptar, INPUT_PULLUP);
  pinMode(Arriba, INPUT_PULLUP);
  pinMode(Abajo, INPUT_PULLUP);
  pinMode(pinDHT, INPUT);
  pinMode(releTemp, OUTPUT);
  pinMode(releHume, OUTPUT);
  dht.begin();
  //Serial.begin(9600);

  rtc.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  /*Obtener datos EEPROM*/
  TempD = EEPROM.read(eeadress1);
  HumeD = EEPROM.read(eeadress2);
  E_Sistema = EEPROM.read(eeadress3);

  if ( EEPROM.read(eeadress3) == true) {
    iForm = 5; //Pantalla de control
  }
}

void loop() {

  Menu(); 

}
