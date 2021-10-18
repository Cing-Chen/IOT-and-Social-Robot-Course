int val = 0, controlPin = 10, buttonPin = 6;

void pin_change() {
    val = !val;
}

void setup() {
    Serial.begin(9600);
    pinMode(controlPin, OUTPUT);
    attachInterrupt(buttonPin, pin_change, RISING);
}

void loop() {
    if(val) {
        digitalWrite(controlPin, HIGH);
        Serial.println("HIGH");
    }
    else {
        digitalWrite(controlPin, LOW);
        Serial.println("LOW");
    }
    delay(500);
}