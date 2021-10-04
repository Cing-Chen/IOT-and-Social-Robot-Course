#include <Grove_LED_Bar.h>

Grove_LED_Bar LED_Bar(3, 2, 0);

void setup() {
    Serial.begin(9600);
    LED_Bar.begin();
}

void loop() {
    for(int i = 0; i < 11; i++) {
        LED_Bar.setLevel(i);
        delay(1000);
    }
    delay(1000);
}