int resistance = 0;

void setup() {
    Serial.begin(9600);
    pinMode(14, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
}

void loop() {
    resistance = analogRead(14);
    if(resistance <= 30) {
        Serial.println("NO POWER");
        changeColor(255, 255, 255);
    }
    else if(resistance <= 1365) {
        Serial.println("MODE 1: BLUE");
        changeColor(255, 0, 0);
    }
    else if(resistance <= 2730){
        Serial.println("MODE 2: YELLOW");
        changeColor(0, 255, 0);
    }
    else {
        Serial.println("MODE 3: RED");
        changeColor(0, 0, 255);
    }
    delay(200);
}

void changeColor(int blue, int yellow, int red) {
    analogWrite(2 , blue);
    analogWrite(4 , yellow);
    analogWrite(3 , red);
}