// For RFID
#include <SPI.h>
#include <MFRC522.h

// For OLED
#include <Wire.h>
#include <SeeedOLED.h>

// For Servo Motor
#include <Servo.h>

// Global variables
MFRC522 rfid(10, 9);
Servo __myservo10;
String read_id;
int locker_status;

// read uid function
String mfrc522_readID() {
    String ret;
    
    if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        MFRC522::PICC_Type PICC_Type = rfid.PICC_GetType(rfid.uid.sak);

        for(byte i = 0; i < rfid.uid.size; i++) {
            ret += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
            ret += String(rfid.uid.uidByte[i], HEX);
        }
    }
    
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    return ret;
}

// print text on oled function
void show_text_on_OLED(char* message) {
    Serial.println(message);
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString(message);
}

// change degree of servo motor funtion
void lock() {
    __myservo10.write(120);
}

// change degree of servo motor funtion
void unlock() {
    __myservo10.write(30);
}

void setup() {
    Serial.begin(9600);

    // RFID initialize
    SPI.begin();
    rfid.PCD_Init();

    // OLED initialize
    Wire.begin();
    SeeedOled.init();
    SeeedOled.deactivateScroll();
    SeeedOled.setPageMode();
    SeeedOled.clearDisplay();

    // servo motor initialize
    __myservo10.attach(2);
    locker_status = 0;
    lock();
}

void loop() {
    show_text_on_OLED("Put card here.");

    read_id = mfrc522_readID();

    if(read_id == "962f1ef9") {
        if(locker_status == 0) {
            show_text_on_OLED("Welcome!");
            locker_status = 1;
            unlock();
        }
        else {
            show_text_on_OLED("Goodbye!");
            locker_status = 0;
            lock();
        }

        read_id = "" ;
    }

    delay(1000);
}