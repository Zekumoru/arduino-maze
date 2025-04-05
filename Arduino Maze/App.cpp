#include "App.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

const int WIDTH = 320;
const int HEIGHT = 240;

void setup()
{
  tft.begin();
  tft.setRotation(1);
}

void loop()
{
  tft.fillScreen(ILI9341_WHITE);

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.println("Hello, dklfdslakjf lkadjf lkdajf lksdajflk sd");
  tft.print("World!");
}
