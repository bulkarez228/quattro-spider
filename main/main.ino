#include <ESP32Servo.h>
#include <Arduino.h>
//#include <WiFi.h>
//#include <GyverHTTP.h>
//#include <DNSServer.h>
//#include "webjoy.h"

//ghttp::Server<WiFiServer, WiFiClient> server(80);
//DNSServer dns;



Servo front_left_high;
Servo front_left_low;
Servo front_right_high;
Servo front_right_low;
Servo rear_left_high;
Servo rear_left_low;
Servo rear_right_high;
Servo rear_right_low;

#define FRONT_LEFT_HIGH_ZERO 95
#define FRONT_LEFT_LOW_ZERO 150
#define FRONT_RIGHT_HIGH_ZERO 95
#define FRONT_RIGHT_LOW_ZERO 47
#define REAR_LEFT_HIGH_ZERO 100
#define REAR_LEFT_LOW_ZERO 50
#define REAR_RIGHT_HIGH_ZERO 105
#define REAR_RIGHT_LOW_ZERO 130

#define WALK_DEGREE 35
#define LEG_UP_DEGREE 45

void home() {
  front_left_high.write(FRONT_LEFT_HIGH_ZERO);
  front_left_low.write(FRONT_LEFT_LOW_ZERO);
  front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
  front_right_low.write(FRONT_RIGHT_LOW_ZERO);
  rear_left_high.write(REAR_LEFT_HIGH_ZERO);
  rear_left_low.write(REAR_LEFT_LOW_ZERO);
  rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
  rear_right_low.write(REAR_RIGHT_LOW_ZERO);
}

void walk(int i) {
  switch (i) {
    case 0:
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO);

      front_left_low.write(FRONT_LEFT_LOW_ZERO - LEG_UP_DEGREE);
      front_left_high.write(FRONT_LEFT_HIGH_ZERO - WALK_DEGREE);

      rear_right_low.write(REAR_RIGHT_LOW_ZERO - WALK_DEGREE);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO + WALK_DEGREE);
      break;

    case 1:
      rear_right_low.write(REAR_RIGHT_LOW_ZERO);
      front_left_low.write(FRONT_LEFT_LOW_ZERO);
      break;

    case 2:
      front_right_low.write(FRONT_RIGHT_LOW_ZERO + WALK_DEGREE);
      front_right_high.write(FRONT_RIGHT_HIGH_ZERO + WALK_DEGREE);
    
      rear_left_low.write(REAR_LEFT_LOW_ZERO + WALK_DEGREE);
      rear_left_high.write(REAR_LEFT_HIGH_ZERO - WALK_DEGREE);

      front_left_high.write(FRONT_LEFT_HIGH_ZERO);
      rear_right_high.write(REAR_RIGHT_HIGH_ZERO);
      break;

    case 3:
      rear_left_low.write(REAR_LEFT_LOW_ZERO);
      front_right_low.write(FRONT_RIGHT_LOW_ZERO);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  /*WiFi.mode(WIFI_AP);
  WiFi.softAP("WebJoy");

  server.begin();
  dns.start(53, "*", WiFi.softAPIP());
    */
  front_left_high.attach(32);
  front_left_low.attach(33);
  front_right_high.attach(25);
  front_right_low.attach(26);
  rear_left_high.attach(27);
  rear_left_low.attach(14);
  rear_right_high.attach(12);
  rear_right_low.attach(13);
  /*
  server.onRequest([](ghttp::ServerBase::Request req) {
    switch (req.path().hash()) {
      case SH("/script.js"):
        server.sendFile_P(webjoy_script_gz, sizeof(webjoy_script_gz), "text/javascript", true, true);
        break;

      case su::SH("/style.css"):
        server.sendFile_P(webjoy_style_gz, sizeof(webjoy_style_gz), "text/css", true, true);
        break;

      case SH("/xy"):
        {
          int x = req.param("x");
          int y = req.param("y");
          front_left_high.write(0);
          front_left_low.write(0);
          front_right_high.write(0);
          front_right_low.write(0);
          rear_left_high.write(0);
          rear_left_low.write(0);
          rear_right_high.write(0);
          rear_right_low.write(0);
        }
        break;

      default:
        server.sendFile_P(webjoy_index_gz, sizeof(webjoy_index_gz), "text/html", false, true);
        break;
    }
  });
  */
  home();
  delay(1000);
}
int i = 0;
void loop() {
  //server.tick();
  //dns.processNextRequest();
  static uint32_t tmr;
  if (millis() - tmr >= 300) {
    tmr = millis();
    i++;
    if (i > 3) i = 0;
  }
  //walk(i);
}