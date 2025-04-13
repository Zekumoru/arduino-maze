#include "Scene.hpp"

#include "../libs/Adafruit_ILI9341.hpp"

extern Adafruit_ILI9341 tft;

void Scene::clearScreen()
{
  // call to clear pixel buffer with black
  tft.fillScreen(COL_BLACK);
}
