#include "MainMenuScene.hpp"

#include "../libs/Adafruit_ILI9341.hpp"

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
