#include <WiFi.h>

const char* ssid = "bfi-maeda_11bgn";
const char* password = "bfi11111maeda";
int value = 0;
WiFiServer server(80);


void setup()
{
  Serial.begin(115200);
  Serial.println("start pgm");
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop()
{
  WiFiClient client = server.available();
  if (client){
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type; text/html");
            client.println();

            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
          
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) {
          Serial.println("client send H");
        }
        if (currentLine.endsWith("GET /L")) {
          Serial.println("client send L");
        }
        
      }
    }

    client.stop();
    Serial.println("Client Desconnected.");
  }
}
