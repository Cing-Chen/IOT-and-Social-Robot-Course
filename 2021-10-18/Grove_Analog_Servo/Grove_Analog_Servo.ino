#include <Servo.h>

int val = 0;

Servo __myservo10;

void setup() {
    __myservo10.attach(10);
}

void loop() {
    __myservo10.write(0);
    delay(1000);
    __myservo10.write(180);
    delay(1000);
}