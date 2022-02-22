#include <WiFi.h>
#include <WiFiUdp.h>

#define SSID "ESP32_AP"
#define PASSWORD "esp32pass"
#define HOST_PORT = 10000;

const IPAddress host_IP(192, 168, 4, 13);
const IPAddress subnet(255, 255, 255, 0);

WiFiUDP udp;

static const uint8_t start_BYTE = 0x0f;
int signal_size = NUM_CH + 2;

static void Wifi_setup()
{
  // setup ESP32 as Access Point
  WiFi.mode(WIFI_STA);
  WiFi.softAP(SSID, PASSWORD);
  delay(100);
  WiFi.softAPConfig(host_IP, host_IP, subnet);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: " + myIP.toString());
}

static void UDP_setup()
{
  Serial.println("Starting UDP");
  int ret = udp.begin(HOST_PORT);
  if (!ret)
    Serial.println("ERROR!!!!");
  Serial.print("Local port: ");
  Serial.println(HOST_PORT);
}

uint8_t _compute_parity()
{
  uint8_t signal_XOR = 0;
  for (int i = 1; i < signal_size - 1; i++)
  {
    signal_XOR ^= pwmBuffer[i];
  }
  return signal_XOR
}

bool _check_signal_rules(uint8_t signal[]) // signal_buffer[signal_size]
{
  if (signal[0] != start_BYTE)
  {
    Serial.println("start byte ERROR");
    return false;
  }

  uint8_t signal_XOR = _compute_parity();
  if (signal_XOR == pwmBuffer[signal_size - 1])
  {
    Serial.print("parity byte: XOR is ");
    Serial.print(signal_XOR);
    Serial.print(", buffer byte is ");
    Serial.println(pwmBuffer[7]);
    return false;
  }

  return true;
}

bool receive_signal(uint8_t signal_buffer[]) // PWM_signal[NUM_CH]
{
  // receive signals using UDP
  char c[1024];
  uint8_t signal_buffer[signal_size];
  udp.read(c, 8);
  // TODO: check code. buffer may not get correct value.
  for (int i = 0; i < signal_size; i++)
  {
    signal_buffer[i] = (uint8_t)(c[i]);
  }

  // check received signal and pickup motor controll signal
  bool check_result = _check_signal_rules();
  if (check_result)
  {
    for (int i = 1; i < signal_size - 1; i++)
    {
      signal_buffer[i - 1] = signal_buffer[i];
    }
  }

  return check_result;
}
