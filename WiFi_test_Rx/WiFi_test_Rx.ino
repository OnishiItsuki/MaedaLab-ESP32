#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "ESP32_AP";
const char password[] = "esp32pass";
const int localPort = 10000;

const IPAddress RxIP(192, 168, 4, 13);
const IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;

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
    udp.read(c, 4);
    unsigned long t1 = ((unsigned long)(c[0] & 0xff)) << 24;
    unsigned long t2 = ((unsigned long)(c[1] & 0xff)) << 16;
    unsigned long t3 = ((unsigned long)(c[2] & 0xff)) << 8;
    unsigned long t4 =  (unsigned long) c[3];
    Serial.println(t1 + t2 + t3 + t4);

    // reset watch dog counter
    err_cnt = 0;
    return;
  }
    else
  {
    if (err_cnt++>10000)
    {
      // reconnect
      Wifi_setup();

      // reset watch dog counter
      err_cnt = 0;
    }
}
