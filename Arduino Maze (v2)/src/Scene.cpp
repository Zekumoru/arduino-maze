#include "Scene.hpp"

#ifndef IS_USING_SDL
#include "Adafruit_ILI9341.h"
#else
#include "libs/Adafruit_ILI9341.hpp"
#endif

extern Adafruit_ILI9341 tft;

void Scene::clearScreen()
{
  // call to clear pixel buffer with black
  tft.fillScreen(COL_BLACK);
}
