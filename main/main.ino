#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

// #include <EEPROM.h>

int pin_pump = D1;
int pin_btn = D7;
int pin_led = D8;
int pin_soil = A0;

int timeset = 0;
int timenow = 1;
int humidset = 0;
int humidnow = 1;
int waterset;

bool humidnotify = true;

BlynkTimer timer;
WidgetRTC rtc;

void(* resetFunc) (void) = 0;

// bool shouldSaveConfig = false;
// void saveConfigCallback () {
//   Serial.println("Should save config");
//   shouldSaveConfig = true;
// }

void clockDisplay(){
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details
    timenow = hour() * 3600 + minute() * 60;
//   String currentTime = String(hour()) + ":" + minute() + ":" + second();
//   Serial.print("Current time: ");
//   Serial.println(currentTime);
}

void pumpOn(int length){
    digitalWrite(pin_pump, HIGH);
    delay(length);
    digitalWrite(pin_pump, LOW);
}

WiFiManager wifiManager;
char blynk_token[34] = "6c4178abbcec4ec0af60edc3c90b2784";
// WiFiManagerParameter custom_blynk_token("blynk_token", "Blynk Token", blynk_token, 34);

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
  Blynk.syncAll();
}

BLYNK_APP_CONNECTED() {
  Blynk.syncAll();
}

void setup() {
    Serial.begin(115200);

    pinMode(pin_pump, OUTPUT);
    pinMode(pin_led, OUTPUT);
    pinMode(pin_btn, INPUT_PULLUP);
    pinMode(pin_soil, INPUT);

    digitalWrite(pin_led, HIGH);

    // wifiManager.setSaveConfigCallback(saveConfigCallback);
    // wifiManager.addParameter(&custom_blynk_token);s
    wifiManager.autoConnect("Greenigate-01", "P@ssw0rd");

    digitalWrite(pin_led, LOW);

    // if(shouldSaveConfig){
    //     int eeAddress = 0;
    //     strcpy(blynk_token, custom_blynk_token.getValue());
    //     // EEPROM.put(eeAddress, blynk_token);
    // }
    
    // strcpy(blynk_token, EEPROM.get(0, char));
    Serial.println(blynk_token);

    Blynk.begin(blynk_token, WiFi.SSID().c_str(), WiFi.psk().c_str(), "blynk.iot-cm.com", 8080);

    setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)
    // Display digital clock every 10 seconds
    timer.setInterval(10000L, clockDisplay);
}

void loop() {

    Blynk.run();
    timer.run();

    //WiFi reset button
    if(!digitalRead(pin_btn)){
        wifiManager.resetSettings();
        Serial.println("pushed");
        // resetFunc();
        ESP.restart();
    }

    Serial.print(timeset);
    Serial.print(" ");
    Serial.println(timenow);

    if(timeset == timenow){
        if(humidnow > 80){
            Blynk.notify("The plant was not watered as the humidity is too high.");
        }else{
            Blynk.notify("Watering Plant...");
            pumpOn(waterset * 100);
        }
        delay(60000);
    }

    if(humidnow < humidset && humidnotify){
        Blynk.notify("Soil humidity is low considered manual watering.");
        humidnotify = false;
    }else if(humidnow >= humidset){
        humidnotify = true;
    }

    delay(50);
}