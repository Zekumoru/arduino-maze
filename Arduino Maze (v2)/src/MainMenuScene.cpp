#include "MainMenuScene.hpp"

#ifndef IS_USING_SDL
#include "Adafruit_ILI9341.h"
#else
#include "libs/Adafruit_ILI9341.hpp"
#endif

extern Adafruit_ILI9341 tft;

MainMenuScene::MainMenuScene()
{
  // call to load image?
  // set text_pos
}

void MainMenuScene::render()
{
  clearScreen();
  // call to render image
  // call to render text "Press a button to start"
  tft.setCursor(0, 0);
  tft.setTextColor(COL_BLUE);
  tft.setTextSize(5);
  tft.print("Press\na button\nto start!");
}

GameState MainMenuScene::processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime)
{
  // process input logic here

  return GameState::GAME_VIEW;
}
