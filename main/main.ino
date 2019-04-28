#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>

// #include <EEPROM.h>

int pin_pump = D1;
int pin_btn = D7;
int pin_led = D8;
int pin_soil = A0;

void(* resetFunc) (void) = 0;

// bool shouldSaveConfig = false;
// void saveConfigCallback () {
//   Serial.println("Should save config");
//   shouldSaveConfig = true;
// }

void pumpOn(int length){
    digitalWrite(pin_pump, HIGH);
    delay(length);
    digitalWrite(pin_pump, LOW);
}

WiFiManager wifiManager;
char blynk_token[34] = "6c4178abbcec4ec0af60edc3c90b2784";
// WiFiManagerParameter custom_blynk_token("blynk_token", "Blynk Token", blynk_token, 34);

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

// WidgetLED led1(V5);

//Manual watering
BLYNK_WRITE(V5) {
    int pinValue = param.asInt();
    digitalWrite(pin_pump, pinValue);
    // if(pinValue){led1.on();}else{led1.off();}
}

//Send moisture readings
BLYNK_READ(V6) {
    Blynk.virtualWrite(V6, map(analogRead(pin_soil), 250, 1024, 0 ,100));
}

//Read time from application
BLYNK_WRITE(V7){
    int pinValue = param.asInt();
    Blynk.virtualWrite(V7, pinValue);
    Serial.println(pinValue);
}

//Read target humidity from application
BLYNK_WRITE(V8){
    int pinValue = param.asInt();
    Blynk.virtualWrite(V8, pinValue);
    Serial.println(pinValue);
}

//Read water amount from application
BLYNK_WRITE(V9){
    int pinValue = param.asInt();
    Blynk.virtualWrite(V9, pinValue);
    Serial.println(pinValue);
}