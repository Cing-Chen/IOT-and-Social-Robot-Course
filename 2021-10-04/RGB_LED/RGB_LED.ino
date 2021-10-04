int counter = 0;
int status[3];

void setup() {
    Serial.begin(9600);
    pinMode(15, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
}

void loop() {
    counter = (counter + 1) % 3;
    switch (counter) {
    case 0:
        status[0] = 0;
        status[1] = 1;
        status[2] = 1;
        break;
    case 1:
        status[0] = 0;
        status[1] = 0;
        status[2] = 1;
        // status = {0, 0, 1};
        break;
    case 2:
        status[0] = 0;
        status[1] = 0;
        status[2] = 0;
        // status = {0, 0, 0};
    default:
        break;
    }
    changeColor(status);
    delay(1000);
}

void changeColor(int *status) {
    for(int i = 0; i < 3; i++) {
        if (status[i] == 0) {
            digitalWrite(i + 15, LOW);
        }
        else {
            digitalWrite(i + 15, HIGH);
        }
    }
}