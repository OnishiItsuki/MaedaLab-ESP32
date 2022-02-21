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
#define DISP_WIDTH 128
#define DISP_HEIGHT 64
#define FONT ArialMT_Plain_16

#define FONT_SIZE_HEIGHT 20
#define FONT_SIZE_WIDTH 10
static const max_num_char_width = DISP_WIDTH / FONT_SIZE_WIDTH;

static const indent_x = 5;
static const indent_y = 5;

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
  display.fillRect(0, 0, DISP_WIDTH, DISP_HEIGHT);
  display.display();
}

void disp_add_string(int16_t x, int16_t y, String message)
{
  display.drawString(x, y, message);
  display.display();
}

void disp_show_string(String message) // TODO: debug
{
  disp_clear();
  int line_index = 0;

  int str_index = 0;
  while (str_index < message.length())
  {
    String string_line = "";
    for (int i = 0; i < max_num_char_width; i++)
    {
      static int pointer = str_index + i;
      char char1 = message.charAt(pointer);
      char char2 = message.charAt(pointer + 1);

      if (char1 == '\\' and char2 == 'n')
      {
        break;
      }
      else
      {
        string_line += message[pointer];
      }

      int16_t y = indent_y + (FONT_SIZE_HEIGHT * line_index);
      disp_add_string(indent_x, y, string_line);
      str_index = pointer + 2;
    }

  }
}
