#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;

#define USE_SERIAL Serial
#define OUTPUT_LED 0
#define LED_BLINK_MS 250
#define HTTP_POLLING_SEC 60


#define WIFI_APNAME your_ap_name
#define WIFI_PASSWD 123456
#define URL_RET_0   https://raw.githubusercontent.com/S-shangli/garbagetrashcan/main/return_0/README.md
#define URL_RET_1   https://raw.githubusercontent.com/S-shangli/garbagetrashcan/main/return_1/README.md
#define TARGET_URL  URL_RET_1
#ifndef WIFI_APNAME
  #include "wifi_passwd.h" // private file :)
#endif

unsigned char NOTIFICATION_STATUS=0;

void setup() {
  USE_SERIAL.begin(115200);
  USE_SERIAL.print("\n\n");
  USE_SERIAL.print("[serial] begin ... done\n");

  pinMode(OUTPUT_LED , OUTPUT);

  USE_SERIAL.print("[wifi] set to STA ... ");
  WiFi.mode(WIFI_STA);
  USE_SERIAL.print("done\n");

  USE_SERIAL.print("[wifi] connect to AP ... ");
  WiFiMulti.addAP("WIFI_APNAME", "WIFI_PASSWD");
  USE_SERIAL.print("waiting ... ");
  LEDOUT_1();
  while(WiFiMulti.run() != WL_CONNECTED){
    delay(1);
  }
  USE_SERIAL.print("done\n");
  LEDOUT_0();
}

void LEDOUT_1(){
  digitalWrite(OUTPUT_LED, HIGH);
}

void LEDOUT_0(){
  digitalWrite(OUTPUT_LED, LOW);
}

void LEDOUTPUT_HANDLER(){
  if(NOTIFICATION_STATUS != 0 ){
    unsigned long LED_BLINK_COUNTER = millis() % (LED_BLINK_MS * 2);
    if( LED_BLINK_COUNTER > LED_BLINK_MS ){ LEDOUT_1(); }
    else                                  { LEDOUT_0(); }
  }else{
    LEDOUT_0();
  }
}

unsigned char POLLING_FLG=1;
void STATUS_UPDATE_HANDLER(){
  unsigned long HTTP_POLLING_COUNTER = millis() / 1000;
  
  if( 0 == ( HTTP_POLLING_COUNTER % HTTP_POLLING_SEC ) ){
    if( 1 == POLLING_FLG ){
      NOTIFICATION_STATUS=GET_STATUS();
      POLLING_FLG=0;
    }
  }else{
    POLLING_FLG = 1;
  }
}

int GET_STATUS(){
  HTTPClient http;
  String payload="0";
    
  USE_SERIAL.print("[HTTP] begin...\n");
  http.begin("TARGET_URL"); //HTTP

  USE_SERIAL.print("[HTTP] GET ... ");
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    USE_SERIAL.printf("code: %d\n", httpCode);

    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      payload = http.getString();
      USE_SERIAL.print("[HTTP] payload: ");
      USE_SERIAL.print(payload.toInt());
      USE_SERIAL.print("\n");
    }else{
      payload="0";
    }
  } else {
      USE_SERIAL.printf("failed, error: %s\n", http.errorToString(httpCode).c_str());
      payload="0";
  }

  USE_SERIAL.print("[HTTP] close ... ");
  http.end();
  USE_SERIAL.print("done\n");
  return(payload.toInt());
}


void loop() {

  STATUS_UPDATE_HANDLER();

  LEDOUTPUT_HANDLER();

  delay(10);
}
