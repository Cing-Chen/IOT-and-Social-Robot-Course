int led = 0;
int fade = 5;

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
}

void loop() {
    analogWrite(2, led);
    led += fade;

    if(led <= 0) {
        fade = 5;
    }
    else if(led >= 255) {
        fade = -5;
    }

    Serial.print("Current led value = ");
    Serial.println(led);
    delay(30);
}