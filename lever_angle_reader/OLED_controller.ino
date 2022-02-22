// This file requires "ESP8266 and ESP32 driver for SSD1366 displays" library.

// detail is on following
// https://wak-tech.com/archives/825
// https://github.com/ThingPulse/esp8266-oled-ssd1306

#include <Wire.h>
#include <SSD1306.h>

#ifndef SDA_PNT
#define SDA_PIN 21
#endif

#ifndef SCL_PIN
#define SCL_PIN 22
#endif

#define OLED_ADDR 0x3c
#define FONT ArialMT_Plain_16

const static int font_size_width = 10;
const static int font_size_height = 20;

const static int disp_width = 128;
const static int disp_height = 64;

static const int max_num_char_width = disp_width / font_size_width;
static const int max_num_line = disp_height / font_size_height;


SSD1306 display(OLED_ADDR, SDA_PIN, SCL_PIN);

void OLED_init()
{
  disp_init();
  disp_all_pixel();
  delay(1000);
  disp_clear();
}

void disp_init()
{
  display.init();
  display.setFont(FONT);
}

void disp_clear()
{
  disp_init();
}

void disp_all_pixel()
{
  display.fillRect(0, 0, disp_width, disp_height);
  display.display();
}

void disp_add_string(int16_t x, int16_t y, String message)
{
  display.drawString(x, y, message);
  display.display();
}


void disp_show_string(String message)
{
  disp_clear();

  int line_index = 0;
  int str_pointer_of_line_head = 0;
  int pointer;
  String string_line;
  
  while (str_pointer_of_line_head < message.length())
  {
    string_line = "";
    for (int i = 0; i < max_num_char_width; i++)
    {
      pointer = str_pointer_of_line_head + i;
      string_line += message[pointer];
    }
    int16_t y = font_size_height * line_index;
    disp_add_string(0, y, string_line);

    line_index++;
    str_pointer_of_line_head = pointer + 1;
  }

  if (line_index > max_num_line)
  {
    Serial.println("Waring: String on display may be cut off and not be displayed correctly.");
  }
}