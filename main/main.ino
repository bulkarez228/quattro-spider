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
}

void loop() {
  //server.tick();
  //dns.processNextRequest();
  front_left_high.write(95);
  front_left_low.write(150);
  front_right_high.write(95);
  front_right_low.write(47);
  rear_left_high.write(100);
  rear_left_low.write(50);
  rear_right_high.write(105);
  rear_right_low.write(130);
}