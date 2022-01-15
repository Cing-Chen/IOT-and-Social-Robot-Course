#include <LWiFi.h>
#include <Arduino_JSON.h>
#include <DHT.h>

const char* ssid = "TELDAP";
const char* password = "TELDAP4F";

// const char* ssid = "412 - JC IS NOT LOLICON";
// const char* password = "jcnot1011con";

const char * host = "192.168.0.230"; // TODO: server ip
const uint16_t port = 7100; // TODO: server port

WiFiClient client;

DHT __dht2(2,DHT22);

void setup() {
  Serial.begin(9600);

  __dht2.begin();

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println(__dht2.readTemperature());
  Serial.println(__dht2.readHumidity());
  Serial.println(analogRead(A0));

  if(client.connected()) {
    JSONVar JSONlight;
    JSONlight["type"] = "light";
    JSONlight["content"] = analogRead(A0);

    String JSONlightString = JSON.stringify(JSONlight) + "\n";
    client.print(JSONlightString);

    JSONVar JSONtemp;
    JSONtemp["type"] = "temp";
    JSONtemp["content"] = __dht2.readTemperature();

    String JSONtempString = JSON.stringify(JSONtemp) + "\n";
    client.print(JSONtempString);


    JSONVar JSONhumi;
    JSONhumi["type"] = "humi";
    JSONhumi["content"] = __dht2.readHumidity();

    String JSONhumiString = JSON.stringify(JSONhumi) + "\n";
    client.print(JSONhumiString);

    delay(1000);
  }
  else {
    if(!client.connect(host, port)) {
      Serial.println("Connection to host failed");
      delay(1000);
    }
    else {
      Serial.println("Connected to server successful!");
    }
  }
}