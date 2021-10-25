#include <LWiFi.h>
#include "MCS.h"
#include "DHT.h"

int t;
int h;

char _lwifi_ssid[] = "TELDAP-2";
char _lwifi_pass[] = "TELDAP4F";

MCSLiteDevice mcs("HyAxWj7IF", "35b4a54989701369158c09bbea5a916ea8887b38b8cd84a089af143efa4bc233", "140.115.158.250", 3000);
MCSDisplayInteger temp("temp");
MCSDisplayInteger humid("humid");

DHT __dht2(2, DHT22);

void setup()
{
  Serial.begin(9600);

  mcs.addChannel(temp);
  mcs.addChannel(humid);
  Serial.println("Wi-Fi 開始連線");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) { delay(1000); }
  Serial.println("Wi-Fi 連線成功");
  while(!mcs.connected()) { mcs.connect(); }
  Serial.println("MCS 連線成功");
  Serial.begin(9600);
  __dht2.begin();
}

void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) { Serial.println("MCS 已重新連線"); }
  }
  mcs.process(100);

  t = __dht2.readTemperature();
  h = __dht2.readHumidity();
  temp.set(t);
  humid.set(h);

  Serial.print("攝氏溫度 : ");
  Serial.println(t);
  Serial.print("相對溼度 :");
  Serial.println(h);

  delay(1000);
}
