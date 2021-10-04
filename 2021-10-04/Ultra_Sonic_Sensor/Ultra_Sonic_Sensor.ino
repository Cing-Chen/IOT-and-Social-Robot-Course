#include <Ultrasonic.h>

int range = 0;
Ultrasonic ultra_sonic(2);

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    range = ultra_sonic.MeasureInCentimeters();
    Serial.print("The range value = ");
    Serial.println(range);

    if(range < 5) {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
        digitalWrite(LED_BUILTIN, LOW);
    }

    delay(100);
}