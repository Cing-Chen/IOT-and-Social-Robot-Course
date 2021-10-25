#include <LWiFi.h>
 
const char* ssid = "TELDAP-2";
const char* password =  "TELDAP4F";
 
const uint16_t port = 12345;
const char * host = "10.50.2.19";
 
void setup()
{
 
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");

    String sendStr = "[{\"LightSensor\":\"" + String(analogRead(A0), OCT) + "\\"Group3333333333333\"}]";
    client.print(sendStr);
 
    Serial.println("Disconnecting...");
    client.stop();

    printWifiStatus();
    delay(10000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
