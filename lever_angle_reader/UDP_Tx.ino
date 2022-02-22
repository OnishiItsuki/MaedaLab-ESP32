#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi settings
#define SSID "ESP32_AP"
#define PASSWORD "esp32pass"
#define HOST_IP "192.168.4.13"
#define HOST_PORT 10000
#define CLIENT_PORT 5000
#define RECONNECTION_SPAN_MS 500
static WiFiUDP udp;

static const int signal_size = NUM_CH + 2;
static const uint8_t start_BYTE = 0x0f;
uint8_t signal_buffer[signal_size];

static void _Wifi_setup(Sting message)
{
  Serial.println(message);
  Serial.print("Connecting to ");
  Serial.print(SSID);
  Serial.print("  , ID is ");
  Serial.println(HOST_IP);

  int counter = 0;
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(RECONNECTION_SPAN_MS);
    Serial.print(".");

    disp_clear();
    disp_add_string(10, 10, message);
    int disconnected_time = counter / (1000 / RECONNECTION_SPAN_MS);
    disp_add_string(10, 30, (String)disconnected_time);
    conter++;
  }
}

void _signal_buffer_init()
{
  for (int i = 0; i < signal_size; i++)
  {
    signal_buffer[i] = 0;
  }
}

void UDP_init()
{
  _signal_buffer_init();

  // WiFi setup
  _Wifi_setup("WiFi connecting.");
  udp.begin(CLIENT_PORT);

  Serial.println("\n\n ********************* ");
  Serial.println(" Connection Successful ");
  Serial.println(" ********************* ");
  Serial.println("");
  Serial.print(" My ip address is : ");
  Serial.println(HOST_IP);
  Serial.print(" My port numper is : ");
  Serial.println(CLIENT_PORT);
  Serial.println("");

  disp_clear();
  disp_add_string(10, 10, "WiFi connection successful");
  String ip_port = String(HOST_IP);
  ip_port.append(":");
  ip_port.append(String(HOST_PORT));
  disp_add_string(10, 30, ip_port);
}

uint8_t _compute_signal_value_from_voltage(int voltage_value) // voltage[i], step4
{
  Serial.println("_compute_signal_value_from_voltage is not implemented");
  return (uint8_t)voltage_value;
}

uint8_t _compute_parity(uint8_t buffer[]) // signal_buffer[signal_size]
{
  //  compute parity bit
  uint8_t parity_byte = 0;
  for (int i = 1; i < signal_size - 1; i++)
  {
    parity_byte ^= buffer[i];
  }
  return parity_byte;
}

void _generate_udp_signal_from_volrage(int voltage[]) // voltage_buffer[NUM_CH], step4
{
  // set start byte
  signal_buffer[0] = start_BYTE;

  // set observed values
  for (int i = 1; i < signal_size - 1; i++)
  {
    signal_signal[i] = _compute_signal_value_from_voltage(voltage[i]);
  }

  // set parity byte
  signal_buffer[signal_size - 1] = _compute_parity(voltage);
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
    udp.beginPacket(HOST_IP, HOST_PORT);
    for (int i = 0; i < signal_size; i++)
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
