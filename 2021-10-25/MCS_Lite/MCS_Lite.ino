#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "TELDAP-2";
char _lwifi_pass[] = "TELDAP4F";

MCSLiteDevice mcs("H1Pwu9m8Y", "4bb9194c252d6f4af894c127ab568270779546d52ac6e0702ae6d630689463b0", "140.115.158.250", 3000);
MCSControllerOnOff MySwitch("MySwitch");

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(MySwitch);
  Serial.println("Wi-Fi 開始連線");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi 連線成功");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS 連線成功");
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
  }
  mcs.process(100);

  if (MySwitch.updated()) {
    Serial.print("控制通道更新 :");
    Serial.println(MySwitch.value());

    if (MySwitch.value()) {
      digitalWrite(LED_BUILTIN, HIGH);

    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(1000);
}
