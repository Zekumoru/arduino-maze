#include "LoadingScene.hpp"

#include "../definitions.hpp"
#include "../engine/Scene.hpp"
#include "../libs/Adafruit_ILI9341.hpp"

extern Adafruit_ILI9341 tft;

LoadingScene::LoadingScene() : loadingText("Loading...")
{
  // calls to load the image?
  // set text pos
}

GameState LoadingScene::processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime)
{
  return GameState::LOADING;
}

void LoadingScene::render()
{
  clearScreen();
  // call to render the image
  // call to render the text "Loading..."
  tft.setCursor(0, 0);
  tft.setTextColor(COL_BLUE);
  tft.setTextSize(5);
  tft.print(loadingText);
}
