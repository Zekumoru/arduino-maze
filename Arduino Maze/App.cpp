// SDL Related Includes
#include "App.h"
#include "SDL.h"
#include "defines.hpp"
// Arduino Related Includes
#include "Adafruit_ILI9341.h"
#include <cmath>
#include <cstdint>

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft(TFT_CS, TFT_DC);

void setup()
{
  tft.begin();
  tft.setRotation(1);
}

float posX = 0;
float posY = 0;
int speed = 200; // in pixels

void loop()
{
  Button pressed = getInput();
  float deltaTime = getDeltaTime();

  switch (pressed)
  {
  case KEY_LEFT:
  {
    posX -= speed * deltaTime;
    if (posX < 0)
    {
      posX = 0;
    }
    break;
  }
  case KEY_RIGHT:
  {
    posX += speed * deltaTime;
    if (posX > SCREEN_WIDTH - 1)
    {
      posX = SCREEN_WIDTH - 1;
    }
    break;
  }
  case KEY_UP:
  {
    posY -= speed * deltaTime;
    if (posY < 0)
    {
      posY = 0;
    }
    break;
  }
  case KEY_OPTION:
  {
    posY += speed * deltaTime;
    if (posY > SCREEN_HEIGHT - 1)
    {
      posY = SCREEN_HEIGHT - 1;
    }
    break;
  }
  }

  // Convert to integers for rendering
  int renderPosX = static_cast<int>(std::round(posX));
  int renderPosY = static_cast<int>(std::round(posY));

  tft.fillScreen(ILI9341_WHITE);

  tft.setCursor(renderPosX, renderPosY);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.println("Hello Roby!\nThis is a simulation!! :D");

  // Test drawPixel
  for (int16_t x = 0; x < 5; x++)
  {
    for (int16_t y = 0; y < 5; y++)
    {
      tft.drawPixel(100 + x + posX, 200 + y + posY, ILI9341_BLACK);
    }
  }
}
