#include <LWiFi.h>
#include <WiFiClient.h>
// #include <LWebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "LinkItAP_Group3";
const char *password = "12345678";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);      // set the LED pin mode
    pinMode(11, OUTPUT);  //R
    pinMode(9, OUTPUT);   //G
    pinMode(7, OUTPUT);   //B
    Serial.println();
    Serial.print("Configuring access point...");

    /* You can remove the password parameter if you want the AP to be open. */
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("AP ready.");
    Serial.print("Connect to AP ");
    Serial.print(ssid);
    Serial.print(" and visit http://");
    Serial.println(myIP);

    Serial.print("AP MAC=");
    Serial.println(WiFi.softAPmacAddress());

    server.begin();
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/R\">here</a> to light red<br>");
            client.print("Click <a href=\"/G\">here</a> to light green<br>");
            client.print("Click <a href=\"/B\">here</a> to light blue<br>");
            client.print("Click <a href=\"/W\">here</a> to light white<br>");
            client.print("Click <a href=\"/o\">here</a> to light off<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check client request
        if (currentLine.startsWith("GET /R")) {  // GET /R to light red
          led(0,1,1);     
        }
        if (currentLine.startsWith("GET /G")) {  // GET /G to light green
          led(1,0,1); 
        }
        if (currentLine.startsWith("GET /B")) {  // GET /B to light blue
          led(1,1,0);
        }
        if (currentLine.startsWith("GET /W")) {  // GET /W to light white
          led(0,0,0);
        }
        if (currentLine.startsWith("GET /o")) {  // GET /o to light off
          led(1,1,1);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void led(int R, int G, int B) {
  digitalWrite(11, R);
  digitalWrite(9, G);
  digitalWrite(7, B);
}
