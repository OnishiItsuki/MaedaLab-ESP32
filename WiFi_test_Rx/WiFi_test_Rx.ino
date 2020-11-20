#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "ESP32_AP";
const char password[] = "damedame";
const int localPort = 10000;

const IPAddress RxIP(192, 168, 4, 13);
const IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  // setup ESP32 as Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(RxIP, RxIP, subnet);

  Serial.print("AP IP address: ");
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  Serial.println("Starting UDP");

  Serial.print("Local port: ");
  Serial.println(localPort);
}

void loop() {
  if (udp.parsePacket()) {
    char tmp = udp.read();
    Serial.println(tmp);
  }
}
