// SDL Related Includes
#include "App.h"
#include "SDL.h"
#include "defines.hpp"
// Arduino Related Includes
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

void setup()
{
  tft.begin();
  tft.setRotation(1);
}

int x = 0;
int y = 0;

void loop()
{
  Button pressed = getInput();

  if (pressed == KEY_LEFT)
  {
    x -= 1;

    if (x < 0)
    {
      x = 0;
    }
  }
  if (pressed == KEY_RIGHT)
  {
    x += 1;

    if (x > SCREEN_WIDTH - 1)
    {
      x = SCREEN_WIDTH - 1;
    }
  }

  tft.fillScreen(ILI9341_WHITE);

  tft.setCursor(x, y);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.println("Hello Roby!\nThis is a simulation!! :D");
}
