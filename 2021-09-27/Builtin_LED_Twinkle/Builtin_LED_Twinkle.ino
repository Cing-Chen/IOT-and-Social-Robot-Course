void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED is lighting");
    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED is not lighting");
    delay(1000);
}