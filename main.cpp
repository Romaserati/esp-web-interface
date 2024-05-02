#include <Arduino.h>
#define LDR A0

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const int redLed = 15;
const int greenLed = 12;
const int blueLed = 13;

ESP8266WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", "<h1>Hello world from esp!</h1>");
}

void homePage() {
  String webpage =
  "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
</head>\
<body>\
<style>\
body {\
    background: #1e1e1f;\
}\
.form-switch {\
    display: inline-block;\
    cursor: pointer;\
}\
\
.form-switch:not(:last-child) {\
    margin-bottom: 15px;\
}\
\
.form-switch input {\
    display: none;\
}\
\
.form-switch i {\
    position: relative;\
    display: inline-block;\
    margin-right: 0.5rem;\
    width: 46px;\
    height: 26px;\
    background-color: #e6e6e6;\
    border-radius: 23px;\
    vertical-align: text-bottom;\
    transition: all 0.3s;\
}\
\
.form-switch i::before {\
    content: \"\";\
    position: absolute;\
    left: 0;\
    width: 42px;\
    height: 22px;\
    background-color: #fff;\
    border-radius: 11px;\
    transform: translate3d(2px, 2px, 0) scale3d(1, 1, 1);\
    transition: all 0.3;\
}\
\
.form-switch i::after {\
    content: \"\";\
    position: absolute;\
    left: 0;\
    width: 22px;\
    height: 22px;\
    background-color: #fff;\
    border-radius: 11px;\
    box-shadow: 0 2px 2px rgba(0, 0, 0, 0.24);\
    transform: translate3d(2px, 2px, 0);\
    transition: all 0.2s ease-in-out;\
}\
\
.form-switch:active i::after {\
    width: 28px;\
    transform: translate3d(2px, 2px, 0);\
}\
.form-switch:active input:checked + i::after {\
    transform: translate3d(16px, 2px, 0);\
}\
\
.form-switch input:checked + i {\
    background-color: #5bda4e;\
}\
\
.form-switch input:checked + i::before {\
    transform: translate3d(18px, 2px, 0) scale3d(0, 0, 0);\
}\
.form-switch input:checked + i::after {\
    transform: translate3d(22px, 2px, 0);\
}\
    </style>\
    <h1 style='color:white'>HOME PAGE</h1>\
    <span style='font-size:25px; color:white; margin-right:15px'><span style='color:red'>Красный</span> светодиод</span>\
    <label class=\"form-switch\">\
        <input type=\"checkbox\""; if (digitalRead(redLed)) webpage += "checked "; webpage += "id=\"red\">\
        <i></i>\
    </label> <br>\
    <span style='font-size:25px; color:white; margin-right:15px'><span style='color:green'>Зеленый</span> светодиод</span>\
    <label class=\"form-switch\">\
        <input type=\"checkbox\""; if (digitalRead(greenLed)) webpage += "checked "; webpage += "id=\"green\">\
        <i></i>\
    </label> <br>\
    <span style='font-size:25px; color:white; margin-right:15px'><span style='color:blue'>Синий</span> светодиод</span>\
    <label class=\"form-switch\">\
        <input type=\"checkbox\""; if (digitalRead(blueLed)) webpage += "checked "; webpage += "id=\"blue\">\
        <i></i>\
    </label>\
    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\
    <script>\
        $(\"#red\").on('change', function() {\
                  $.ajax({\
                    url: 'red_switch',\
                    type: 'GET',\
                    success: console.log(`Красный ${$('input[id=\"red\"]').is(\":checked\") ? \"вкл\" : \"выкл\"}`)\
                })\
        });\
        $(\"#green\").on('change', function() {\
                  $.ajax({\
                    url: 'green_switch',\
                    type: 'GET',\
                    success: console.log(`Зеленый ${$('input[id=\"green\"]').is(\":checked\") ? \"вкл\" : \"выкл\"}`)\
                })\
        });\
        $(\"#blue\").on('change', function() {\
                  $.ajax({\
                    url: 'blue_switch',\
                    type: 'GET',\
                    success: console.log(`Синий ${$('input[id=\"blue\"]').is(\":checked\") ? \"вкл\" : \"выкл\"}`)\
                })\
        });\
    </script>\
</body>\
</html>";

server.send(200, "text/html", webpage);
}

void redSwitch() {
  digitalWrite(redLed, !digitalRead(redLed));
  server.send(200, "text/html", "ok");
}

void greenSwitch() {
  digitalWrite(greenLed, !digitalRead(greenLed));
  server.send(200, "text/html", "ok");
}

void blueSwitch() {
  digitalWrite(blueLed, !digitalRead(blueLed));
  server.send(200, "text/html", "ok");
}

const char* ssid = "GoodLine-9056";
const char* pass = "2203631427";

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
  Serial.begin(115200);

  WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/home", homePage);
    server.on("/red_switch", redSwitch);
    server.on("/green_switch", greenSwitch);
    server.on("/blue_switch", blueSwitch);
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
