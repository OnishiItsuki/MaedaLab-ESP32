#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "ESP32_AP";
const char password[] = "damedame";

static WiFiUDP udp;
static const char *RxIP = "192.168.4.13";
static const int RxPort = 10000;

static const int localPort = 5000;

static void Wifi_setup()
{
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("  , ID is ");
  Serial.println(RxIP);
  
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  // WiFi setup
  Wifi_setup();
  udp.begin(localPort);

  Serial.println("\n\n **************************");
  Serial.println(" * Connected Successfully *");
  Serial.println(" **************************");
  Serial.println("");
  Serial.print(" My ip address is : ");   Serial.println(RxIP);
  Serial.print(" My port numper is : ");  Serial.println(RxPort);
  Serial.println("");
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Disconnected");
  } else {
    udp.beginPacket(RxIP, RxPort);
    udp.write('a');
    udp.endPacket();  
  }
  delay(3000);
}
