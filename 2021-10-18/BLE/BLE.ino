#include <LBLE.h>
#include <LBLEPeriphral.h>

int data;
LBLEService __periphralService("6f11903e-c3e9-4247-8921-60674c1a1b82");
LBLECharacteristicInt __6f11903e_c3e9_4247_8921_60674c1a1b82("6f11903e-c3e9-4247-8921-60674c1a1b82", (LBLE_READ | LBLE_WRITE));

void setup() {
    LBLE.begin();
    while(!LBLE.ready()) {
        delay(100);
    }

    __periphralService.addAttribute(__6f11903e_c3e9_4247_8921_60674c1a1b82);

    LBLEPeripheral.addService(__periphralService);
    LBLEPeripheral.begin();
    LBLEAdvertisementData __advertisement;
    __advertisement.configAsConnectableDevice("LinkIt 7697");
    LBLEPeripheral.advertise(__advertisement);
    Serial.begin(9600);
    Serial.println("Build Bluetooth Device Successfully!");
}

void loop() {
    if(__6f11903e_c3e9_4247_8921_60674c1a1b82.isWritten()) {
        data = __6f11903e_c3e9_4247_8921_60674c1a1b82.getValue();
        Serial.println(data);
    }
    __6f11903e_c3e9_4247_8921_60674c1a1b82.setValue(12345);
    delay(1000);
}