#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "ESP32_AP";
const char password[] = "damedame";

static WiFiUDP udp;
static const char *RxIP = "192.168.4.13";
static const int RxPort = 10000;

static const int localPort = 5000;


void setup() {
  Serial.begin(115200);
  Serial.println();
  
  // WiFi setup
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("  , ID is ");
  Serial.println(RxIP);
  
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  udp.begin(localPort);
}

void loop()
{
  udp.beginPacket(RxIP, RxPort);
  udp.write('a');
  udp.endPacket();

  delay(3000);
}
