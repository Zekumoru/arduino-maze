#include "GameOverScene.hpp"

#include "libs/Adafruit_ILI9341.hpp"

extern Adafruit_ILI9341 tft;

GameOverScene::GameOverScene()
{
  // set text pos
}

void GameOverScene::render()
{
  // REFACTOR: Dependency inject minimap.
  // render "GAME OVER" text

  // resetMiniMap();
  // player.pos = playerStartPos;
  // setMiniMap((int)player.pos.x, (int)player.pos.y);

  // render "Press a button to try again..."
}

GameState GameOverScene::processInput(const bool *buttonsState, const bool *buttonsJustPressed, float deltaTime)
{
  // REFACTOR: Use putButtons().
  // GameState newGamestate = GameState::GAME_OVER;
  // bool input = false;
  // while (!input)
  // {
  //   // read input
  //   Button button = getButton();
  //   if (button)
  //   {
  //     input = true;
  //     newGamestate = GameState::MAIN_MENU;
  //   }
  //   // sleep??
  // }

  return GameState::GAME_OVER;
}