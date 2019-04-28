#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>

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
char blynk_token[34] = "YOUR_TOKEN_HERE";
WiFiManagerParameter custom_blynk_token("blynk_token", "Blynk Token", blynk_token, 34);

void setup() {
    Serial.begin(115200);

    pinMode(pin_pump, OUTPUT);
    pinMode(pin_led, OUTPUT);
    pinMode(pin_btn, INPUT_PULLUP);
    pinMode(pin_soil, INPUT);

    digitalWrite(pin_led, HIGH);

    wifiManager.addParameter(&custom_blynk_token);
    wifiManager.autoConnect("Greenigate-01", "P@ssw0rd");

    digitalWrite(pin_led, LOW);

    strcpy(blynk_token, custom_blynk_token.getValue());
    Blynk.begin(blynk_token, WiFi.SSID().c_str(), WiFi.psk().c_str(), "blynk.iot-cm.com", 8080);
}

void loop() {

    Blynk.run();

    //WiFi reset button
    if(!digitalRead(pin_btn)){
        wifiManager.resetSettings();
        Serial.println("pushed");
        // resetFunc();
        ESP.restart();
    }

    delay(50);
}

//Manual watering
BLYNK_WRITE(V5) {
    int pinValue = param.asInt();
    digitalWrite(pin_pump, pinValue);
}

//Send moisture readings
BLYNK_READ(V6) {
    Blynk.virtualWrite(V6, map(analogRead(pin_soil), 250, 1024, 0 ,100));
}