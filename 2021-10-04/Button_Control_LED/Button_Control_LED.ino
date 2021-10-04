void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if(digitalRead(2) == HIGH) {
        Serial.println("Button is pushed");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
        Serial.println("Button is not pushed");
        digitalWrite(LED_BUILTIN, LOW);
    }
    delay(100);
}