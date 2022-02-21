#include <WiFi.h>
#include <WiFiUdp.h>

static const int buffer_size = NUM_CH + 2;
static uint8_t start_bit = 0x0f;
uint8_t signal_buffer[buffer_size];
int reconnection_span_ms = 500;

// WiFi settings
const char ssid[] = "ESP32_AP";
const char password[] = "esp32pass";
static WiFiUDP udp;
static const char RxIP[] = "192.168.4.13";
static const int RxPort = 10000;
static const int localPort = 5000;

static void _Wifi_setup(Sting message)
{
  Serial.println(message);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("  , ID is ");
  Serial.println(RxIP);

  int counter = 0;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(reconnection_span_ms);
    Serial.print(".");

    disp_clear();
    disp_add_string(10, 10, message);
    int disconnected_time = counter / (1000 / reconnection_span_ms);
    disp_add_string(10, 30, (String)disconnected_time);
    conter++;
  }
}

void _signal_buffer_init()
{
  for (int i = 0; i < buffer_size; i++)
  {
    signal_buffer[i] = 0;
  }
}

void UDP_init()
{
  _signal_buffer_init();

  // WiFi setup
  _Wifi_setup("WiFi connecting.");
  udp.begin(localPort);

  Serial.println("\n\n ********************* ");
  Serial.println(" Connection Successful ");
  Serial.println(" ********************* ");
  Serial.println("");
  Serial.print(" My ip address is : ");
  Serial.println(RxIP);
  Serial.print(" My port numper is : ");
  Serial.println(RxPort);
  Serial.println("");

  disp_clear();
  disp_add_string(10, 10, "WiFi connection successful");
  String ip_port = String(RxIP);
  ip_port.append(":");
  ip_port.append(String(RXPort));
  disp_add_string(10, 30, ip_port);
}

uint8_t _compute_signal_value_from_voltage(int voltage_value) // voltage[i], step4
{
  Serial.println("_compute_signal_value_from_voltage is not implemented");
  return (uint8_t)voltage_value;
}

uint8_t _compute_parity(uint8_t buffer[]) // signal_buffer[buffer_size]
{
  // initialize parity bit
  buffer[buffer_size - 1] = 0;

  //  compute parity bit
  uint8_t parity_bit = 0;
  for (int i = 1; i < buffer_size - 1; i++)
  {
    parity_bit ^= buffer[i];
  }
  return parity_bit;
}

void _generate_udp_signal_from_volrage(int voltage[]) // voltage_buffer[NUM_CH], step4
{
  signal_buffer[0] = start_bit;
  for (int i = 1; i < buffer_size - 1; i++)
  {
    signal_signal[i] = _compute_signal_value_from_voltage(voltage[i]);
  }
  signal_buffer[buffer_size - 1] = _compute_parity(voltage);
}

void _send_signal() // step5
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi disconnected. Reconnecting");
    _Wifi_setup("WiFi disconnected. Reconnecting");
  }
  else
  {
    udp.beginPacket(RxIP, RxPort);
    for (int i = 0; i < buffer_size; i++)
    {
      udp.write(signal_buffer[i]); // send packet
    }
    udp.endPacket();
  }
  _signal_buffer_init();
}

void send_udp_signal(int voltage[]) // voltage_buffer[NUM_CH]
{
  _generate_udp_signal_from_volrage(voltage); // step4
  _send_signal();                             // step5
}
