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
  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(RxIP, RxIP, subnet);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: " + myIP.toString());
  Serial.println("Starting UDP");
  Serial.print("Local port: ");
  Serial.println(localPort);
}

void loop() {
  if (udp.parsePacket()) {
    char tmp = udp.read();
    Serial.println(tmp);
  } else {
//    Serial.println(udp.parsePacket());
//    Serial.println("else");
  }
}
