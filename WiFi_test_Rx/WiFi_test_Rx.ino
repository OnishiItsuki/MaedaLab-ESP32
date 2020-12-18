#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "ESP32_AP";
const char password[] = "esp32pass";
const int localPort = 10000;

const IPAddress RxIP(192, 168, 4, 13);
const IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;

static uint8_t buffer[8];

static void Wifi_setup()
{
  // setup ESP32 as Access Point
  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(RxIP, RxIP, subnet);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: " + myIP.toString());
}

static void UDP_setup()
{
  Serial.println("Starting UDP");
  int ret = udp.begin(localPort);
  if (!ret)  Serial.println("ERROR!!!!");
  Serial.print("Local port: ");
  Serial.println(localPort);

}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Wifi_setup();
  UDP_setup();
}

char c[1024];
long err_cnt = 0;

void loop() {
  if (udp.parsePacket()) {
    udp.read(c, 8);
    for (int i=0; i<8; i++) {
      buffer[i] = ((uint8_t)(c[i] & 0xff));
    }
    Serial.println("print Buffer array");
    for (int i=0; i<8; i++) {
      Serial.println(buffer[i]);
    }

    // reset watch dog counter
    err_cnt = 0;
    return;
  }
    else
  {
    if (err_cnt++>100000)
    {
      Serial.println("Disconeted");
      // reset watch dog counter
      err_cnt = 0;
    }
  }
}
