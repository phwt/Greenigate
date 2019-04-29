//Manual watering
BLYNK_WRITE(V5) {
    int pinValue = param.asInt();
    digitalWrite(pin_pump, pinValue);
    // if(pinValue){led1.on();}else{led1.off();}
}

//Send moisture readings
BLYNK_READ(V6) {
    humidnow = map(analogRead(pin_soil), 1024, 250, 0 ,100);
    Blynk.virtualWrite(V6, humidnow);
}

//Read time from application
BLYNK_WRITE(V7){
    int pinValue = param.asInt();

    timeset = pinValue;
    
    // String hm = "";
    int hr = floor(pinValue / 3600);
    int mn = floor(pinValue / 60 % 60);
    String hm = String(hr) + ":" + String(mn);

    Blynk.virtualWrite(V7, hm);

    Serial.println(hr*100 + mn);
}

//Read target humidity from application
BLYNK_WRITE(V8){
    int pinValue = param.asInt();
    Blynk.virtualWrite(V8, pinValue);

    humidset = pinValue;

    Serial.println(pinValue);
}

//Read water amount from application
BLYNK_WRITE(V9){
    int pinValue = param.asInt();
    waterset = pinValue;
    Blynk.virtualWrite(V9, pinValue);
    Serial.println(pinValue);
}