void setup() {
    Serial.begin(9600);
    pinMode(14, INPUT);
}

void loop() {
    Serial.println(analogRead(14));
    delay(1000);
}