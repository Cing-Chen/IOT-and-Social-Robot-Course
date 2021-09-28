void setup() {
    pinMode(2, OUTPUT);
    pinMode(5, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(2, HIGH);
    Serial.println("LED1 light on!");
    delay(500);

    digitalWrite(2, LOW);
    Serial.println("LED1 light off!");
    delay(500);

    digitalWrite(5, HIGH);
    Serial.println("LED2 light on!");
    delay(500);

    digitalWrite(5, LOW);
    Serial.println("LED2 light off!");
    delay(500);
}