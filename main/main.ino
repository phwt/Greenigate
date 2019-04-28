#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>

char auth[] = "6c4178abbcec4ec0af60edc3c90b2784";


int pin_pump = D1;
int pin_btn = D7;
int pin_led = D8;
int pin_soil = A0;

void(* resetFunc) (void) = 0;

void pumpOn(int length){
    digitalWrite(pin_pump, HIGH);
    delay(length);
    digitalWrite(pin_pump, LOW);
}

WiFiManager wifiManager;

void setup() {
    Serial.begin(115200);

    pinMode(pin_pump, OUTPUT);
    pinMode(pin_led, OUTPUT);
    pinMode(pin_btn, INPUT_PULLUP);

    digitalWrite(pin_led, HIGH);

    // WiFiManagerParameter custom_text("<p>This is just a text paragraph</p>");
    // wifiManager.addParameter(&custom_text);

    wifiManager.autoConnect("Greenigate-01", "P@ssw0rd");

    digitalWrite(pin_led, LOW);
    // Serial.println();
    Blynk.begin(auth, "xxxx", "xxxx", "blynk.iot-cm.com", 8080);
}

BLYNK_WRITE(V5){
    int pinValue = param.asInt();
    if(pinValue){
        pumpOn(2000);
    }
    // Serial.println(pinValue);
}

void loop() {

    Blynk.run();

    if(!digitalRead(pin_btn)){
        wifiManager.resetSettings();
        Serial.println("pushed");
        resetFunc();
    }

    // pumpOn(2000);

    // Serial.println("new");
    // digitalWrite(pin_pump, HIGH);
    // delay(2000);
    // digitalWrite(pin_pump, LOW);

    delay(50);
}
