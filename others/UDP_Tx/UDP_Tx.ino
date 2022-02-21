#include <WiFi.h>
#include <WiFiUdp.h>

const char ssid[] = "ESP32_AP";
const char password[] = "esp32pass";

static WiFiUDP udp;
static const char *RxIP = "192.168.4.13";
static const int RxPort = 10000;
static const int localPort = 5000;

uint8_t start_byte = 0x0f;
uint8_t boom_byte = 10;
uint8_t arm_byte = 50;
uint8_t bucket_byte = 100;
uint8_t slewing_byte = 138;
uint8_t r_wheel_byte = 178;
uint8_t l_wheel_byte = 228;
uint8_t parity_byte = 0x00;

uint8_t buffer[8];

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

static void AD_converter()
{
  // TODO: make AD converter
  // Now put test value into buffer for test
  buffer[0] = start_byte;
  buffer[1] = boom_byte;
  buffer[2] = arm_byte;
  buffer[3] = bucket_byte;
  buffer[4] = slewing_byte;
  buffer[5] = r_wheel_byte;
  buffer[6] = l_wheel_byte;
}

static unsigned int comp_parity()
{
  // initialize parity buffer
  buffer[7] = 0;

  //  compute parity buffer
  uint8_t tmp = buffer[1];
  for (int i = 2; i < 7; i++) {
    tmp ^= buffer[i];
  }
  return tmp;
}

void loop()
{
  AD_converter();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected");
    Wifi_setup();
  } else {
    buffer[7] = comp_parity();

    udp.beginPacket(RxIP, RxPort);
    for (int i = 0; i < 8; i++) {
      udp.write(buffer[i]);    //packet sending
    }
    udp.endPacket();

    Serial.println("print Buffer array");
    for (int i = 0; i < 8; i++) {
      Serial.println(buffer[i]); // to separate line
    }

    delay(1000);
  }
}
